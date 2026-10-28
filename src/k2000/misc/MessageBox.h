// MessageBox.h - the system message queue and its overlay (original unit MessageBox.cpp, 0x683d8-0x69848;
// not a registered class). The overlay is drawn after the 2D stages by CManager2d::RenderMsgBox: a
// full-screen dim while a save-data request runs, the queued system messages (the newest, in the pulsing
// system text), the loading-video texts, or the Flash message box.
#pragma once
#include <cstdint>

// 0x000687a8 Draw2d_FullScreenColorQuad_maybe: DrawScreenColorQuad over the whole screen in `color`
// (RwRGBA bytes) with the alpha blend (source alpha, inverse source alpha: 0x00c297ec/0x00c297fc +4) and
// no texture.
void Draw2d_FullScreenColorQuad(const uint8_t* color);

// 0x00068de0 CManager2d_GetPulsingTextColor_maybe: once per real-time frame the pulse (a FloatApproach
// 1 -> 0 -> 1 at 1.2 per second, held 3 s at 1) steps; the grey 40 + 215 x pulse, opaque.
void CManager2d_GetPulsingTextColor(uint8_t* color);

// 0x00068ef0 CManager2d_DrawSystemMessageOverlay_maybe
void CManager2d_DrawSystemMessageOverlay();

// The queue's entry count (0x00c5c6c0). Nothing fills the queue before the level (MessageBox_Push 0x69358,
// MessageBox_ProcessQueue 0x68a70: C2), so it stays 0 in the front end.
uint32_t SystemMessage_GetCount();
