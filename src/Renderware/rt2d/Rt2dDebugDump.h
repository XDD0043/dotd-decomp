// Rt2dDebugDump.h - debug-only JSON dump of the native Rt2d Maestro state (no PS3 counterpart).
//
// The native side of checkpoint C1.5's Maestro check. It walks the remake's Rt2dMaestro structs
// (Rt2dTypes.h; in the x86 parity build their layout is the PS3's) into the same JSON shape as
// work/maestro_live.py writes from RPCS3's memory, so work/maestro_diff.py can compare the two field by
// field. tests/c15/verify_test.cpp writes it when DOTD_DUMP_MAESTRO=path is set.
//
// Shape ("format": "maestro-dump-1"):
//   {"format", "source": "native" | "rpcs3", "tag", "time", "frame", "frameAfter",
//    "uis": [{"index", "flags44", "sceneVisible", "drawn", "maestro": MAESTRO | null}]}
//   MAESTRO: the header (flag, version, messageHandler (set or not), prevMouse, invWinH/W, winAspectRatio,
//     currAnimIndex, bbox, stateTransTable (64 words in memory order)), byteBucketSize, labels (with their
//     names from the byte bucket), scene (the object tree), buttons, messageList, messageStore,
//     messageQueue ({top, bot, size, pending: the entries [top, bot)}), animations (anim nodes: anim with
//     the keyframe schedule and each keyframe list's compact data decoded into sets, props (scene,
//     directory, labels, sceneCurrentState), celList, parent, posInParentScene) and shapeReps.
//   An object: path ("s" the root scene, "s/3/0" child 0 of child 3), type, depth, flag, MTM, LTM,
//     colorMult, colorOffs, and per type: scene (objectCount, isDirtyDepths, children, depths), shape
//     (rep "#k", colorCache per node, atomic), pick region (pickPath, bbox, transformation), object string
//     (text, maxLength, brush, height, font name, wideChars, justiftype, boxwidth); dataTail = the
//     non-zero union words past the type's struct (parity build only).
//   Values: floats are "f:xxxxxxxx" (their bits); words shown as flags are "%08x" strings; RwRGBA is
//   "rrggbbaa"; pointers are structural references ("@s/1/2" an object of the tree, "#k" a shape rep,
//   an index into the owning array, null, or "@ext" when the pointer is not part of the walk); RpAtomic,
//   RpGeometry, RpMaterial, RwTexture and the message handler are true/false.
//
// Native assumptions (where the port chooses a representation): object-string text in Rt2dFontChar
// (host-order 2-byte characters) when the font's flag has bit 1, else bytes; the keyframe lists' compact
// data as Rt2dKeyFrameSet records followed by Rt2dKeyFrameTransform / Rt2dKeyFrameColor (colorOffs,
// then colorMult) / Rt2dKeyFrameShow / Rt2dKeyFrameMorph by the set's flag (0x20 ends), the PS3 layout
// of 0x006face8 _rt2dKeyFrameListStreamReadTo_maybe; morph source/destination there as the stream's
// indices (stored in the pointer fields).
#pragma once
#include <cstdint>
#include <string>

struct Rt2dMaestro;

// One CKFlashUI as the dump lists it. The K-side fields come from the caller (verify_test.cpp reads
// them from CKFlashUI): flags44 = CKFlashUI+0x44, sceneVisible = Rt2dObjectIsVisible(scene) (flag & 4),
// drawn = DrawFlashUISceneAndSynchronizeWidgets' (0x6f280) condition.
struct Rt2dDebugDumpUI {
    int32_t index;
    uint32_t flags44;
    bool sceneVisible;
    bool drawn;
    const Rt2dMaestro* maestro;  // may be null
};

// The JSON object of one maestro (MAESTRO above); "null" for a null maestro.
std::string Rt2dDebugDumpMaestro(const Rt2dMaestro* maestro);

// Rt2dObjectIsVisible's test on a maestro's scene (flag & 4); false without a maestro or scene.
bool Rt2dDebugDumpSceneVisible(const Rt2dMaestro* maestro);

// Writes the whole dump to path (plain JSON). False when the file cannot be written.
bool Rt2dDebugDumpWrite(const char* path, const char* tag, uint32_t frame, const Rt2dDebugDumpUI* uis,
                        int32_t count);
