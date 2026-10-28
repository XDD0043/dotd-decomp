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

#endif /* DOTD_FFMPEG_CONFIG_COMPONENTS_H */
