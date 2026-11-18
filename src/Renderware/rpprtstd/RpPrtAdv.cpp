// RpPrtAdv.cpp - the advanced emitter properties (RpPrtAdv) and the emitter class callback builder DotD
// installs, ported from the PS3 library code (TOC 0xc25974, 0x6ef3b0-0x6f5df0): the create, stream read
// and copy callbacks of each property; their emit / update callbacks are in RpPrtAdvRuntime.cpp. STUB(C2):
// the stream write / size callbacks (slots 8 / 9) are not ported (nothing in the game writes RenderWare
// streams).
//
//   [x] 0x6ef410  RpPrtStdPClass_BuildStdCallBackArray_maybe
//   [x] 0x6ef7c8  RpPrtStdEClass_BuildStdCallBackArray_maybe
//   [x] 0x6f0f08  PrtStdEmitterProp1000008_StreamRead_maybe
//   [x] 0x6f1010  PrtStdEmitterProp1000008_Copy_maybe
//   [x] 0x6f17b0  PrtStdEmitterProp1000007_StreamRead_maybe
//   [x] 0x6f18c0  PrtStdEmitterProp1000007_Copy_maybe
//   [x] 0x6f20a0  PrtStdEmitterProp1000006_Init_maybe
//   [x] 0x6f23e8  PrtStdEmitterProp1000006_StreamRead_maybe
//   [x] 0x6f25a0  PrtStdEmitterProp1000006_Copy_maybe
//   [x] 0x6f2fb0  PrtStdEmitterProp1000001_StreamRead_maybe
//   [x] 0x6f3078  PrtStdEmitterProp1000001_Copy_maybe
//   [x] 0x6f38f0  PrtStdEmitterProp1000002_3_5_Init_maybe
//   [x] 0x6f3d58  PrtStdEmitterProp1000002_3_5_StreamRead_maybe
//   [x] 0x6f3fd0  PrtStdEmitterProp1000002_3_5_Copy_maybe
//   [x] 0x6f54e0  PrtStdEmitterProp1000004_Init_maybe
//   [x] 0x6f56c8  PrtStdEmitterProp1000004_StreamRead_maybe
//   [x] 0x6f57d0  PrtStdEmitterProp1000004_Copy_maybe
#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpprtstd/RpPrtStdInternal.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"

