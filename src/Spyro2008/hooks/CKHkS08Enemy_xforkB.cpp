// CKHkS08Enemy_xforkB.cpp - DOTD (C2.7 enemy family, fork B): stand-ins for functions other forks port (CKHkS08Enemy.cpp,
// _2.cpp, _5.cpp, CKCoreManager.cpp). The merge replaces each with its port and deletes this file.
#include "Spyro2008/hooks/CKHkS08Enemy.h"

#include "k2000/components/CKEnemySectorCpnt.h"
#include "k2000/core/Stub.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/groups/CKGrpSquad.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvShadow.h"

// 0x0001d5c0 Group_TransferHook_maybe (CKCoreManager.cpp): the hook moved between the weapon pools (CKGrpSquad.cpp).
void GroupTransferHook(CKCoreManager* /*core*/, IKHook* hook, IKBaseGroup* to, IKBaseGroup* from, uint32_t /*flags*/) {
    Group_TransferHook(hook, to, from);
}

// 0x0027cf30 CKHkS08Enemy_SetPartsFlagForCategory_maybe: with volumes of the type: type 2 sets +0x7cd; type 1 sets
// flag 0x100 of each of its volumes (+0x1a); other types nothing (the original's loop is empty). The count is read
// again after each volume.
void CKHkS08Enemy::SetPartsFlagForCategory(int32_t category) {
    if (m_aui8BoundingNumberByType[category] == 0) return;
    if (category == 2) {
        m_unk7cd = 1;
        return;
    }
    if (category != 1) return;
    for (uint32_t i = 0; m_aui8BoundingNumberByType[1] > i; ++i) {
        auto* volume = static_cast<IKBoundingVolume*>(m_apBV[m_aui8BoundingIndexByType[1] + i]);
        if (volume != nullptr) volume->m_ui16PropertiesFlags = static_cast<uint16_t>(volume->m_ui16PropertiesFlags | 0x100u);
    }
}

// 0x0027d018 CKHkS08Enemy_ClearPartsFlagForCategory_maybe: SetPartsFlagForCategory's opposite (+0x7cd = 0, flag 0x100
// cleared).
void CKHkS08Enemy::ClearPartsFlagForCategory(int32_t category) {
    if (m_aui8BoundingNumberByType[category] == 0) return;
    if (category == 2) {
        m_unk7cd = 0;
        return;
    }
    if (category != 1) return;
    for (uint32_t i = 0; m_aui8BoundingNumberByType[1] > i; ++i) {
        auto* volume = static_cast<IKBoundingVolume*>(m_apBV[m_aui8BoundingIndexByType[1] + i]);
        if (volume != nullptr) volume->m_ui16PropertiesFlags = static_cast<uint16_t>(volume->m_ui16PropertiesFlags & ~0x100u);
    }
}

// 0x002773e0 CKHkS08Enemy_UnregisterShadowCaster_maybe: a registered caster (+0x1b0 set, used byte +0x1ad) leaves the
// shadow service.
void CKHkS08Enemy::UnregisterShadowCaster() {
    if (m_pShadowCpnt == nullptr || m_unk1ad == 0) return;
    static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow)
        ->UnregisterCaster(reinterpret_cast<CKShadowGround*>(&m_v3ShadowGroundPosition), m_pShadowCpnt);  // 0x001fd6f0
}

// The layer's slot's active track's evaluated time (+0x54, the time its last Evaluate used), as the states that test the
// animation marks read it inline (State00_Spawn 0x2a0da8: layer 0's slot 0, the controller array (+4) at the active
// index (+0x10)).
float CKHkS08Enemy::LayerSlotAnimTime(int32_t layer, int32_t slot) {
    return ActiveTrack(m_apAnimLayerSlots[layer][slot])->m_unk54;
}
