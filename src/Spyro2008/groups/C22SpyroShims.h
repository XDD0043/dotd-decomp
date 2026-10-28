// C22SpyroShims.h - C2.2 family spyro: local copies of small callees whose owner TU belongs to another
// family (the brief says "stay in your files"). Each carries the original address and name; when the owner
// family's port lands, the main session replaces the call by the real function and deletes the copy here.
// Not a translation unit of the original: nothing here is ported code of its own.
#pragma once
#include <cstdint>

#include <cmath>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/core/Stub.h"
#include "k2000/components/CKBoundingCpnt.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/hooks/CKHkHeroActivator.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvDynamic.h"
#include "k2000/sound/CKListener.h"

namespace c22spyro {

// The PS3 is big-endian: the byte at the lowest address of a word is its most significant one. `index` is the
// byte's offset from the word's address (0..3), as the original's byte stores name it.
inline void SetBeByte(uint32_t& word, unsigned index, uint8_t value) {
    const unsigned shift = 24u - 8u * index;
    word = (word & ~(0xffu << shift)) | (static_cast<uint32_t>(value) << shift);
}

// 0x0023aff8 CKSrvDynamic_SetEntryFlag (k2000/services/CKSrvDynamic.cpp, family svc): the first entry
// registered for `object` gets its flag byte (the first byte of the big-endian word at +0x04) set.
inline void SrvDynamicSetEntryFlag(CKSrvDynamic* service, const IKSerializable* object, uint8_t flag) {
    if (service->m_vEntries.m_ui32NbUsedElt == 0) return;
    CKSrvDynamic::Entry* entries = service->m_vEntries.m_pBlock;
    for (uint32_t i = 0; i < service->m_vEntries.m_ui32NbUsedElt; ++i) {
        if (entries[i].m_unk00 == object) {
            entries[i].m_ui8Flag = flag;
            return;
        }
    }
}

// 0x00110330 SoundListener_SetFollowCamera_maybe / 0x00110308 SoundListener_SetOrientationFollowCamera_maybe
// (k2000/sound/SoundListener.cpp, family svc): a non-zero argument stores 0, zero stores 1.
inline void ListenerSetFollowCamera(CKListener* listener, int32_t follow) { listener->m_unk38 = follow != 0 ? 0u : 1u; }
inline void ListenerSetOrientationFollowCamera(CKListener* listener, int32_t follow) {
    listener->m_unk3c = follow != 0 ? 0u : 1u;
}

// 0x004497d0 CKHkHeroActivator_SetEnabled (k2000/hooks/CKHkHeroActivator.cpp, family hooks) for enabled == 0,
// the only way the C2.2 spyro code calls it (vt+0xcc). Local copy.
// STUB(C2.2): SetMarkerFx(0) 0x4494c0 releases the marker node fx with its vt+0x58 when m_unk94 is set; the
// activators start with it clear (PostLoad), so only that branch is left out.
inline void HeroActivatorDisable(CKHkHeroActivator* activator) {
    activator->m_bitArray = activator->m_bitArray & 0xfffffeffu;  // enabled bit (bit 8) = 0
    activator->m_bitArray = activator->m_bitArray & 0xfffff9ffu;
    activator->m_unk94 = 0;
    if (activator->m_unk60 != nullptr) {
        CParticlesNodeFx* marker = static_cast<CParticlesNodeFx*>(activator->m_unk60);
        marker->m_sgProperties = marker->m_sgProperties & 0xfff7fbffu;  // bits 10 and 19
        marker->m_pRpPrtStdEmitter->flag = marker->m_pRpPrtStdEmitter->flag & 0xfffffff7u;
    }
    if (activator->m_pKGLObject != nullptr) {
        CSGLeaf* object = static_cast<CSGLeaf*>(activator->m_pKGLObject);
        object->m_sgProperties = (object->m_sgProperties & 0xfffffffbu) | 4u;  // (enabled ^ 1) << 2
    }
}

// 0x001920e8 CKSrvCollision_DisableVolume (k2000/services/CKSrvCollision.cpp, family svc). Local copy.
inline void CollisionDisableVolume(CKSrvCollision* service, IKBoundingVolume* volume) {
    if ((volume->m_ba8Infos & 1u) != 0) {
        volume->m_ba8Infos = static_cast<uint8_t>(volume->m_ba8Infos & 0xfeu);
        service->m_Infos = (service->m_Infos & 0xfffffffdu) | 2u;
    }
    volume->m_ba8Infos = static_cast<uint8_t>(volume->m_ba8Infos & 0xfbu);
}

// 0x00192090 CKSrvCollision_EnableVolume (k2000/services/CKSrvCollision.cpp, family svc). Local copy.
inline void CollisionEnableVolume(CKSrvCollision* service, IKBoundingVolume* volume) {
    if ((volume->m_ba8Infos & 1u) == 0) {
        volume->m_ba8Infos = static_cast<uint8_t>((volume->m_ba8Infos & 0xfeu) | 1u);
        service->m_Infos = (service->m_Infos & 0xfffffffeu) | 1u;
    }
    volume->m_ba8Infos = static_cast<uint8_t>((volume->m_ba8Infos & 0xfbu) | 4u);
}

// 0x001903c0 VolumeArray_SetDamage_maybe (k2000/components/CKBoundingCpnt.cpp, family hooks). Local copy:
// every volume of the component (last to first) gets the damage object.
inline void VolumeArraySetDamage(CKBoundingCpnt* cpnt, IKSerializable* damage) {
    for (uint32_t i = cpnt->m_vVolumes.m_ui32NbUsedElt; i != 0; --i) {
        static_cast<IKBoundingVolume*>(cpnt->m_vVolumes.m_pBlock[i - 1])->m_unk1c = damage;
    }
}

// ---- scene-frame and math primitives of other families' files (k2000/misc/Wcs.cpp, k2000/math/Vec3.cpp,
// k2000/misc/Mat4.cpp). The exact ones are copied; the others are stubs until those ports land.

// 0x00010690 Math_Sqrtf: the double square root rounded to float, as a double.
inline double MathSqrtf(double x) { return static_cast<double>(static_cast<float>(std::sqrt(x))); }

// 0x00010698 RwFrame_MarkDirty: the root frame's private flags |= 3 (hierarchy dirty), this frame's |= 0xc.
// (The dirty list itself, RwFrameAddChild's, is not ported: the flags are all the original sets here.)
inline void RwFrameMarkDirty(RwFrame* frame) {
    frame->root->object.privateFlags = static_cast<RwUInt8>(frame->root->object.privateFlags | 3);
    frame->object.privateFlags = static_cast<RwUInt8>(frame->object.privateFlags | 0xc);
}

// The frame's position written (modelling matrix +0x30) and the matrix' identity flag (0x20000) cleared, as
// the original does inline before RwFrame_MarkDirty.
inline void RwFrameSetPosition(RwFrame* frame, float x, float y, float z) {
    frame->modelling.pos.x = x;
    frame->modelling.pos.y = y;
    frame->modelling.pos.z = z;
    frame->modelling.flags = frame->modelling.flags & 0xfffdffffu;
}

}  // namespace c22spyro
