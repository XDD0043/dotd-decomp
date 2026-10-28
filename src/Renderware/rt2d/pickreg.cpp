// pickreg.cpp - RW 3.7 tool/2d/pickreg.c, ported from the PS3 library code (0x718a28-0x719088). See Rt2d.h.
//
// Not ported (the front end never reaches them: no pointer input, no editor paths): Rt2dPickRegionIsPointIn
// 0x718bf8 (with _rt2dPathIsPointIn_maybe 0x714788 and _rt2dInverseTransformPointByCTM_maybe 0x7146e0),
// the stream writers and sizes 0x718b28 / 0x718b78 / 0x718e88 / 0x718ee0, Rt2dPickRegionCreate 0x718e20,
// Rt2dPickRegionDestroy 0x718d08, Rt2dPickRegionStreamRead 0x718fb8.
#include "Renderware/rt2d/Rt2dInternal.h"
#include "Renderware/rwcore/RwMatrix.h"

DOTD_ASSERT_OFFSET(Rt2dObject, data.pickRegion.path, 0xb0);
DOTD_ASSERT_OFFSET(Rt2dObject, data.pickRegion.transformation, 0xd0);

// 0x00718a28 Rt2dPickRegionGetPath
Rt2dPath* Rt2dPickRegionGetPath(Rt2dObject* region) { return region->data.pickRegion.path; }

// 0x00718a30 _rt2dPickRegionRender_maybe: a visible region only brings its transformation up to date:
// when its MTM changed, LTM = CTM x MTM and the transformation becomes the inverse LTM.
Rt2dObject* _rt2dPickRegionRender(Rt2dObject* region) {
    if ((region->flag & 4) == 0) return region;
    if ((region->flag & 2) != 0) {
        _rt2dCTMPushMult(&region->MTM);
        region->LTM = *_rt2dCTMGet();
        RwMatrixInvert(&region->data.pickRegion.transformation, &region->LTM);
        region->flag &= ~2;
    } else {
        _rt2dCTMPush(&region->LTM);
    }
    Rt2dCTMPop();
    return region;
}

// 0x00718c90 _rt2dPickRegionDestruct_maybe
RwBool _rt2dPickRegionDestruct(Rt2dObject* region) { return Rt2dPathDestroy(region->data.pickRegion.path); }

// 0x00718cc0 _rt2dPickRegionInit_maybe: a new (locked) path.
Rt2dObject* _rt2dPickRegionInit(Rt2dObject* region) {
    region->data.pickRegion.path = Rt2dPathCreate();
    region->flag &= ~1;
    return region;
}

// 0x00718d88 _rt2dPickRegionStreamReadTo: a new path (still locked), RwStreamFindChunk(0x1a1), the path.
// The bounding box and transformation are not read (the render computes the transformation).
Rt2dObject* _rt2dPickRegionStreamReadTo(Rt2dObject* region, RwStream* stream) {
    region->data.pickRegion.path = Rt2dPathCreate();
    region->flag &= ~1;
    RwUInt32 length = 0, version = 0;
    if (RwStreamFindChunk(stream, 0x1a1, &length, &version) == 0) return nullptr;
    if (_rt2dPathStreamReadTo(region->data.pickRegion.path, stream) == nullptr) return nullptr;
    return region;
}
