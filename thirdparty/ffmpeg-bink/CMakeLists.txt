# ffmpeg-bink: a static build of FFmpeg's Bink video and Bink audio decoders (libavcodec bink, binkaudio_dct,
# binkaudio_rdft) and the ATRAC3 decoder (speech) with the minimum of libavcodec/libavutil they need. FFmpeg is LGPL-2.1-or-later: the
# source comes from a shallow clone of the official repository (see ../README.md), built here from
# source with the handwritten configuration in include/ (no configure script, no assembly, no threads).
#
# LGPL note: this static link is for a local, non-distributed build. A distributed binary must either link
# FFmpeg dynamically or ship what LGPL-2.1 section 6 asks for (the FFmpeg source used, these build files,
# and the object files of the program so it can be relinked with a modified FFmpeg).
#
# Input: FFMPEG_BINK_SOURCE_DIR = the FFmpeg clone (tag n7.1.2). Output: target ffbink.
cmake_minimum_required(VERSION 3.20)

set(_ff "${FFMPEG_BINK_SOURCE_DIR}")

set(DOTD_FFMPEG_BINK_SOURCES
  # libavcodec: the decoders
  libavcodec/bink.c libavcodec/binkdsp.c libavcodec/binkaudio.c libavcodec/wma_freqs.c
  libavcodec/atrac3.c libavcodec/atrac.c  # ATRAC3: the levels' SPEECH/*.RWS streams
  libavcodec/blockdsp.c libavcodec/hpeldsp.c libavcodec/vlc.c libavcodec/bitstream.c libavcodec/mathtables.c
  # libavcodec: the core avcodec_send_packet / avcodec_receive_frame need
  libavcodec/allcodecs.c libavcodec/avcodec.c libavcodec/decode.c libavcodec/encode.c libavcodec/bsf.c
  libavcodec/bitstream_filters.c libavcodec/bsf/null.c libavcodec/codec_desc.c libavcodec/codec_par.c
  libavcodec/options.c libavcodec/packet.c libavcodec/get_buffer.c libavcodec/utils.c libavcodec/profiles.c
  libavcodec/version.c libavcodec/refstruct.c libavcodec/threadprogress.c libavcodec/lcevcdec.c
  # libavutil
  libavutil/avstring.c libavutil/bprint.c libavutil/buffer.c libavutil/channel_layout.c libavutil/cpu.c
  libavutil/crc.c libavutil/dict.c libavutil/display.c libavutil/error.c libavutil/eval.c libavutil/fifo.c
  libavutil/frame.c libavutil/hwcontext.c libavutil/imgutils.c libavutil/intmath.c libavutil/log.c
  libavutil/log2_tab.c libavutil/mathematics.c libavutil/mem.c libavutil/opt.c libavutil/parseutils.c
  libavutil/pixdesc.c libavutil/random_seed.c libavutil/rational.c libavutil/reverse.c libavutil/samplefmt.c
  libavutil/time.c libavutil/timecode.c libavutil/utils.c libavutil/version.c libavutil/avsscanf.c libavutil/sha.c
  libavutil/float_dsp.c libavutil/tx.c libavutil/tx_float.c libavutil/tx_double.c libavutil/tx_int32.c
  libavutil/mastering_display_metadata.c libavutil/hdr_dynamic_metadata.c libavutil/spherical.c
  libavutil/stereo3d.c libavutil/ambient_viewing_environment.c libavutil/downmix_info.c
  libavutil/film_grain_params.c libavutil/video_enc_params.c libavutil/csp.c
)
list(TRANSFORM DOTD_FFMPEG_BINK_SOURCES PREPEND "${_ff}/")

add_library(ffbink STATIC ${DOTD_FFMPEG_BINK_SOURCES})
set_target_properties(ffbink PROPERTIES LINKER_LANGUAGE C)
# FFmpeg's bsf/ sources include their libavcodec headers by bare name.
set_source_files_properties("${_ff}/libavcodec/bsf/null.c" PROPERTIES INCLUDE_DIRECTORIES "${_ff}/libavcodec")
target_include_directories(ffbink
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include" "${_ff}"
  INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include" "${_ff}")
target_compile_definitions(ffbink PRIVATE HAVE_AV_CONFIG_H=1 _USE_MATH_DEFINES _CRT_SECURE_NO_WARNINGS
  _CRT_NONSTDC_NO_WARNINGS)
if(MSVC)
  # MSVC has no <stdatomic.h> without /experimental:c11atomics; FFmpeg ships a Win32 replacement.
  target_include_directories(ffbink PRIVATE "${_ff}/compat/atomics/win32")
  # FFmpeg relies on dead-code elimination of `if (CONFIG_X)` / `if (ARCH_X)` branches, so it is always
  # optimised (also in Debug). /RTC1 is incompatible with /O2 and is removed for this directory only.
  foreach(_flag /RTC1 /Od /Ob0)
    string(REPLACE "${_flag}" "" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
  endforeach()
  target_compile_options(ffbink PRIVATE /O2 /std:c11 /W0 /wd4028 /wd4244 /wd4267 /wd4996)
else()
  target_compile_options(ffbink PRIVATE -O2 -std=c11 -w)
endif()
