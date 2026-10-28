# platform/

Replaces the PS3 SDK surface the game uses (110 imports in 11 modules) and the replaced libraries:
`cell/` (thin shims named after the cell APIs: pad, fs, savedata, sysutil, l10n), `sdl/` (window,
events, input, audio device), `gfx/` (GL 3.3 core / GLES 3.0 backend + PSGL-subset device),
`audio/` (mixer replacing MultiStream, RWS decoding), `video/` (Bink 1), `timing/` (Console and Free
dt modes, replay recorder), `web/` (Emscripten glue).
