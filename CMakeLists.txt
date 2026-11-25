cmake_minimum_required(VERSION 3.25)
project(dotd LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- no build-machine paths in the binaries -------------------------------------------------------
# __FILE__ (asserts, FFmpeg's av_log/av_assert) and debug info would otherwise hold the checkout's
# absolute path, the build machine's user folder included; the published dotd.wasm must not. The paths
# become relative to the folder above dotd/ (dotd/src/..., dotd/thirdparty/ffmpeg/..., toolchain/...).
if(NOT MSVC)
  get_filename_component(DOTD_PATH_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/.." ABSOLUTE)
  add_compile_options("-ffile-prefix-map=${DOTD_PATH_ROOT}/=" "-ffile-prefix-map=${DOTD_PATH_ROOT}=.")
endif()

# ---- the web build (Emscripten: wasm32 + WebGL2, preset "wasm"; web/README.md) --------------------
# The game keeps its threads (the load-request worker, the particle threads), so every object, SDL and
# FFmpeg included, is built with -pthread (shared memory: the page must be served cross-origin isolated,
# which web/serve.py does).
if(EMSCRIPTEN)
  add_subdirectory(web/zstddec)  # (before -pthread: the download worker's zstd decoder is a module without threads)
  add_compile_options(-pthread)
  add_link_options(-pthread)
  set(SDL_PTHREADS ON CACHE BOOL "" FORCE)
endif()

# ---- third party (built from source) -------------------------------------------------------------
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)
# SDL and FFmpeg come from the submodule / clone when they are there (a git worktree can point DOTD_SDL_DIR and
# DOTD_FFMPEG_DIR at the main checkout's copies), else from their release source archives, downloaded and checked by
# cmake/FetchDeps.cmake (the same sources: SDL release-3.4.18 = the submodule's commit 829a65d, FFmpeg 7.1.2 = tag
# n7.1.2).
include(cmake/FetchDeps.cmake)
set(DOTD_SDL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SDL" CACHE PATH "SDL3 source tree")
dotd_fetch_source(SDL3 "https://github.com/libsdl-org/SDL/releases/download/release-3.4.18/SDL3-3.4.18.tar.gz"
                  9c75cf16330322c217dedd2e0609f1124f1b54b8633e763467b4684d0f4334a3 SDL3-3.4.18 CMakeLists.txt DOTD_SDL_DIR)
if(NOT EXISTS "${DOTD_SDL_DIR}/CMakeLists.txt")
  message(FATAL_ERROR "dotd: no SDL3 source at ${DOTD_SDL_DIR}. Run 'git submodule update --init' or configure with "
                      "DOTD_FETCH_DEPS=ON and an internet connection (thirdparty/README.md).")
endif()
add_subdirectory("${DOTD_SDL_DIR}" "${CMAKE_BINARY_DIR}/thirdparty/SDL" EXCLUDE_FROM_ALL)
# Bink video, Bink audio and the levels' ATRAC3 speech: FFmpeg's decoders, built from the FFmpeg source by
# thirdparty/ffmpeg-bink. Without them the game runs with no videos and no speech, so a build without FFmpeg is
# refused unless DOTD_NO_VIDEO=ON asks for one.
option(DOTD_NO_VIDEO "Build without FFmpeg (no videos, no speech)" OFF)
set(DOTD_FFMPEG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/ffmpeg" CACHE PATH "FFmpeg source tree (tag n7.1.2)")
if(NOT DOTD_NO_VIDEO)
  dotd_fetch_source(FFmpeg "https://ffmpeg.org/releases/ffmpeg-7.1.2.tar.xz"
                    089bc60fb59d6aecc5d994ff530fd0dcb3ee39aa55867849a2bbc4e555f9c304 ffmpeg-7.1.2 libavcodec/bink.c
                    DOTD_FFMPEG_DIR)
endif()
if(NOT DOTD_NO_VIDEO AND EXISTS "${DOTD_FFMPEG_DIR}/libavcodec/bink.c")
  set(FFMPEG_BINK_SOURCE_DIR "${DOTD_FFMPEG_DIR}")
  add_subdirectory(thirdparty/ffmpeg-bink "${CMAKE_BINARY_DIR}/ff" EXCLUDE_FROM_ALL)
  set(DOTD_HAVE_FFMPEG_BINK 1)
elseif(DOTD_NO_VIDEO)
  message(STATUS "dotd: DOTD_NO_VIDEO=ON: built without FFmpeg, videos and speech are not played")
  set(DOTD_HAVE_FFMPEG_BINK 0)
else()
  message(FATAL_ERROR "dotd: no FFmpeg source at ${DOTD_FFMPEG_DIR} and the download failed: without it there are no "
                      "videos and no speech. Configure again with an internet connection, clone FFmpeg n7.1.2 there "
                      "(thirdparty/README.md), or pass -DDOTD_NO_VIDEO=ON for a build without them.")
endif()

# ASTC block packing: ARM's astc-encoder, a source clone (thirdparty/README.md). Only the web build links it: there a
# GPU without S3TC gets the DXT textures rewritten as ASTC 4x4 (platform/gfx/texture_transcode.h); natively it is only
# the transcoder test's. Scalar code (no SSE / NEON paths: the same everywhere, wasm included).
set(DOTD_ASTCENC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/astc-encoder" CACHE PATH "astc-encoder source tree (tag 5.5.0)")
if(EXISTS "${DOTD_ASTCENC_DIR}/Source/astcenc_symbolic_physical.cpp")
  file(GLOB DOTD_ASTCENC_SOURCES "${DOTD_ASTCENC_DIR}/Source/astcenc_*.cpp")
  add_library(astcenc_pack STATIC EXCLUDE_FROM_ALL ${DOTD_ASTCENC_SOURCES})
  target_include_directories(astcenc_pack PUBLIC "${DOTD_ASTCENC_DIR}/Source")
  target_compile_definitions(astcenc_pack PUBLIC ASTCENC_SSE=0 ASTCENC_AVX=0 ASTCENC_NEON=0 ASTCENC_SVE=0
                             ASTCENC_POPCNT=0 ASTCENC_F16C=0)
else()
  message(STATUS "dotd: no astc-encoder clone at ${DOTD_ASTCENC_DIR}: phones without S3TC get RGBA8 textures")
endif()

# ---- our code: floating point must match the PS3 (outputs/decompilation-plan.md section 4) ------
# No contraction, no fast-math; decompiled code also needs wrapping integer arithmetic and no
# strict aliasing. These options apply to dotd targets only, not to SDL.
if(MSVC)
  set(DOTD_COMPILE_OPTIONS /fp:precise /W3 /utf-8 /D_CRT_SECURE_NO_WARNINGS)
else()
  set(DOTD_COMPILE_OPTIONS -ffp-contract=off -fno-fast-math -fno-strict-aliasing -fwrapv)
endif()

# DOTD_PS3_LAYOUT: 1 when pointers are 32-bit, enabling the static_asserts that check struct layouts against
# the PS3 offsets. That is the Win32 parity preset's job: the web build (wasm32) leaves them off, like x64.
if(CMAKE_SIZEOF_VOID_P EQUAL 4 AND NOT EMSCRIPTEN)
  set(DOTD_LAYOUT_DEFINE DOTD_PS3_LAYOUT=1)
else()
  set(DOTD_LAYOUT_DEFINE DOTD_PS3_LAYOUT=0)
endif()

function(dotd_target_setup target)
  target_compile_options(${target} PRIVATE ${DOTD_COMPILE_OPTIONS})
  target_compile_definitions(${target} PUBLIC ${DOTD_LAYOUT_DEFINE})
  target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
endfunction()

# Platform layer (replaces the PS3 SDK surface the game calls; the only place SDL is used)
file(GLOB_RECURSE DOTD_PLATFORM_SOURCES CONFIGURE_DEPENDS src/platform/*.cpp)
add_library(dotd_platform STATIC ${DOTD_PLATFORM_SOURCES})
dotd_target_setup(dotd_platform)
target_link_libraries(dotd_platform PUBLIC SDL3::SDL3-static)
target_compile_definitions(dotd_platform PRIVATE DOTD_HAVE_FFMPEG_BINK=${DOTD_HAVE_FFMPEG_BINK})
if(DOTD_HAVE_FFMPEG_BINK)
  target_link_libraries(dotd_platform PRIVATE ffbink)
endif()
if(EMSCRIPTEN AND TARGET astcenc_pack)
  target_link_libraries(dotd_platform PRIVATE astcenc_pack)
  target_compile_definitions(dotd_platform PRIVATE DOTD_HAVE_ASTCENC=1)
endif()

# Game and engine sources (one .cpp per reconstructed original translation unit)
file(GLOB_RECURSE DOTD_GAME_SOURCES CONFIGURE_DEPENDS src/crt/*.cpp src/k2000/*.cpp src/Spyro2008/*.cpp
     src/Renderware/*.cpp)
add_library(dotd_game STATIC ${DOTD_GAME_SOURCES})
dotd_target_setup(dotd_game)
target_link_libraries(dotd_game PUBLIC dotd_platform)

add_executable(dotd src/main.cpp)
dotd_target_setup(dotd)
target_link_libraries(dotd PRIVATE dotd_game)

if(EMSCRIPTEN)
  # dotd.js + dotd.wasm next to web/index.html (copied into the build folder); web/serve.py serves them and
  # the game's USRDIR. WebGL2 only (the backend is GLES 3.0), memory grows up to the wasm32 limit, the thread
  # pool is created before main() so a thread started from the browser's main thread runs at once. IDBFS: the
  # page keeps the home folder (saves, the shader variant list) in the browser's IndexedDB.
  set(DOTD_WEB_LINK_OPT "-O2" CACHE STRING "Optimisation level of the wasm link (-O1 links much faster)")
  set_target_properties(dotd PROPERTIES SUFFIX ".js")
  target_link_options(dotd PRIVATE
    ${DOTD_WEB_LINK_OPT} --profiling-funcs
    -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sGL_ENABLE_GET_PROC_ADDRESS=1
    -sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=1024MB -sMAXIMUM_MEMORY=4GB
    -sSTACK_SIZE=4MB -sDEFAULT_PTHREAD_STACK_SIZE=2MB -sPTHREAD_POOL_SIZE=12
    -sENVIRONMENT=web,worker -sEXIT_RUNTIME=0
    -lidbfs.js
    "-sEXPORTED_RUNTIME_METHODS=['callMain','FS','IDBFS','ENV','addRunDependency','removeRunDependency']" -sINVOKE_RUN=0)
  foreach(web_file index.html serve.py sw.js pack-worker.js manifest.webmanifest icon.svg
          btn-triangle.png btn-circle.png btn-cross.png btn-square.png)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/web/${web_file} ${CMAKE_CURRENT_BINARY_DIR}/${web_file} COPYONLY)
  endforeach()
  if(TARGET zstddec)
    add_dependencies(dotd zstddec)
  endif()
  return()  # the tests are native only
endif()

# ---- tests -------------------------------------------------------------------------------------
enable_testing()
# Build size (work/test-runner.md): the tests that link the game are compiled into one executable, dotd_tests, which runs
# one of them by name: dotd_tests <source name> [args] (e.g. dotd_tests level_load_test 10), the test's main() getting the
# args after the name (argv[0] stays the executable). ctest keeps one entry per test. One linked copy of the game instead
# of one per test (a worktree build was 8-10 GB, mostly the per-test .exe/.pdb/.ilk). newgame_test stays its own
# executable (the replay scripts run it directly). The test executables link without incremental linking (no .ilk).
if(MSVC)
  set(DOTD_TEST_LINK_OPTIONS "$<$<CONFIG:Debug,RelWithDebInfo>:/INCREMENTAL:NO>")
  # A main() renamed for the runner has no implicit "return 0": a missing return must not compile.
  set(DOTD_RUNNER_COMPILE_OPTIONS /we4715 /we4716)
endif()

function(dotd_test_setup target)
  dotd_target_setup(${target})
  target_link_options(${target} PRIVATE ${DOTD_TEST_LINK_OPTIONS})
endfunction()

# dotd_runner_test(TEST SOURCE): ctest entry TEST runs SOURCE's main() in dotd_tests, under SOURCE's file name. A
# generated wrapper includes SOURCE with main renamed (its includes and __FILE__ unchanged) and exports it.
set(DOTD_RUNNER_NAMES)
set(DOTD_RUNNER_SOURCES)
function(dotd_runner_test test source)
  get_filename_component(name ${source} NAME_WE)
  set(wrapper "${CMAKE_CURRENT_BINARY_DIR}/dotd_tests/${name}.cpp")
  file(CONFIGURE OUTPUT "${wrapper}" @ONLY CONTENT [[
// Generated by dotd/CMakeLists.txt (dotd_runner_test): @name@ in the dotd_tests runner.
#define main dotd_test_main_@name@
#include "@source@"
#undef main
namespace {
int DotdRunnerCall(int (*run)(), int, char**) { return run(); }
int DotdRunnerCall(int (*run)(int, char**), int argc, char** argv) { return run(argc, argv); }
}  // namespace
extern "C" int dotd_test_run_@name@(int argc, char** argv) { return DotdRunnerCall(&dotd_test_main_@name@, argc, argv); }
]])
  set(DOTD_RUNNER_NAMES ${DOTD_RUNNER_NAMES} ${name} PARENT_SCOPE)
  set(DOTD_RUNNER_SOURCES ${DOTD_RUNNER_SOURCES} ${wrapper} PARENT_SCOPE)
  add_test(NAME ${test} COMMAND dotd_tests ${name})
endfunction()

add_executable(ppc_ops_test tests/ppc_ops_test.cpp)
dotd_test_setup(ppc_ops_test)
add_test(NAME ppc_ops COMMAND ppc_ops_test)

dotd_runner_test(kclock ${CMAKE_CURRENT_SOURCE_DIR}/tests/kclock_test.cpp)

# The DXT to ASTC transcoder against astc-encoder's decoder, on the textures of a level (DOTD_USRDIR; skipped without).
if(TARGET astcenc_pack)
  add_executable(astc_transcode_test tests/astc_transcode_test.cpp src/platform/gfx/texture_transcode.cpp)
  dotd_test_setup(astc_transcode_test)
  target_link_libraries(astc_transcode_test PRIVATE astcenc_pack)
  target_compile_definitions(astc_transcode_test PRIVATE DOTD_HAVE_ASTCENC=1)
  add_test(NAME astc_transcode COMMAND astc_transcode_test)
  set_tests_properties(astc_transcode PROPERTIES SKIP_RETURN_CODE 77)
endif()

add_executable(platform_test tests/platform_test.cpp)
dotd_test_setup(platform_test)
target_link_libraries(platform_test PRIVATE dotd_platform)
add_test(NAME platform COMMAND platform_test)

# The disc's EBOOT.BIN decrypted in memory against RPCS3's EBOOT.elf (DOTD_USRDIR; skipped without).
add_executable(self_decrypt_test tests/self_decrypt_test.cpp)
dotd_test_setup(self_decrypt_test)
target_link_libraries(self_decrypt_test PRIVATE dotd_platform)
add_test(NAME self_decrypt COMMAND self_decrypt_test)
set_tests_properties(self_decrypt PROPERTIES SKIP_RETURN_CODE 77)

dotd_runner_test(boot ${CMAKE_CURRENT_SOURCE_DIR}/tests/boot_test.cpp)
set_tests_properties(boot PROPERTIES SKIP_RETURN_CODE 77)

# Checkpoint C1.5: one test per tests/c15/*_test.cpp, each with the boot helper. They need the game data for the boot
# parts (skipped, exit 77, without it). newgame_test is its own executable, the others are in dotd_tests.
file(GLOB DOTD_C15_TESTS CONFIGURE_DEPENDS tests/c15/*_test.cpp)
foreach(test_source ${DOTD_C15_TESTS})
  get_filename_component(test_name ${test_source} NAME_WE)
  if(test_name STREQUAL "newgame_test")
    add_executable(newgame_test ${test_source} tests/c15/boot_helper.cpp)
    dotd_test_setup(newgame_test)
    target_link_libraries(newgame_test PRIVATE dotd_game)
    add_test(NAME newgame_test COMMAND newgame_test)
  else()
    dotd_runner_test(${test_name} ${test_source})
  endif()
  set_tests_properties(${test_name} PROPERTIES SKIP_RETURN_CODE 77)
endforeach()

# fps_timing (not a ctest): the --fps N timing measurements, run by hand with DOTD_TEST_FPS (tests/c15/fps_timing.cpp).
add_executable(fps_timing tests/c15/fps_timing.cpp tests/c15/boot_helper.cpp)
dotd_test_setup(fps_timing)
target_link_libraries(fps_timing PRIVATE dotd_game)

# The runner: the wrappers, the boot helper once, and a main() that dispatches on argv[1].
set(DOTD_RUNNER_TABLE "")
foreach(name ${DOTD_RUNNER_NAMES})
  string(APPEND DOTD_RUNNER_TABLE "extern \"C\" int dotd_test_run_${name}(int argc, char** argv);\n")
endforeach()
string(APPEND DOTD_RUNNER_TABLE "const DotdTest kTests[] = {\n")
foreach(name ${DOTD_RUNNER_NAMES})
  string(APPEND DOTD_RUNNER_TABLE "    {\"${name}\", &dotd_test_run_${name}},\n")
endforeach()
string(APPEND DOTD_RUNNER_TABLE "};")
file(CONFIGURE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/dotd_tests/dotd_tests_main.cpp" @ONLY CONTENT [[
// Generated by dotd/CMakeLists.txt: dotd_tests <test> [args] runs one test's main() with the arguments after <test>;
// argv[0] stays this executable. The test's name is also put in DOTD_TESTS_RUN, so a test that starts argv[0] again
// as a child process (level_load_test) gets itself back: dotd_tests [args] runs the DOTD_TESTS_RUN test.
#include <cstdio>
#include <cstdlib>
#include <cstring>
namespace {
struct DotdTest {
    const char* name;
    int (*run)(int argc, char** argv);
};
}  // namespace
@DOTD_RUNNER_TABLE@
namespace {
const DotdTest* FindTest(const char* name) {
    for (const DotdTest& test : kTests) {
        if (std::strcmp(name, test.name) == 0) return &test;
    }
    return nullptr;
}
}  // namespace
int main(int argc, char** argv) {
    if (argc >= 2) {
        if (const DotdTest* test = FindTest(argv[1])) {
#ifdef _WIN32
            _putenv_s("DOTD_TESTS_RUN", test->name);
#else
            setenv("DOTD_TESTS_RUN", test->name, 1);
#endif
            argv[1] = argv[0];
            return test->run(argc - 1, argv + 1);
        }
    }
    if (const char* name = std::getenv("DOTD_TESTS_RUN")) {
        if (const DotdTest* test = FindTest(name)) return test->run(argc, argv);
    }
    if (argc >= 2) std::fprintf(stderr, "dotd_tests: no test %s\n", argv[1]);
    std::fprintf(stderr, "usage: dotd_tests <test> [args]; tests:");
    for (const DotdTest& test : kTests) std::fprintf(stderr, " %s", test.name);
    std::fprintf(stderr, "\n");
    return 2;
}
]])
add_executable(dotd_tests "${CMAKE_CURRENT_BINARY_DIR}/dotd_tests/dotd_tests_main.cpp" ${DOTD_RUNNER_SOURCES}
               tests/c15/boot_helper.cpp)
dotd_test_setup(dotd_tests)
target_compile_options(dotd_tests PRIVATE ${DOTD_RUNNER_COMPILE_OPTIONS})
target_link_libraries(dotd_tests PRIVATE dotd_game)
# C2.3: the opening cutscene skipped with START + yes during its video (the same executable, a variant by environment).
add_test(NAME newgame_skip_test COMMAND newgame_test)
set_tests_properties(newgame_skip_test PROPERTIES SKIP_RETURN_CODE 77 ENVIRONMENT "DOTD_NEWGAME_SKIP=1")

# C2.5 step 6: the opening skipped, LVL010's one clone node (hidden at start-up) shown and the free camera put next to it (it needs the
# hidden-window device: no frame is drawn without one): it must go through the team's render. No picture is saved (frame 999999).
add_test(NAME newgame_clone_test COMMAND newgame_test)
set_tests_properties(newgame_clone_test PROPERTIES SKIP_RETURN_CODE 77
  ENVIRONMENT "DOTD_NEWGAME_SKIP=1;DOTD_SHOW_CLONES=2;DOTD_NEWGAME_SHOTS=${CMAKE_CURRENT_BINARY_DIR};DOTD_NEWGAME_SHOT_FRAMES=999999")

# Needs the game data: set DOTD_USRDIR (or dotd.ini); skipped (exit 77) when not configured.
add_test(NAME fs_selftest COMMAND dotd --selftest-fs)
set_tests_properties(fs_selftest PROPERTIES SKIP_RETURN_CODE 77)
# C2.3 step 4: START during the opening cutscene's in-engine part (not skippable: the pause request of CKS08GameManager::CheckPauseRequest).
add_test(NAME newgame_pause_scene_test COMMAND newgame_test)
# C2.8 live-fixes: in that pause the armours page is opened, an armour chosen and the page left with Circle (DOTD_NEWGAME_ARMORS).
# C2.8 live-fixes-3: then the moves page is opened, its pages turned with the d-pad and the page left with Circle (DOTD_NEWGAME_MOVES).
set_tests_properties(newgame_pause_scene_test PROPERTIES SKIP_RETURN_CODE 77 ENVIRONMENT "DOTD_NEWGAME_SKIP2=1;DOTD_NEWGAME_ARMORS=1;DOTD_NEWGAME_MOVES=1")
