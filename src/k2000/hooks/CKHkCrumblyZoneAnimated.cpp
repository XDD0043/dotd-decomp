// Reconstructed original translation unit: 0x410190-0x411100 (GAME_TOC1, main_toc1), 27 functions, 24 live.
// Primary class: CKHkCrumblyZoneAnimated  key 0x3982  category Hook  size 0x1cc  vtable 0xb258c0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x410190  CKHkCrumblyZoneAnimated_Delete  (the factory Delete, DOTD_DECLARE_FACTORIES)
//   [ ] 0x4101e0  RegisterCKHkCrumblyZoneAnimatedClass
//   [ ] 0x410258  _GLOBAL__I_410258
//   [ ] 0x410268  CKHkCrumblyZoneAnimated_IsAnimEndReached_maybe  [dead]
//   [x] 0x410298  CKHkCrumblyZoneAnimated_vfF0  (CKHkCrumblyZone::UpdateStageNodeMotion 0x406410: inherited)
//   [x] 0x4102c0  CKHkCrumblyZoneAnimated_vfF8  (CKHkCrumblyZone::VfF8 0x4072a8: inherited)
//   [x] 0x4102e8  CKHkCrumblyZoneAnimated_UpdateAnim_maybe  (no caller: only its OPD; Update inlines it)
//   [x] 0x410368  CKHkCrumblyZoneAnimated_Resume  (the actor base's 0x3f6e60: inherited)
//   [x] 0x410390  CKHkCrumblyZoneAnimated_Pause  (the actor base's 0x3f6e58: inherited)
//   [x] 0x4103b8  CKHkCrumblyZoneAnimated_Stop  (the actor base's 0x3f6e50: inherited)
//   [x] 0x4103e0  CKHkCrumblyZoneAnimated_Start  (CKHkCrumblyZone::Start 0x406de0: inherited)
//   [x] 0x410408  CKHkCrumblyZoneAnimated_OnDeactivate  (CKHkCrumblyZone::VfA4 0x40bcd8: inherited)
//   [ ] 0x410430  CKHkCrumblyZoneAnimated_Save
//   [x] 0x410458  CKHkCrumblyZoneAnimated_RecursiveRegistration  (CKHkCrumblyZone::RecursiveRegistration 0x406810: inherited)
//   [x] 0x410480  CKHkCrumblyZoneAnimated_Destroy
//   [x] 0x4104b8  CKHkCrumblyZoneAnimated_BaseDestructor  (the header's destructor; the inlined base destructor 0x9c11e8 is not ported)
//   [ ] 0x410660  CKHkCrumblyZoneAnimated_Construct  [dead]
//   [x] 0x410708  CKHkCrumblyZoneAnimated_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x4107a8  CKHkCrumblyZoneAnimated_OnActivate  (CKHkCrumblyZoneAnimated::VfA0)
//   [x] 0x410868  CKHkCrumblyZoneAnimated_vf104
//   [ ] 0x4108b0  CKHkCrumblyZoneAnimated_Construct_2  [dead]
//   [x] 0x410958  CKHkCrumblyZoneAnimated_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x410aa8  CKHkCrumblyZoneAnimated_Create  (the header's constructor)
//   [x] 0x410b70  CKHkCrumblyZoneAnimated_Load
//   [x] 0x410c70  CKHkCrumblyZoneAnimated_Update
//   [x] 0x410d98  CKHkCrumblyZoneAnimated_DeletingDestructor  (the header's destructor; the inlined base destructor 0x9c11e8 is not ported)
//   [x] 0x410f58  CKHkCrumblyZoneAnimated_Destructor  (the header's destructor; the inlined base destructor 0x9c11e8 is not ported)
//
//   [ ] 0x9c2550  CKHkCrumblyZoneAnimated_IsKindOfClass  [inline]
//   [ ] 0x9c25b0  CKHkCrumblyZoneAnimated_GetClassType  [inline]
//   [ ] 0x9c25b8  CKHkCrumblyZoneAnimated_GetClassID  [inline]
#include "k2000/hooks/CKHkCrumblyZoneAnimated.h"

