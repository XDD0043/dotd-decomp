/* config_components.h - handwritten for the dotd Bink-only FFmpeg build: the only components are the
 * Bink video and Bink audio decoders, ATRAC3 (speech) and the null bitstream filter (decode.c's default). */
#ifndef DOTD_FFMPEG_CONFIG_COMPONENTS_H
#define DOTD_FFMPEG_CONFIG_COMPONENTS_H

#define CONFIG_BINK_DECODER 1
#define CONFIG_BINKAUDIO_DCT_DECODER 1
#define CONFIG_BINKAUDIO_RDFT_DECODER 1
#define CONFIG_ATRAC3_DECODER 1
#define CONFIG_ATRAC3AL_DECODER 1
#define CONFIG_NULL_BSF 1
/* VP9 (the web pack's re-encoded videos): the software decoder only. */
#define CONFIG_VP9_DECODER 1
#define CONFIG_VORBIS_DECODER 1 /* the web pack's re-encoded music */
#define CONFIG_VP9_SUPERFRAME_SPLIT_BSF 1
#define CONFIG_VP9_DXVA2_HWACCEL 0
#define CONFIG_VP9_D3D11VA_HWACCEL 0
#define CONFIG_VP9_D3D11VA2_HWACCEL 0
#define CONFIG_VP9_D3D12VA_HWACCEL 0
#define CONFIG_VP9_NVDEC_HWACCEL 0
#define CONFIG_VP9_VAAPI_HWACCEL 0
#define CONFIG_VP9_VDPAU_HWACCEL 0
#define CONFIG_VP9_VIDEOTOOLBOX_HWACCEL 0

#endif /* DOTD_FFMPEG_CONFIG_COMPONENTS_H */
