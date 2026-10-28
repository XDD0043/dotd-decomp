/* codec_list.c - handwritten for the dotd Bink-only FFmpeg build (included by libavcodec/allcodecs.c). */
static const FFCodec * const codec_list[] = {
    &ff_bink_decoder,
    &ff_binkaudio_dct_decoder,
    &ff_binkaudio_rdft_decoder,
    &ff_atrac3_decoder,
    &ff_atrac3al_decoder,
    NULL };
