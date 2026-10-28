// button.cpp - RW 3.7 tool/2danim/button.c (0x701890-0x702620; Ghidra's "Elem90" is Rt2dButton, 0x90
// bytes): the movie's buttons, their stream reader and the state transition table, ported from the PS3
// library code. See Rt2dAnim.h.
//
// A button: strLabelIndex (its label), objectIndex (its object in the scene of the animation that shows
// it), stateFlag (bit 0 active, bits 1-3 the up/down/over images are children 1.. of the object, bits
// 4.. the transitions it has actions for), buttonState (bit 0 "over", bit 1 the mouse button), and per
// transition the message list to post (-1 none).
#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rt2danim/Rt2dAnimPrivate.h"

// 0x007019e0 Rt2dMaestro_InitDefaultLimits_maybe (_rt2dStateTransTableInit): the 16 entries of
// stateTransTable[over][button][over][button] {transState, upImg, downImg, overImg}. The values are the
// PS3 code's stores (and the live maestros' tables, read 2026-10-17).
Rt2dStateTransData* _rt2dStateTransTableInit(Rt2dStateTransData* table) {
    static const RwInt32 kTable[16][4] = {
        {0, 1, 0, 0},      {0, 1, 0, 0},      {0x10, 0, 0, 1},  {0, 0, 1, 0},
        {0x400, 1, 0, 0},  {0, 1, 0, 0},      {0, 0, 0, 1},     {0xa00, 0, 1, 0},
        {0x20, 1, 0, 0},   {0, 0, 0, 1},      {0, 0, 0, 1},     {0x40, 0, 1, 0},
        {0, 1, 0, 0},      {0x1100, 1, 0, 0}, {0x80, 0, 0, 1},  {0, 0, 1, 0},
    };
    for (int32_t i = 0; i < 16; ++i) {
        table[i].transState = kTable[i][0];
        table[i].buttonUpImg = kTable[i][1];
        table[i].buttonDownImg = kTable[i][2];
        table[i].buttonOverImg = kTable[i][3];
    }
    return table;
}

// 0x00701b18 Rt2dElem90_ApplyButtonStateVisibility_maybe (_rt2dButtonReset_maybe): an active button shows
// its up image and hides the down and over images.
Rt2dButton* _rt2dButtonReset(Rt2dButton* button, Rt2dObject* scene) {
    if ((button->stateFlag & 1u) == 0) return button;
    Rt2dObject* object = Rt2dSceneGetChildByIndex(scene, button->objectIndex);
    RwInt32 child = 1;
    if ((button->stateFlag & 2u) != 0) {
        Rt2dObjectSetVisible(Rt2dSceneGetChildByIndex(object, 1), 1);
        child = 2;
    }
    if ((button->stateFlag & 4u) != 0) {
        Rt2dObjectSetVisible(Rt2dSceneGetChildByIndex(object, child), 0);
        ++child;
    }
    if ((button->stateFlag & 8u) != 0) {
        Rt2dObjectSetVisible(Rt2dSceneGetChildByIndex(object, child), 0);
    }
    return button;
}

// 0x00701c68 Rt2dMaestro_GetElem90_maybe (_rt2dMaestroGetButtonByIndex; no range check)
Rt2dButton* _rt2dMaestroGetButtonByIndex(Rt2dMaestro* maestro, RwInt32 index) {
    return RwSListEntry<Rt2dButton>(maestro->buttons, index);
}

// 0x00701c98 Rt2dMaestro_DestroyElem90List_maybe (_rt2dMaestroDestroyButtons)
Rt2dMaestro* _rt2dMaestroDestroyButtons(Rt2dMaestro* maestro) {
    if (maestro->buttons != nullptr) {
        _rwSListDestroy(maestro->buttons);
        maestro->buttons = nullptr;
    }
    return maestro;
}

// 0x00701cf0 Rt2dMaestro_CreateElem90List_maybe (_rt2dMaestroCreateButtons)
Rt2dMaestro* _rt2dMaestroCreateButtons(Rt2dMaestro* maestro) {
    maestro->buttons = _rwSListCreate(static_cast<RwInt32>(sizeof(Rt2dButton)), kRt2dMaestroHint);
    return maestro->buttons != nullptr ? maestro : nullptr;
}

namespace {
void ButtonClear(Rt2dButton* button) {
    button->strLabelIndex = -1;
    button->objectIndex = -1;
    button->stateFlag = 0;
    button->buttonState = 0;
    for (RwInt32& action : button->actionListForStateTransition) action = -1;
}
}  // namespace

// 0x00702090 _rt2dButtonStreamRead: label, object, stateFlag, then transitionCount action words in one
// read (a count of 0 is a zero-length read, which fails). A new button when none is given.
static Rt2dButton* _rt2dButtonStreamRead(Rt2dMaestro* /*maestro*/, Rt2dButton* button, RwStream* stream,
                                         RwInt32 /*unused*/, RwUInt32 transitionCount) {
    if (button == nullptr) {
        button = static_cast<Rt2dButton*>(RwFreeListAlloc(g_rt2dAnimFreeLists[kRt2dAnimFreeListButton], kRt2dAnimHint));
        if (button == nullptr) return nullptr;
        ButtonClear(button);
    }
    if (RwStreamReadInt32(stream, &button->strLabelIndex, 4) == nullptr) return nullptr;
    if (RwStreamReadInt32(stream, &button->objectIndex, 4) == nullptr) return nullptr;
    if (RwStreamReadInt32(stream, &button->stateFlag, 4) == nullptr) return nullptr;
    if (RwStreamReadInt32(stream, button->actionListForStateTransition, (transitionCount & 0x3fffffffu) << 2) ==
        nullptr)
        return nullptr;
    return button;
}

// 0x007021f8 _rt2dMaestroButtonsStreamRead: {count, a word the button reader ignores, the transition
// count}, then the buttons (each cleared first).
Rt2dMaestro* _rt2dMaestroButtonsStreamRead(Rt2dMaestro* maestro, RwStream* stream) {
    if (maestro == nullptr) {
        maestro = Rt2dMaestroCreate();
        if (maestro == nullptr) return nullptr;
    }
    RwInt32 count = 0, word1 = 0;
    RwUInt32 transitionCount = 0;
    if (RwStreamReadInt32(stream, &count, 4) == nullptr) return nullptr;
    if (RwStreamReadInt32(stream, &word1, 4) == nullptr) return nullptr;
    if (RwStreamReadInt32(stream, &transitionCount, 4) == nullptr) return nullptr;
    if (count < 1) return maestro;
    if (maestro->buttons == nullptr) {
        maestro->buttons = _rwSListCreate(static_cast<RwInt32>(sizeof(Rt2dButton)), kRt2dMaestroHint);
        if (maestro->buttons == nullptr) return nullptr;
    }
    Rt2dButton* button = static_cast<Rt2dButton*>(_rwSListGetNewEntries(maestro->buttons, count, kRt2dMaestroHint));
    if (button == nullptr) return nullptr;
    Rt2dButton* const end = button + count;
    for (; button != end; ++button) {
        ButtonClear(button);
        if (_rt2dButtonStreamRead(maestro, button, stream, word1, transitionCount) == nullptr) return nullptr;
    }
    return maestro;
}
