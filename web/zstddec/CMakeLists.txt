# zstddec: the zstd decoder as its own small wasm module (zstddec.js + zstddec.wasm next to index.html) for the
# page's download worker (../pack-worker.js). No threads: dotd/CMakeLists.txt adds this folder before it turns
# -pthread on for everything else. The source is a shallow clone of zstd, see thirdparty/README.md.
set(DOTD_ZSTD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/zstd" CACHE PATH "zstd source tree (v1.5.7)")
if(NOT EXISTS "${DOTD_ZSTD_DIR}/lib/zstd.h")
  message(STATUS "dotd: no zstd clone at ${DOTD_ZSTD_DIR}: the web build's download mode is not built")
  return()
endif()
file(GLOB DOTD_ZSTD_SOURCES "${DOTD_ZSTD_DIR}/lib/common/*.c" "${DOTD_ZSTD_DIR}/lib/decompress/*.c")
add_executable(zstddec zstddec.c ${DOTD_ZSTD_SOURCES})
target_include_directories(zstddec PRIVATE "${DOTD_ZSTD_DIR}/lib")
target_compile_definitions(zstddec PRIVATE ZSTD_DISABLE_ASM=1)
target_compile_options(zstddec PRIVATE -O3)
set_target_properties(zstddec PROPERTIES SUFFIX ".js" RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
target_link_options(zstddec PRIVATE
  -O3 -sMODULARIZE=1 -sEXPORT_NAME=DotdZstd -sENVIRONMENT=worker -sFILESYSTEM=0
  -sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=16MB -sMAXIMUM_MEMORY=2GB
  "-sEXPORTED_FUNCTIONS=['_malloc','_free','_dotd_zstd_begin','_dotd_zstd_feed','_dotd_zstd_written','_dotd_zstd_error']"
  "-sEXPORTED_RUNTIME_METHODS=['HEAPU8','UTF8ToString']")
