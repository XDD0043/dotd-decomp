# dotd/cmake/FetchDeps.cmake: the third-party sources the build needs, fetched at configure time when they are not
# already there, so a fresh copy of the repository (a git clone without submodules, or a downloaded zip) builds with
# one command. Only source archives are fetched, each checked against its SHA-256; everything is compiled here with
# the same compiler as the game, so there is no prebuilt binary and no ABI to match.
#
#   dotd_fetch_source(NAME URL SHA256 SUBDIR CHECK_FILE OUT_VAR)
#     OUT_VAR (a directory) is left alone when it already holds CHECK_FILE (a submodule, a clone, a -D path). Else the
#     archive is downloaded once to thirdparty/.fetched/ (kept for the next configure and for other build folders),
#     extracted there, and OUT_VAR is set to the extracted SUBDIR for this configure.
#
# DOTD_FETCH_DEPS=OFF turns the downloads off (offline machines: put the sources in place by hand,
# thirdparty/README.md).
option(DOTD_FETCH_DEPS "Download the SDL and FFmpeg source archives when they are missing" ON)
set(DOTD_FETCH_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/.fetched")

function(dotd_fetch_source name url sha256 subdir check_file out_var)
  if(EXISTS "${${out_var}}/${check_file}")
    return()
  endif()
  set(dest "${DOTD_FETCH_ROOT}/${subdir}")
  if(NOT EXISTS "${dest}/${check_file}")
    if(NOT DOTD_FETCH_DEPS)
      return()
    endif()
    get_filename_component(archive_name "${url}" NAME)
    set(archive "${DOTD_FETCH_ROOT}/${archive_name}")
    if(EXISTS "${archive}")
      file(SHA256 "${archive}" have)
      if(NOT have STREQUAL sha256)
        file(REMOVE "${archive}")
      endif()
    endif()
    if(NOT EXISTS "${archive}")
      message(STATUS "dotd: downloading the ${name} source (${url})")
      file(DOWNLOAD "${url}" "${archive}.part" EXPECTED_HASH SHA256=${sha256} TLS_VERIFY ON STATUS status)
      list(GET status 0 code)
      if(NOT code EQUAL 0)
        list(GET status 1 why)
        file(REMOVE "${archive}.part")
        message(WARNING "dotd: could not download the ${name} source: ${why}")
        return()
      endif()
      file(RENAME "${archive}.part" "${archive}")
    endif()
    message(STATUS "dotd: extracting ${archive_name}")
    file(REMOVE_RECURSE "${dest}")
    file(ARCHIVE_EXTRACT INPUT "${archive}" DESTINATION "${DOTD_FETCH_ROOT}")
    if(NOT EXISTS "${dest}/${check_file}")
      message(WARNING "dotd: ${archive_name} did not hold ${subdir}/${check_file}")
      return()
    endif()
  endif()
  set(${out_var} "${dest}" PARENT_SCOPE)
endfunction()
