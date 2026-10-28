// strlabel.cpp - RW 3.7 tool/2danim/strlabel.c (0x700a28-0x701858): string labels (animation, frame,
// button and URL names with their data word) and the byte bucket that holds the names, ported from the
// PS3 library code. See Rt2dAnim.h.
//
// The names are stored in the bucket with their terminating zero (the stream length includes it).
#include <cstring>

#include "Renderware/rt2danim/Rt2dAnimPrivate.h"

// 0x00701748 Rt2dStringBuffer_GetString_maybe (_rt2dByteBucketGetDataByIndex; no range check)
static RwChar* _rt2dByteBucketGetDataByIndex(RwSList* bucket, RwInt32 index) {
    return static_cast<RwChar*>(_rwSListGetEntry(bucket, index));
}

// 0x00701770 Rt2dStringBuffer_Append_maybe (_rt2dByteBucketAddData): size bytes at the end (copied from
// data when given); their index, or -1.
static RwInt32 _rt2dByteBucketAddData(RwSList* bucket, const void* data, RwInt32 size) {
    const RwInt32 index = _rwSListGetNumEntries(bucket);
    void* bytes = _rwSListGetNewEntries(bucket, size, kRt2dAnimHint);
    if (bytes == nullptr) return -1;
    if (data != nullptr) std::memcpy(bytes, data, static_cast<size_t>(size));
    return index;
}

// 0x00701830 Rt2dStringBuffer_Destroy_maybe (_rt2dByteBucketDestroy)
RwBool _rt2dByteBucketDestroy(RwSList* bucket) {
    _rwSListDestroy(bucket);
    return 1;
}

// 0x00701858 Rt2dStringBuffer_Create_maybe (_rt2dByteBucketCreate)
RwSList* _rt2dByteBucketCreate() { return _rwSListCreate(1, kRt2dAnimHint); }

// 0x00700ae8 Rt2dMaestro_GetLabelString_maybe (Rt2dMaestroGetStringLabelName)
const RwChar* Rt2dMaestroGetStringLabelName(Rt2dMaestro* maestro, Rt2dStringLabel* strLabel) {
    return _rt2dByteBucketGetDataByIndex(maestro->byteBucket, strLabel->nameIndex);
}

// 0x00700b20 Rt2dMaestro_GetStringLabelByIndex_maybe (Rt2dMaestroGetStringLabelByIndex): null without
// labels or for index >= the count (a negative index is not checked).
Rt2dStringLabel* Rt2dMaestroGetStringLabelByIndex(Rt2dMaestro* maestro, RwInt32 index) {
    if (maestro->labels == nullptr) return nullptr;
    const RwInt32 count = _rwSListGetNumEntries(maestro->labels);
    if (count <= 0 || count <= index) return nullptr;
    return RwSListArray<Rt2dStringLabel>(maestro->labels) + index;
}

// 0x00700ba0 Rt2dMaestro_FindStringLabel_maybe (Rt2dMaestroFindStringLabel): the first label of the type
// whose name equals lookupName (RWEngine string function +0xe8, strcmp); its index in *index when given.
Rt2dStringLabel* Rt2dMaestroFindStringLabel(Rt2dMaestro* maestro, Rt2dStringLabelType entityType,
                                            const RwChar* lookupName, RwInt32* index) {
    if (maestro->labels == nullptr) return nullptr;
    const RwInt32 count = _rwSListGetNumEntries(maestro->labels);
    if (count <= 0) return nullptr;
    Rt2dStringLabel* label = RwSListArray<Rt2dStringLabel>(maestro->labels);
    for (RwInt32 i = 0; i < count; ++i, ++label) {
        const RwChar* name = _rt2dByteBucketGetDataByIndex(maestro->byteBucket, label->nameIndex);
        if (label->entityType != static_cast<RwUInt32>(entityType)) continue;
        if (std::strcmp(name, lookupName) != 0) continue;
        if (index != nullptr) *index = i;
        return label;
    }
    return nullptr;
}

