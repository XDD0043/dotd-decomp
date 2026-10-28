// cel.cpp - RW 3.7 tool/2danim/cel.c (0x702648-0x703a60; Ghidra's "Rt2dAnimNodeGroup(List)" is
// Rt2dCel(List)): per keyframe of an animation, its label, the buttons it shows and the message list it
// posts when reached. Ported from the PS3 library code. See Rt2dAnim.h.
#include "Renderware/rt2danim/Rt2dAnimPrivate.h"

// 0x00702648 Rt2dMaestro_GetAnimNodeGroupValue_maybe: the label index of button buttonIndex of cel
// celIndex; null (and *strLabelIndex untouched) when an entry address is null.
Rt2dCelList* _rt2dCelListGetButtonLabelIndex(Rt2dMaestro* maestro, Rt2dCelList* celList, RwInt32 celIndex,
                                             RwInt32 buttonIndex, RwInt32* strLabelIndex) {
    Rt2dCel* cel = RwSListEntry<Rt2dCel>(celList->cel, celIndex);
    if (cel == nullptr) return nullptr;
    RwInt32* index = RwSListEntry<RwInt32>(cel->buttonIndices, buttonIndex);
    if (index == nullptr) return nullptr;
    Rt2dButton* button = RwSListEntry<Rt2dButton>(maestro->buttons, *index);
    if (button == nullptr) return nullptr;
    *strLabelIndex = button->strLabelIndex;
    return celList;
}

// 0x00702850 Rt2dAnimNodeGroupList_GetByIndex_maybe (_rt2dCelListGetCelByIndex): null without a cel
// list storage pointer; otherwise the array (null while empty) plus index entries, unchecked.
Rt2dCel* _rt2dCelListGetCelByIndex(Rt2dCelList* celList, RwInt32 index) {
    if (celList->cel == nullptr) return nullptr;
    const uintptr_t array = reinterpret_cast<uintptr_t>(_rwSListGetArray(celList->cel));
    return reinterpret_cast<Rt2dCel*>(array + static_cast<uintptr_t>(static_cast<intptr_t>(index)) * sizeof(Rt2dCel));
}

// 0x00702c68 _rt2dCelStreamRead: label, cel index, the button count and indices, the message list.
static Rt2dCel* _rt2dCelStreamRead(Rt2dMaestro* /*maestro*/, Rt2dCel* cel, RwStream* stream) {
    if (RwStreamReadInt32(stream, &cel->strLabelIndex, 4) == nullptr) return nullptr;
    if (RwStreamReadInt32(stream, &cel->celIndex, 4) == nullptr) return nullptr;
    RwInt32 count = 0;
    if (RwStreamReadInt32(stream, &count, 4) == nullptr) return nullptr;
    if (count > 0) {
        if (cel->buttonIndices == nullptr) {
            cel->buttonIndices = _rwSListCreatePreallocated(static_cast<RwInt32>(sizeof(RwInt32)), count, kRt2dAnimHint);
            if (cel->buttonIndices == nullptr) return nullptr;
        }
        void* indices = _rwSListGetNewEntries(cel->buttonIndices, count, kRt2dAnimHint);
        if (indices == nullptr) return nullptr;
        if (RwStreamReadInt32(stream, indices, static_cast<RwUInt32>(count) << 2) == nullptr) return nullptr;
    }
    if (RwStreamReadInt32(stream, &cel->messageListIndex, 4) == nullptr) return nullptr;
    return cel;
}

// 0x007034c8 Rt2dAnimNodeGroupList_Destroy_maybe (_rt2dCelListDestroy)
RwBool _rt2dCelListDestroy(Rt2dCelList* celList) {
    if (celList->cel != nullptr) {
        const RwInt32 count = _rwSListGetNumEntries(celList->cel);
        Rt2dCel* cel = RwSListArray<Rt2dCel>(celList->cel);
        if (count > 0 && cel != nullptr) {
            for (RwInt32 i = 0; i < count; ++i, ++cel) {
                if (cel->buttonIndices != nullptr) _rwSListDestroy(cel->buttonIndices);
                cel->messageListIndex = -1;
                cel->buttonIndices = nullptr;
                cel->strLabelIndex = -1;
                cel->celIndex = -1;
            }
        }
        _rwSListDestroy(celList->cel);
        celList->cel = nullptr;
    }
    celList->flag = 0;
    RwFreeListFree(g_rt2dAnimFreeLists[kRt2dAnimFreeListCelList], celList);
    return 1;
}

// 0x00703600 Rt2dAnimNodeGroupList_Create_maybe (_rt2dCelListCreate): flag 1.
Rt2dCelList* _rt2dCelListCreate() {
    Rt2dCelList* celList =
        static_cast<Rt2dCelList*>(RwFreeListAlloc(g_rt2dAnimFreeLists[kRt2dAnimFreeListCelList], kRt2dAnimHint));
    if (celList == nullptr) return nullptr;
    celList->cel = _rwSListCreate(static_cast<RwInt32>(sizeof(Rt2dCel)), kRt2dAnimHint);
    if (celList->cel == nullptr) {
        celList->flag = 0;
        RwFreeListFree(g_rt2dAnimFreeLists[kRt2dAnimFreeListCelList], celList);
        return nullptr;
    }
    celList->flag = 1;
    return celList;
}

// 0x00703838 _rt2dCelListStreamRead: the count, then the cels (each cleared, with an empty button list).
// A new list (flag 0) when none is given.
Rt2dCelList* _rt2dCelListStreamRead(Rt2dMaestro* maestro, Rt2dCelList* celList, RwStream* stream) {
    if (celList == nullptr) {
        celList = static_cast<Rt2dCelList*>(
            RwFreeListAlloc(g_rt2dAnimFreeLists[kRt2dAnimFreeListCelList], kRt2dAnimHint));
        if (celList == nullptr) return nullptr;
        celList->cel = _rwSListCreate(static_cast<RwInt32>(sizeof(Rt2dCel)), kRt2dAnimHint);
        if (celList->cel == nullptr) {
            celList->flag = 0;
            RwFreeListFree(g_rt2dAnimFreeLists[kRt2dAnimFreeListCelList], celList);
            return nullptr;
        }
        celList->flag = 0;
    }
    RwInt32 count = 0;
    if (RwStreamReadInt32(stream, &count, 4) == nullptr) return nullptr;
    if (count > 0) {
        Rt2dCel* cel = static_cast<Rt2dCel*>(_rwSListGetNewEntries(celList->cel, count, kRt2dAnimHint));
        if (cel == nullptr) return nullptr;
        for (RwInt32 i = 0; i < count; ++i, ++cel) {
            cel->strLabelIndex = -1;
            cel->celIndex = -1;
            cel->messageListIndex = -1;
            cel->buttonIndices = _rwSListCreate(static_cast<RwInt32>(sizeof(RwInt32)), kRt2dAnimHint);
            if (_rt2dCelStreamRead(maestro, cel, stream) == nullptr) return nullptr;
        }
    }
    return celList;
}