#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/io/IKFile.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/system/IKTime.h"

namespace {

const float kZero = 0.0f;  // TOC1 +0x4a4c

CAnimatedNode* Node(const CKHkCrumblyZoneAnimated* z) { return static_cast<CAnimatedNode*>(z->m_pKGLObject); }
// Animation `index` of the dictionary (a word: the original's PostLoad turns the words into animations).
uint32_t AnimWord(const CKHkCrumblyZoneAnimated* z, uint32_t index) {
    return static_cast<uint32_t>(static_cast<CAnimationDictionary*>(z->m_pZFAAnimDictionary)->m_apAnimations[index]);
}

}  // namespace

// 0x004102e8 CKHkCrumblyZoneAnimated_UpdateAnim_maybe
void CKHkCrumblyZoneAnimated::UpdateAnim(float dt) {
    const uint8_t next = m_ui8NextAnim;
    if (m_ui8CurrentAnim != next) {
        m_ui8CurrentAnim = next;
        Node(this)->PlayAnim(kZero, AnimWord(this, next), 0);  // 0x000c98b8
        return;
    }
    Node(this)->AddAnimTime(dt);  // 0x000c9638
}

// 0x00410480 CKHkCrumblyZoneAnimated_Destroy
void CKHkCrumblyZoneAnimated::Destroy() {
    CKHkCrumblyZone::Destroy();  // 0x00406398
    m_pZFAAnimDictionary = nullptr;
}

// 0x004107a8 CKHkCrumblyZoneAnimated_OnActivate
void CKHkCrumblyZoneAnimated::VfA0() {
    CKHkCrumblyZone::VfA0();  // 0x0040bf00
    if (m_unk188 == 0) return;
    if (m_pKGLObject->GetClassID() != 0x15) return;  // vt+0x18: an animated node
    m_ui8NextAnim = 0;
    m_ui8CurrentAnim = 0;
    Node(this)->PlayAnim(kZero, AnimWord(this, 0), 0);  // 0x000c98b8
}

// 0x00410868 CKHkCrumblyZoneAnimated_vf104
void CKHkCrumblyZoneAnimated::Vf104(uint32_t mode, const CVector3* point) {
    CKHkCrumblyZone::TriggerCollapse(mode, point, 0);  // 0x00407880 (called directly, not through vt+0xf4)
    if (m_unk1C8 != 0) m_ui8NextAnim = 1;
}

// 0x00410b70 CKHkCrumblyZoneAnimated_Load
int32_t CKHkCrumblyZoneAnimated::Load(IKFile* file, int32_t type) {
    CKHkCrumblyZone::Load(file, type);  // 0x0040ca50
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pZFAAnimDictionary);
    ReadF32LE(file, &m_fAnimScale);
    return 1;
}

// 0x00410c70 CKHkCrumblyZoneAnimated_Update
void CKHkCrumblyZoneAnimated::Update(IKTime* clock) {
    CKHkCrumblyZone::Update(clock);  // 0x0040c2f8
    if (m_unk188 == 0) return;
    if (m_pKGLObject->GetClassID() != 0x15) return;  // vt+0x18
    const float dt = clock->m_afDeltaTime[0];  // +0x1c
    const uint8_t next = m_ui8NextAnim;
    if (m_ui8CurrentAnim != next) {
        m_ui8CurrentAnim = next;
        Node(this)->PlayAnim(kZero, AnimWord(this, next), 0);  // 0x000c98b8
    } else {
        Node(this)->AddAnimTime(m_fAnimScale * dt);  // fmuls, 0x000c9638
    }
    if (m_unk1C8 == 0) return;
    if (m_ui8CurrentAnim != 1) return;
    if (Node(this)->IsAnimEndReached(clock->m_afDeltaTime[0])) m_ui8NextAnim = 0;  // 0x000ca368
}