// 0x00700ce8 Rt2dMaestro_CreateStringLabelList_maybe (_rt2dMaestroCreateStringLabels)
Rt2dMaestro* _rt2dMaestroCreateStringLabels(Rt2dMaestro* maestro) {
    maestro->labels = _rwSListCreate(static_cast<RwInt32>(sizeof(Rt2dStringLabel)), kRt2dAnimHint);
    return maestro->labels != nullptr ? maestro : nullptr;
}

// 0x007010c0 Rt2dMaestro_DestroyStringLabelList_maybe (_rt2dMaestroDestroyStringLabels)
Rt2dMaestro* _rt2dMaestroDestroyStringLabels(Rt2dMaestro* maestro) {
    if (maestro->labels == nullptr) return maestro;
    const RwInt32 count = _rwSListGetNumEntries(maestro->labels);
    if (count > 0) {
        Rt2dStringLabel* label = RwSListArray<Rt2dStringLabel>(maestro->labels);
        Rt2dStringLabel* const end = label + count;
        for (; label != end; ++label) {
            label->userData = nullptr;
            label->entityType = rt2dANIMLABELTYPENONE;
            label->nameIndex = -1;
            label->internalData = nullptr;
        }
    }
    _rwSListDestroy(maestro->labels);
    maestro->labels = nullptr;
    return maestro;
}

// 0x00701278 _rt2dStringLabelStreamRead: the name length and name (into the byte bucket; length < 1:
// no name, index -1), then entityType and the data word. A new label from the free list when none is
// given.
static Rt2dStringLabel* _rt2dStringLabelStreamRead(Rt2dMaestro* maestro, Rt2dStringLabel* label, RwStream* stream) {
    if (label == nullptr) {
        label = static_cast<Rt2dStringLabel*>(
            RwFreeListAlloc(g_rt2dAnimFreeLists[kRt2dAnimFreeListStringLabel], kRt2dAnimHint));
        if (label == nullptr) return nullptr;
        label->userData = nullptr;
        label->nameIndex = -1;
        label->entityType = rt2dANIMLABELTYPENONE;
        label->internalData = nullptr;
    }
    RwInt32 length = 0;
    if (RwStreamReadInt32(stream, &length, 4) == nullptr) return nullptr;
    if (length < 1) {
        label->nameIndex = -1;
    } else {
        const RwInt32 index = _rt2dByteBucketAddData(maestro->byteBucket, nullptr, length);
        if (index == -1) return nullptr;
        RwChar* name = _rt2dByteBucketGetDataByIndex(maestro->byteBucket, index);
        if (RwStreamRead(stream, name, static_cast<RwUInt32>(length)) != static_cast<RwUInt32>(length)) return nullptr;
        label->nameIndex = index;
    }
    if (RwStreamReadInt32(stream, &label->entityType, 4) == nullptr) return nullptr;
    RwInt32 data = 0;
    if (RwStreamReadInt32(stream, &data, 4) == nullptr) return nullptr;
    label->internalData = Rt2dWordAsPointer(data);  // the PS3 reads the word into the field
    return label;
}

// 0x00701410 _rt2dMaestroStringLabelsStreamRead: the count, then the labels (each cleared first).
Rt2dMaestro* _rt2dMaestroStringLabelsStreamRead(Rt2dMaestro* maestro, RwStream* stream) {
    RwInt32 count = 0;
    if (RwStreamReadInt32(stream, &count, 4) == nullptr) return nullptr;
    if (count < 1) return maestro;
    if (maestro->labels == nullptr) {
        maestro->labels = _rwSListCreate(static_cast<RwInt32>(sizeof(Rt2dStringLabel)), kRt2dAnimHint);
        if (maestro->labels == nullptr) return nullptr;
    }
    Rt2dStringLabel* label =
        static_cast<Rt2dStringLabel*>(_rwSListGetNewEntries(maestro->labels, count, kRt2dAnimHint));
    if (label == nullptr) return nullptr;
    Rt2dStringLabel* const end = label + count;
    for (; label != end; ++label) {
        label->entityType = rt2dANIMLABELTYPENONE;
        label->nameIndex = -1;
        label->internalData = nullptr;
        label->userData = nullptr;
        if (_rt2dStringLabelStreamRead(maestro, label, stream) == nullptr) return nullptr;
    }
    return maestro;
}
