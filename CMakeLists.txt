cmake_minimum_required(VERSION 3.25)
project(dotd LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- third party (built from source) -------------------------------------------------------------
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)
# A git worktree has no submodule checkout: point DOTD_SDL_DIR at the main checkout's thirdparty/SDL.
set(DOTD_SDL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SDL" CACHE PATH "SDL3 source tree")
add_subdirectory("${DOTD_SDL_DIR}" "${CMAKE_BINARY_DIR}/thirdparty/SDL" EXCLUDE_FROM_ALL)
# Bink video: FFmpeg's Bink decoders, built from a source clone of FFmpeg (thirdparty/README.md) by
# thirdparty/ffmpeg-bink. Without the clone everything still builds and videos are not played. A git
# worktree can point DOTD_FFMPEG_DIR at the main checkout's clone.
set(DOTD_FFMPEG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/ffmpeg" CACHE PATH "FFmpeg source tree (tag n7.1.2)")
if(EXISTS "${DOTD_FFMPEG_DIR}/libavcodec/bink.c")
  set(FFMPEG_BINK_SOURCE_DIR "${DOTD_FFMPEG_DIR}")
  add_subdirectory(thirdparty/ffmpeg-bink "${CMAKE_BINARY_DIR}/ff" EXCLUDE_FROM_ALL)
  set(DOTD_HAVE_FFMPEG_BINK 1)
else()
  message(STATUS "dotd: no FFmpeg clone at ${DOTD_FFMPEG_DIR}: Bink videos are not played")
  set(DOTD_HAVE_FFMPEG_BINK 0)
endif()

# ---- our code: floating point must match the PS3 (outputs/decompilation-plan.md section 4) ------
# No contraction, no fast-math; decompiled code also needs wrapping integer arithmetic and no
# strict aliasing. These options apply to dotd targets only, not to SDL.
if(MSVC)
  set(DOTD_COMPILE_OPTIONS /fp:precise /W3 /utf-8 /D_CRT_SECURE_NO_WARNINGS)
else()
  set(DOTD_COMPILE_OPTIONS -ffp-contract=off -fno-fast-math -fno-strict-aliasing -fwrapv)
endif()

# DOTD_PS3_LAYOUT: 1 when pointers are 32-bit (Win32, wasm32), enabling the static_asserts that check
# struct layouts against the PS3 offsets.
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
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

# Game and engine sources (one .cpp per reconstructed original translation unit)
file(GLOB_RECURSE DOTD_GAME_SOURCES CONFIGURE_DEPENDS src/crt/*.cpp src/k2000/*.cpp src/Spyro2008/*.cpp
     src/Renderware/*.cpp)
add_library(dotd_game STATIC ${DOTD_GAME_SOURCES})
dotd_target_setup(dotd_game)
target_link_libraries(dotd_game PUBLIC dotd_platform)

add_executable(dotd src/main.cpp)
dotd_target_setup(dotd)
target_link_libraries(dotd PRIVATE dotd_game)

# ---- tests -------------------------------------------------------------------------------------
enable_testing()
add_executable(ppc_ops_test tests/ppc_ops_test.cpp)
dotd_target_setup(ppc_ops_test)
add_test(NAME ppc_ops COMMAND ppc_ops_test)

add_executable(kclock_test tests/kclock_test.cpp)
dotd_target_setup(kclock_test)
target_link_libraries(kclock_test PRIVATE dotd_game)
add_test(NAME kclock COMMAND kclock_test)

add_executable(platform_test tests/platform_test.cpp)
dotd_target_setup(platform_test)
target_link_libraries(platform_test PRIVATE dotd_platform)
add_test(NAME platform COMMAND platform_test)

add_executable(boot_test tests/boot_test.cpp)
dotd_target_setup(boot_test)
target_link_libraries(boot_test PRIVATE dotd_game)
add_test(NAME boot COMMAND boot_test)
set_tests_properties(boot PROPERTIES SKIP_RETURN_CODE 77)

# Checkpoint C1.5: one test executable per tests/c15/*_test.cpp, each with the boot helper. They need the
# game data for the boot parts (skipped, exit 77, without it).
file(GLOB DOTD_C15_TESTS CONFIGURE_DEPENDS tests/c15/*_test.cpp)
foreach(test_source ${DOTD_C15_TESTS})
  get_filename_component(test_name ${test_source} NAME_WE)
  add_executable(${test_name} ${test_source} tests/c15/boot_helper.cpp)
  dotd_target_setup(${test_name})
  target_link_libraries(${test_name} PRIVATE dotd_game)
  add_test(NAME ${test_name} COMMAND ${test_name})
  set_tests_properties(${test_name} PROPERTIES SKIP_RETURN_CODE 77)
endforeach()
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
set_tests_properties(newgame_pause_scene_test PROPERTIES SKIP_RETURN_CODE 77 ENVIRONMENT "DOTD_NEWGAME_SKIP2=1")