namespace rpprtstd {

namespace {

// The property `propID` of `emitter` and its rounded table size (RpPrtStdPropTabGetPropIndex, then
// RpPrtStdPropTabGetInfo_maybe's size array), or null.
uint8_t* PropertyWithSize(RpPrtStdEmitter* emitter, int32_t propID, uint32_t* size) {
    const RpPrtStdPropertyTable* table = emitter->emtClass->propTab;
    const int32_t index = RpPrtStdPropTabGetPropIndex(table, propID);
    *size = static_cast<uint32_t>(table->propSize[index]);
    return PropertyAt(emitter, table->propOffset[index]);
}

// A keyframe list property's create (0x6f38f0, 0x6f54e0): the count from the property's size, the self
// pointer to the keys at `keys`, the stride words (4, then the offsets of the arrays after the times).
void InitKeys(uint8_t* prop, uint32_t keys, uint32_t count) {
    StoreSelfPointer(prop + 4, prop + keys);
    WordAt(prop, 0) = count;
    WordAt(prop, 8) = 4;
}

// The stride words a version < 3 stream gets again in 0x6f3d58, from the streamed key count (the time
// offset 4, then the particle arrays after the n times): colour start / delta (16 bytes per key), texcoords
// UV0 start / delta and UV1 start / delta (8 each), size start / delta (8).
void LegacyStrides(uint8_t* prop, int32_t propID, uint32_t count) {
    const uint32_t first = count * 4 + 4;
    WordAt(prop, 8) = 4;
    WordAt(prop, 0xc) = first;
    if (propID == rpPRTADVPROPERTYCODEEMITTERPRTMULTICOLOR) {
        WordAt(prop, 0x10) = first + count * 0x10;
    } else if (propID == rpPRTADVPROPERTYCODEEMITTERPRTMULTITEXCOORDS) {
        const uint32_t step = count * 8;
        WordAt(prop, 0x10) = first + step;
        WordAt(prop, 0x14) = first + step + step;
        WordAt(prop, 0x18) = first + step + step + step;
    } else {
        WordAt(prop, 0x10) = first + count * 8;
    }
}

}  // namespace

// 0x006f20a0 PrtStdEmitterProp1000006_Init_maybe: the points follow the header, the directions the points;
// the capacity from the property's size (64 in DotD's data).
RpPrtStdEmitter* PointListInit(RpAtomic*, RpPrtStdEmitter* emitter, void*) {
    uint32_t size = 0;
    uint8_t* prop = PropertyWithSize(emitter, rpPRTADVPROPERTYCODEEMITTERPOINTLIST, &size);
    RpPrtAdvEmtPointList* list = reinterpret_cast<RpPrtAdvEmtPointList*>(prop);
    list->random = 0;
    list->useDirection = 0;
    list->lastPoint = 0;
    list->pointList = reinterpret_cast<RwV3d*>(list + 1);
    const uint32_t count = (size - static_cast<uint32_t>(sizeof(RpPrtAdvEmtPointList))) / 0x18u;
    list->numPoint = count;
    list->directionList = list->pointList + count;
    return emitter;
}

// 0x006f23e8 PrtStdEmitterProp1000006_StreamRead_maybe: the count, then four flags: use direction, random,
// points present (else the point pointer is cleared), directions present (else cleared).
RpPrtStdEmitter* PointListStreamRead(RpAtomic*, RpPrtStdEmitter* emitter, void* data) {
    Stream* stream = static_cast<Stream*>(data);
    const int32_t offset = EmitterPropOffset(emitter, rpPRTADVPROPERTYCODEEMITTERPOINTLIST);
    if (offset < 0) return emitter;
    RpPrtAdvEmtPointList* list = reinterpret_cast<RpPrtAdvEmtPointList*>(PropertyAt(emitter, offset));
    stream->ReadWords(&list->numPoint, 4);
    list->useDirection = stream->ReadInt32() == 1 ? 1 : 0;
    list->random = stream->ReadInt32() == 1 ? 1 : 0;
    if (stream->ReadInt32() == 1) {
        stream->ReadWords(list->pointList, list->numPoint * 12);
    } else {
        list->pointList = nullptr;
    }
    if (stream->ReadInt32() == 1) {
        stream->ReadWords(list->directionList, list->numPoint * 12);
    } else {
        list->directionList = nullptr;
    }
    return emitter;
}

// 0x006f25a0 PrtStdEmitterProp1000006_Copy_maybe: count, flags and points (and the directions when used)
// into the clone's own arrays.
RpPrtStdEmitter* PointListCopy(RpAtomic*, RpPrtStdEmitter* emitter, void* data) {
    RpPrtStdEmitter* clone = static_cast<RpPrtStdEmitter*>(data);
    const int32_t from = EmitterPropOffset(emitter, rpPRTADVPROPERTYCODEEMITTERPOINTLIST);
    const int32_t to = EmitterPropOffset(clone, rpPRTADVPROPERTYCODEEMITTERPOINTLIST);
    if (from < 0 || to < 0) return clone;
    const RpPrtAdvEmtPointList* source = reinterpret_cast<RpPrtAdvEmtPointList*>(PropertyAt(emitter, from));
    RpPrtAdvEmtPointList* target = reinterpret_cast<RpPrtAdvEmtPointList*>(PropertyAt(clone, to));
    target->useDirection = source->useDirection;
    target->random = source->random;
    target->numPoint = source->numPoint;
    std::memcpy(target->pointList, source->pointList, source->numPoint * 12);
    if (source->useDirection == 1) std::memcpy(target->directionList, source->directionList, target->numPoint * 12);
    return clone;
}

// 0x006f17b0 PrtStdEmitterProp1000007_StreamRead_maybe (circle): three reals, a flag (+0x0c = 1 when 1),
// a real.
RpPrtStdEmitter* CircleStreamRead(RpAtomic*, RpPrtStdEmitter* emitter, void* data) {
    Stream* stream = static_cast<Stream*>(data);
    const int32_t offset = EmitterPropOffset(emitter, rpPRTADVPROPERTYCODEEMITTERCIRCLE);
    if (offset < 0) return emitter;
    uint8_t* prop = PropertyAt(emitter, offset);
    stream->ReadWords(prop + 0x0, 4);
    stream->ReadWords(prop + 0x4, 4);
    stream->ReadWords(prop + 0x8, 4);
    WordAt(prop, 0xc) = stream->ReadInt32() == 1 ? 1u : 0u;
    stream->ReadWords(prop + 0x10, 4);
    return emitter;
}
// 0x006f18c0 PrtStdEmitterProp1000007_Copy_maybe: 0x14 bytes.
RpPrtStdEmitter* CircleCopy(RpAtomic*, RpPrtStdEmitter* emitter, void* data) {
    RpPrtStdEmitter* clone = static_cast<RpPrtStdEmitter*>(data);
    const int32_t from = EmitterPropOffset(emitter, rpPRTADVPROPERTYCODEEMITTERCIRCLE);
    const int32_t to = EmitterPropOffset(clone, rpPRTADVPROPERTYCODEEMITTERCIRCLE);
    if (from >= 0 && to >= 0) std::memcpy(PropertyAt(clone, to), PropertyAt(emitter, from), 0x14);
    return clone;
}

// 0x006f0f08 PrtStdEmitterProp1000008_StreamRead_maybe (sphere): two reals, a flag (+0x08 = 1 when 1).
RpPrtStdEmitter* SphereStreamRead(RpAtomic*, RpPrtStdEmitter* emitter, void* data) {
    Stream* stream = static_cast<Stream*>(data);
    const int32_t offset = EmitterPropOffset(emitter, rpPRTADVPROPERTYCODEEMITTERSPHERE);
    if (offset < 0) return emitter;
    uint8_t* prop = PropertyAt(emitter, offset);
    stream->ReadWords(prop + 0x0, 4);
    stream->ReadWords(prop + 0x4, 4);
    WordAt(prop, 0x8) = stream->ReadInt32() == 1 ? 1u : 0u;
    return emitter;
}
// 0x006f1010 PrtStdEmitterProp1000008_Copy_maybe: 0xc bytes.
RpPrtStdEmitter* SphereCopy(RpAtomic*, RpPrtStdEmitter* emitter, void* data) {
    RpPrtStdEmitter* clone = static_cast<RpPrtStdEmitter*>(data);
    const int32_t from = EmitterPropOffset(emitter, rpPRTADVPROPERTYCODEEMITTERSPHERE);
    const int32_t to = EmitterPropOffset(clone, rpPRTADVPROPERTYCODEEMITTERSPHERE);
    if (from >= 0 && to >= 0) std::memcpy(PropertyAt(clone, to), PropertyAt(emitter, from), 0xc);
    return clone;
}

// 0x006f2fb0 PrtStdEmitterProp1000001_StreamRead_maybe (particle emitter): four reals.
RpPrtStdEmitter* PrtEmitterStreamRead(RpAtomic*, RpPrtStdEmitter* emitter, void* data) {
    Stream* stream = static_cast<Stream*>(data);
    const int32_t offset = EmitterPropOffset(emitter, rpPRTADVPROPERTYCODEEMITTERPRTEMITTER);
    if (offset >= 0) stream->ReadWords(PropertyAt(emitter, offset), 0x10);
    return emitter;
}
// 0x006f3078 PrtStdEmitterProp1000001_Copy_maybe: the four reals; +0x10 cleared.
RpPrtStdEmitter* PrtEmitterCopy(RpAtomic*, RpPrtStdEmitter* emitter, void* data) {
    RpPrtStdEmitter* clone = static_cast<RpPrtStdEmitter*>(data);
    const int32_t from = EmitterPropOffset(emitter, rpPRTADVPROPERTYCODEEMITTERPRTEMITTER);
    const int32_t to = EmitterPropOffset(clone, rpPRTADVPROPERTYCODEEMITTERPRTEMITTER);
    if (from >= 0 && to >= 0) {
        uint8_t* target = PropertyAt(clone, to);
        std::memcpy(target, PropertyAt(emitter, from), 0x10);
        reinterpret_cast<RpPrtAdvEmtPrtEmt*>(target)->emitter = nullptr;
    }
    return clone;
}

// 0x006f38f0 PrtStdEmitterProp1000002_3_5_Init_maybe: multi colour (keys of 0x28 at +0x14), multi texcoords
// (0x28 at +0x1c), multi size (0x18 at +0x14); each only when its offset is above 0.
RpPrtStdEmitter* MultiInit(RpAtomic*, RpPrtStdEmitter* emitter, void*) {
    uint32_t size = 0;
    if (EmitterPropOffset(emitter, rpPRTADVPROPERTYCODEEMITTERPRTMULTICOLOR) > 0) {
        uint8_t* prop = PropertyWithSize(emitter, rpPRTADVPROPERTYCODEEMITTERPRTMULTICOLOR, &size);
        const uint32_t count = (size - 0x14u) / 0x28u;
        InitKeys(prop, 0x14, count);
        WordAt(prop, 0xc) = count * 4 + 4;
        WordAt(prop, 0x10) = count * 4 + 4 + count * 16;
    }
    if (EmitterPropOffset(emitter, rpPRTADVPROPERTYCODEEMITTERPRTMULTITEXCOORDS) > 0) {
        uint8_t* prop = PropertyWithSize(emitter, rpPRTADVPROPERTYCODEEMITTERPRTMULTITEXCOORDS, &size);
        const uint32_t count = (size - 0x1cu) / 0x28u;
        InitKeys(prop, 0x1c, count);
        const uint32_t first = count * 4 + 4;
        WordAt(prop, 0xc) = first;
        WordAt(prop, 0x10) = first + count * 8;
        WordAt(prop, 0x14) = first + count * 16;
        WordAt(prop, 0x18) = first + count * 24;
    }
    if (EmitterPropOffset(emitter, rpPRTADVPROPERTYCODEEMITTERPRTMULTISIZE) > 0) {
        uint8_t* prop = PropertyWithSize(emitter, rpPRTADVPROPERTYCODEEMITTERPRTMULTISIZE, &size);
        const uint32_t count = (size - 0x14u) / 0x18u;
        InitKeys(prop, 0x14, count);
        WordAt(prop, 0xc) = count * 4 + 4;
        WordAt(prop, 0x10) = count * 4 + 4 + count * 8;
    }
    return emitter;
}

// 0x006f3d58 PrtStdEmitterProp1000002_3_5_StreamRead_maybe: per property the key count, then the keys (into
// the keys the create callback points at). Version < 3 streams also get their stride words reset.
RpPrtStdEmitter* MultiStreamRead(RpAtomic*, RpPrtStdEmitter* emitter, void* data) {
    Stream* stream = static_cast<Stream*>(data);
    struct Keys {
        int32_t propID;
        uint32_t keys;
        uint32_t keySize;
    };
    static const Keys kKeys[] = {
        {rpPRTADVPROPERTYCODEEMITTERPRTMULTICOLOR, 0x14, 0x28},
        {rpPRTADVPROPERTYCODEEMITTERPRTMULTITEXCOORDS, 0x1c, 0x28},
        {rpPRTADVPROPERTYCODEEMITTERPRTMULTISIZE, 0x14, 0x18},
    };
    for (const Keys& keys : kKeys) {
        const int32_t offset = EmitterPropOffset(emitter, keys.propID);
        if (offset < 0) continue;
        uint8_t* prop = PropertyAt(emitter, offset);
        stream->ReadWords(prop, 4);
        const uint32_t count = WordAt(prop, 0);
        if (count == 0) continue;
        stream->ReadWords(prop + keys.keys, count * keys.keySize);
        if (g_streamVersion < 3) LegacyStrides(prop, keys.propID, count);
    }
    return emitter;
}

// 0x006f3fd0 PrtStdEmitterProp1000002_3_5_Copy_maybe: each property with its keys, the self pointer reset.
RpPrtStdEmitter* MultiCopy(RpAtomic*, RpPrtStdEmitter* emitter, void* data) {
    RpPrtStdEmitter* clone = static_cast<RpPrtStdEmitter*>(data);
    struct Keys {
        int32_t propID;
        uint32_t keys;
        uint32_t keySize;
    };
    static const Keys kKeys[] = {
        {rpPRTADVPROPERTYCODEEMITTERPRTMULTICOLOR, 0x14, 0x28},
        {rpPRTADVPROPERTYCODEEMITTERPRTMULTITEXCOORDS, 0x1c, 0x28},
        {rpPRTADVPROPERTYCODEEMITTERPRTMULTISIZE, 0x14, 0x18},
    };
    for (const Keys& keys : kKeys) {
        const int32_t from = EmitterPropOffset(emitter, keys.propID);
        const int32_t to = EmitterPropOffset(clone, keys.propID);
        if (from < 0 || to < 0) continue;
        uint8_t* source = PropertyAt(emitter, from);
        uint8_t* target = PropertyAt(clone, to);
        std::memcpy(target, source, WordAt(source, 0) * keys.keySize + keys.keys);
        StoreSelfPointer(target + 4, target + keys.keys);
    }
    return clone;
}

// 0x006f54e0 PrtStdEmitterProp1000004_Init_maybe (multi texcoords step): keys of 0x28 at +0x1c, only when
// the offset is above 0.
RpPrtStdEmitter* TexCoordsStepInit(RpAtomic*, RpPrtStdEmitter* emitter, void*) {
    if (EmitterPropOffset(emitter, rpPRTADVPROPERTYCODEEMITTERPRTMULTITEXCOORDSSTEP) <= 0) return emitter;
    uint32_t size = 0;
    uint8_t* prop = PropertyWithSize(emitter, rpPRTADVPROPERTYCODEEMITTERPRTMULTITEXCOORDSSTEP, &size);
    WordAt(prop, 0x18) = 0;
    WordAt(prop, 0x10) = 0;
    const uint32_t count = (size - 0x1cu) / 0x28u;
    InitKeys(prop, 0x1c, count);
    WordAt(prop, 0xc) = count * 4 + 4;
    WordAt(prop, 0x14) = count * 4 + 4 + count * 8;
    return emitter;
}

// 0x006f56c8 PrtStdEmitterProp1000004_StreamRead_maybe: the key count, then the keys.
RpPrtStdEmitter* TexCoordsStepStreamRead(RpAtomic*, RpPrtStdEmitter* emitter, void* data) {
    Stream* stream = static_cast<Stream*>(data);
    const int32_t offset = EmitterPropOffset(emitter, rpPRTADVPROPERTYCODEEMITTERPRTMULTITEXCOORDSSTEP);
    if (offset < 0) return emitter;
    uint8_t* prop = PropertyAt(emitter, offset);
    stream->ReadWords(prop, 4);
    const uint32_t count = WordAt(prop, 0);
    if (count != 0) {
        stream->ReadWords(prop + 0x1c, count * 0x28);
        // Version < 3 streams: the stride words set again (the time offset 4, the UV0 array after the
        // times, the UV1 array 8 bytes per key after it; +0x10 and +0x18 are left).
        if (g_streamVersion < 3) {
            WordAt(prop, 8) = 4;
            WordAt(prop, 0xc) = count * 4 + 4;
            WordAt(prop, 0x14) = count * 4 + 4 + count * 8;
        }
    }
    return emitter;
}

// 0x006f57d0 PrtStdEmitterProp1000004_Copy_maybe
RpPrtStdEmitter* TexCoordsStepCopy(RpAtomic*, RpPrtStdEmitter* emitter, void* data) {
    RpPrtStdEmitter* clone = static_cast<RpPrtStdEmitter*>(data);
    const int32_t from = EmitterPropOffset(emitter, rpPRTADVPROPERTYCODEEMITTERPRTMULTITEXCOORDSSTEP);
    const int32_t to = EmitterPropOffset(clone, rpPRTADVPROPERTYCODEEMITTERPRTMULTITEXCOORDSSTEP);
    if (from >= 0 && to >= 0) {
        uint8_t* source = PropertyAt(emitter, from);
        uint8_t* target = PropertyAt(clone, to);
        std::memcpy(target, source, WordAt(source, 0) * 0x28 + 0x1c);
        StoreSelfPointer(target + 4, target + 0x1c);
    }
    return clone;
}

// 0x006ef7c8 RpPrtStdEClass_BuildStdCallBackArray_maybe: the standard callbacks, then one array per
// advanced feature the class id names, in this order: the emitter shape (0x10000 point list, 0x20000
// circle, 0x30000 sphere), 0x100 particle emitter, 0x1600 multi colour / texcoords / size, 0x800
// texcoords step. Each slot's callbacks are packed from the first array on (the standard one always
// takes array 0), so the stream reads run standard, shape, particle emitter, multi, step.
RpPrtStdEmitterClass* EClassBuildCallBackArray(RpPrtStdEmitterClass* eClass) {
    RpPrtStdEmitterCallBackArray features[4] = {};
    const uint32_t id = static_cast<uint32_t>(eClass->id);
    int32_t count = 1;
    switch (id & 0xff0000u) {
        case 0x10000u:
            features[0].callback[rpPRTSTDEMITTERCALLBACKEMIT] = PointListEmit;
            features[0].callback[rpPRTSTDEMITTERCALLBACKCREATE] = PointListInit;
            features[0].callback[rpPRTSTDEMITTERCALLBACKSTREAMREAD] = PointListStreamRead;
            features[0].callback[rpPRTSTDEMITTERCALLBACKCLONE] = PointListCopy;
            count = 2;
            break;
        case 0x20000u:
            features[0].callback[rpPRTSTDEMITTERCALLBACKEMIT] = CircleEmit;
            features[0].callback[rpPRTSTDEMITTERCALLBACKSTREAMREAD] = CircleStreamRead;
            features[0].callback[rpPRTSTDEMITTERCALLBACKCLONE] = CircleCopy;
            count = 2;
            break;
        case 0x30000u:
            features[0].callback[rpPRTSTDEMITTERCALLBACKEMIT] = SphereEmit;
            features[0].callback[rpPRTSTDEMITTERCALLBACKSTREAMREAD] = SphereStreamRead;
            features[0].callback[rpPRTSTDEMITTERCALLBACKCLONE] = SphereCopy;
            count = 2;
            break;
        default:
            break;
    }
    if ((id & 0x100u) != 0) {
        features[count - 1].callback[rpPRTSTDEMITTERCALLBACKEMIT] = PrtEmitterEmit;
        features[count - 1].callback[rpPRTSTDEMITTERCALLBACKSTREAMREAD] = PrtEmitterStreamRead;
        features[count - 1].callback[rpPRTSTDEMITTERCALLBACKCLONE] = PrtEmitterCopy;
        ++count;
    }
    if ((static_cast<uint32_t>(eClass->id) & 0x1600u) != 0) {
        features[count - 1].callback[rpPRTSTDEMITTERCALLBACKEMIT] = MultiEmit;
        features[count - 1].callback[rpPRTSTDEMITTERCALLBACKCREATE] = MultiInit;
        features[count - 1].callback[rpPRTSTDEMITTERCALLBACKSTREAMREAD] = MultiStreamRead;
        features[count - 1].callback[rpPRTSTDEMITTERCALLBACKCLONE] = MultiCopy;
        ++count;
    }
    if ((id & 0x800u) != 0) {
        features[count - 1].callback[rpPRTSTDEMITTERCALLBACKEMIT] = TexCoordsStepEmit;
        features[count - 1].callback[rpPRTSTDEMITTERCALLBACKCREATE] = TexCoordsStepInit;
        features[count - 1].callback[rpPRTSTDEMITTERCALLBACKSTREAMREAD] = TexCoordsStepStreamRead;
        features[count - 1].callback[rpPRTSTDEMITTERCALLBACKCLONE] = TexCoordsStepCopy;
        ++count;
    }
    const RpPrtStdEmitterCallBackArray standard = StandardCallBacks();
    RpPrtStdEmitterCallBackArray packed[8] = {};
    for (int32_t slot = 0; slot < rpPRTSTDEMITTERCALLBACKMAX; ++slot) {
        int32_t used = 0;
        packed[used++].callback[slot] = standard.callback[slot];
        for (const RpPrtStdEmitterCallBackArray& feature : features) {
            if (feature.callback[slot] != nullptr) packed[used++].callback[slot] = feature.callback[slot];
        }
    }
    EClassSetCallBackArray(eClass, count, packed);
    return eClass;
}

// 0x006ef410 RpPrtStdPClass_BuildStdCallBackArray_maybe: per slot, the particle emitter feature's callback
// (0x100) before the standard one, then the multi (0x1600) and texcoords step (0x800) features'. Only the
// update slot has callbacks: 0x1000001's (0x6f3348, RpPrtAdvRuntime.cpp), the standard update (0x734188),
// the key frames (0x6f50e0), the texcoord steps (0x6f5df0).
// The count is 1 + one per feature present.
RpPrtStdParticleClass* PClassBuildCallBackArray(RpPrtStdParticleClass* pClass) {
    const uint32_t id = static_cast<uint32_t>(pClass->id);
    RpPrtStdParticleCallBack pre = nullptr;
    RpPrtStdParticleCallBack post[2] = {};
    int32_t count = 1;
    if ((id & 0x100u) != 0) {
        pre = PrtEmitterUpdate;  // 0x6f3348 PrtStdEmitterProp1000001_Update_maybe
        count = 2;
    }
    if ((id & 0x1600u) != 0) {
        post[0] = KeyFramesUpdate;
        ++count;
    }
    if ((id & 0x800u) != 0) {
        post[1] = TexCoordStepUpdate;  // 0x6f5df0
        ++count;
    }
    RpPrtStdParticleCallBackArray packed[4] = {};
    int32_t used = 0;
    if (pre != nullptr) packed[used++].callback[rpPRTSTDPARTICLECALLBACKUPDATE] = pre;
    packed[used++].callback[rpPRTSTDPARTICLECALLBACKUPDATE] = StdParticleUpdate;
    for (RpPrtStdParticleCallBack callback : post) {
        if (callback != nullptr) packed[used++].callback[rpPRTSTDPARTICLECALLBACKUPDATE] = callback;
    }
    PClassSetCallBackArray(pClass, count, packed);
    return pClass;
}

}  // namespace rpprtstd
