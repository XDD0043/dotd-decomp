// Reconstructed original translation unit: 0xc1b50-0xc2848 (GAME_TOC1, main_toc1), 5 functions, 2 live.
// Primary owner: Skin (not a registered class)
// Other owners: RpMeshHeader (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xc1b50  Skin_BlendVerticesSoftware_maybe  [dead: only caller 0xc2848]
//   [ ] 0xc2160  RpMeshHeader_BuildFromTriangles_maybe  [dead]
//   [ ] 0xc2278  Skin_ComputeBoneMatrixPalette_maybe  [dead: only caller 0xc2848]
//
// Animation checkpoint, step 5: both "live" functions are called only by Atomic_RenderIm3DSoftwareSkinned_maybe 0xc2848
// (k2000/render/Atomic.cpp), whose function descriptor 0xb4d418 nothing references (no TOC slot, vtable or data word
// in 0xb00000..0xc40000 holds it; Ghidra lists no reference to it). The game skins on the GPU only
// (BuildPSGLSkinBoneMatrixPalette 0x775478 through the bone palette uniform, Renderware/rpskin/RpSkin.cpp).
//   [ ] 0xc2488  FUN_000c2488  [dead]
//   [ ] 0xc2628  FUN_000c2628  [dead]
