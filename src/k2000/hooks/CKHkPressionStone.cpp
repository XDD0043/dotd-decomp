// CKHkPressionStone.cpp - reconstructed original translation unit 0x425b98-0x42a308 (GAME_TOC1, main_toc1), 43 functions, 38 live.
// Primary class: CKHkPressionStone  key 0x542  category Hook  size 0xd0  vtable 0xb26100
// Other owners: CarryTarget (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x425b98  CKHkPressionStone_Delete
//   [ ] 0x425be8  CKHkPressionStone_RefreshOccupantHero_maybe  [dead]
//   [x] 0x425cd0  CKHkPressionStone_SetOccupant_maybe
//   [ ] 0x425d30  FUN_00425d30  [dead]
//   [ ] 0x425d38  FUN_00425d38  [dead]
//   [ ] 0x425da0  RegisterCKHkPressionStoneClass
//   [ ] 0x425e18  _GLOBAL__I_425e18
//   [x] 0x425e28  CKHkPressionStone_AcquireInputIconFx_maybe
//   [x] 0x4260d0  CKHkPressionStone_FindPressingObject_maybe
//   [x] 0x426330  CKHkPressionStone_Resume  (empty / no effect: inherited)
//   [x] 0x426358  CKHkPressionStone_Pause  (empty / no effect: inherited)
//   [x] 0x426380  CKHkPressionStone_Stop  (empty / no effect: inherited, CKHkActorBase_d82_maybe_Stop 0x3f6e50)
//   [x] 0x4263a8  CKHkPressionStone_Start
//   [x] 0x426410  CKHkPressionStone_PostLoad
//   [ ] 0x426500  CKHkPressionStone_Save
//   [x] 0x426528  CKHkPressionStone_RecursiveRegistration  (= the inherited slot: CKHkActorBase_d82_maybe_LevelReset 0x3f6ee8, then 1)
//   [x] 0x426550  CKHkPressionStone_Construct  [dead]
//   [x] 0x426588  CKHkPressionStone_DeleteArray
//   [x] 0x426628  CKHkPressionStone_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x426658  CKHkPressionStone_Destroy
//   [ ] 0x4266a8  CKHkPressionStone_Construct_2  [dead]
//   [x] 0x4266e0  CKHkPressionStone_GetInfo
//   [x] 0x4268f0  CKHkPressionStone_IsOccupiedByHeroProperty_maybe
//   [x] 0x4269a8  CKHkPressionStone_DeletingDestructor  (the deleting form of the implicit destructor)
//   [x] 0x4269f0  CKHkPressionStone_Destructor  (the C++ destructor (CKHkActorBase_d82_maybe_BaseDestructor 0x3f73f0))
//   [x] 0x426a20  CKHkPressionStone_AttachSounds
//   [x] 0x426be8  CarryTarget_GetGroundedPlacementPoint_maybe  (CKHkTransportableObjectSpawner.cpp)
//   [x] 0x426d20  CKHkPressionStone_ApplyStatePreset_maybe
//   [x] 0x426e50  CKHkPressionStone_SetDefaultState
//   [x] 0x426ef0  CKHkPressionStone_CreateArray
//   [x] 0x426fa0  CKHkPressionStone_OnDeactivate
//   [x] 0x427060  CKHkPressionStone_Create
//   [x] 0x4270b8  CKHkPressionStone_UpdateHotspotSequence_maybe
//   [x] 0x427380  CKHkPressionStone_StartHotspotSequence_maybe
//   [x] 0x4275c8  CKHkPressionStone_ClearFlagC28_StartHotspotSequenceIfFlagC27_maybe
//   [x] 0x427608  CKHkPressionStone_MessageProc
//   [x] 0x427a28  CKHkPressionStone_UpdateStandingHero_maybe
//   [ ] 0x427f88  CKHkPressionStone_SetNavBoxBlocked_maybe  [dead]  (no pointer to its descriptor 0xbb7e30, no call)
//   [x] 0x4280f0  CKHkPressionStone_Restart
//   [x] 0x4284b8  CKHkPressionStone_Update
//   [x] 0x429618  CKHkPressionStone_Load
//   [x] 0x429d38  CKHkPressionStone_OnActivate
//   [x] 0x42a1a8  CKHkPressionStone_SetNavBlockedForGroup_maybe
//
//   [ ] 0x9c30d8  CKHkPressionStone_IsKindOfClass  [inline]
//   [ ] 0x9c3130  CKHkPressionStone_GetClassType  [inline]
//   [ ] 0x9c3138  CKHkPressionStone_GetClassID  [inline]
//   [x] 0x9c3140  CKHkPressionStone_vfE4  [inline]  (CKHkPressionStone.h GetGroundCount)
//   [x] 0x9c3148  CKHkPressionStone_GetTriggerPropA2  [inline]
//   [x] 0x9c3168  CKHkPressionStone_GetTriggerPropA3  [inline]
//   [x] 0x9c3188  CKHkPressionStone_GetTriggerProp9A  [inline]
//   [x] 0x9c3198  CKHkPressionStone_GetTriggerPropA4  [inline]
//   [x] 0x9c31a8  CKHkPressionStone_vfE8  [inline]  (CKHkPressionStone.h GetGround)
//   [x] 0x9c31b0  CKHkPressionStone_GetTriggerPropA8  [inline]
#include "k2000/hooks/CKHkPressionStone.h"
#include "k2000/fx/IKFx.h"

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKPFGraphNode.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "crt/ppc_ops.h"
#include "k2000/core/IKInfo.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/misc/CKHkS08TransportableBase.h"
#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Spyro2008/hooks/IKHkEnemy.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKInputIconNodeFx.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/CKGrpMeca.h"
#include "k2000/misc/IKGrpEnemy.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/system/IKTime.h"
#include "k2000/logic/physics/CDynamicGround.h"
#include "k2000/misc/Mat4.h"

// 0x00429618 CKHkPressionStone_Load: everything but the last reference is read for every serialization type.
int32_t CKHkPressionStone::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    IKFile_ReadRef(file, &m_unk64);
    IKFile_ReadRef(file, &m_unk68);
    IKFile_ReadRef(file, &m_unk88);
    IKFile_ReadRef(file, &m_unk78);
    IKFile_ReadObjectRefArray(file, m_apUnk6C, 3);
    IKFile_ReadRef(file, &m_unk8C);
    m_unk9C.Load(file, type);
    m_unkA4.Load(file, type);
    m_unkAC.Load(file, type);
    m_unkB4.Load(file, type);
    m_unkBC.Load(file, type);
    m_unkC4.Load(file, type);
    ReadU8(file, &m_unk7C);
    if (m_unk7C == 0) {
        m_apUnk80 = nullptr;
    } else {
        m_apUnk80 = static_cast<IKSerializable**>(
            Mem_AllocAligned16(static_cast<uint32_t>(m_unk7C * sizeof(IKSerializable*))));
        IKFile_ReadObjectRefArray(file, m_apUnk80, m_unk7C);
    }
    ReadF32LE(file, &m_fMaxClearance);
    ReadF32LE(file, &m_fUpSpeed);
    ReadF32LE(file, &m_fDownSpeed);
    ReadF32LE(file, &m_unk60);
    ReadU16LE(file, &m_ui16HerosToTest);
    ReadU8(file, &m_unk4C);
    ReadF32LE(file, &m_unk5C);
    ReadF32LE(file, &m_unk84);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_unk90);
    return 1;
}

// 0x004263a8 CKHkPressionStone_Start
void CKHkPressionStone::Start() {
    CKHkActorBase::Start();
    m_bitArray &= 0x3fffffffu;
    m_unkCC = 1;
    m_unk44 = nullptr;  // +0x44
    m_unk48 = 0.0f;  // +0x48
    m_unk40 = nullptr;  // +0x40
}

// g_nullVector 0x00c50d64 (TOC +0x4e34), the moving part's base.
void CKHkPressionStone::PlaceMovingPart() {
    const CVector3 base = {0.0f, 0.0f, 0.0f};
    RwFrame* frame = static_cast<CSGMovable*>(m_unk64)->m_pRwFrame;
    if ((m_bitArray & 0x20000u) != 0) {
        const float raise = m_fMaxClearance;  // +0x50
        m_fRaise = raise;
        const RwV3d& up = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->modelling.up;  // RwFrame +0x20
        frame->modelling.pos.x = ppc::fmadds(raise, up.x, base.x);
        frame->modelling.pos.y = ppc::fmadds(raise, up.y, base.y);
        frame->modelling.pos.z = ppc::fmadds(raise, up.z, base.z);
    } else {
        m_fRaise = 0.0f;
        frame->modelling.pos.z = base.z;
        frame->modelling.pos.x = base.x;
        frame->modelling.pos.y = base.y;
    }
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
}

// The engine's path-finding service (+0x6c); the point's hint 0xffff; the box's height the found point's plus 0.0 (TOC
// +0x4df4), its half side +0x60 times 0.75 (TOC +0x4e3c); the node index checked against the node count.
void CKHkPressionStone::SetNavBox(int32_t blocked) {
    CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    CPFPoint point;
    point.m_position = m_vPosition;
    point.m_i16GraphNodeIndex = 0xffff;
    const float size = m_unk60;
    if ((pathFinding->FindSectorForPoint(&point) & 0xff) == 0) return;  // 0x001e5ca0
    const float half = size * 0.75f;
    const float kHeight = 0.0f;
    const float y = point.m_position.y + kHeight;
    const CVector3 low = {-half + point.m_position.x, y, -half + point.m_position.z};
    const CVector3 high = {half + point.m_position.x, y, half + point.m_position.z};
    const uint16_t node = point.m_i16GraphNodeIndex;
    if (pathFinding->m_Graph.m_ui32GraphNodesSize <= node) return;
    static_cast<CKPFGraphNode*>(pathFinding->m_Graph.m_apGraphNodes[node])->m_Sector.SetBoxBlocked(&low, &high, static_cast<uint8_t>(blocked));  // 0x001ed3c0
}

void CKHkPressionStone::UpdateNavBlocking() {
    if ((m_bitArray & 0x200u) != 0) BlockNavBox();
    m_bitArray &= 0xfbffffffu;
    if ((m_bitArray & 0x400000u) != 0) {
        if ((m_bitArray & 0x200u) != 0) BlockNavBox();
        m_bitArray = (m_bitArray & 0xff7fffffu) | 0x800000u;
    }
    m_unk48 = 0.0f;  // +0x48
}

// 0x00429d38 CKHkPressionStone_OnActivate
void CKHkPressionStone::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    m_bitArray = (m_bitArray & 0xfcffffffu) | 0x1000000u;
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    node->m_sgProperties &= 0xfffffffbu;
    m_pObject = nullptr;  // +0x3c
    m_unk30 = 0;  // +0x30
    m_pHero = nullptr;  // +0x34
    m_unk38 = nullptr;  // +0x38
    PlaceMovingPart();
    if (m_unk68 != nullptr) {
        CAnimationDictionary* animations = static_cast<CAnimationDictionary*>(m_unk88);
        const uint32_t which = (m_bitArray & 0x8000000u) != 0 ? 1u : 0u;  // flag bit 27
        static_cast<CAnimatedNode*>(m_unk68)->PlayAnim(0.0, static_cast<uint32_t>(animations->m_apAnimations[which]), 0);  // 0x000c98b8
    }
    const RwV3d& position = FrameLtm(node->m_pRwFrame)->pos;  // RwFrame +0x80
    m_vPosition = {position.x, position.y, position.z};
    m_bitArray = (m_bitArray & 0xffbfffffu) | 0x400000u;
    UpdateNavBlocking();
}

// 0x004280f0 CKHkPressionStone_Restart
void CKHkPressionStone::Restart() {
    if ((m_bitArray & 4u) == 0) {
        m_unk30 = 0;  // +0x30
        PlaceMovingPart();
        m_bitArray = (m_bitArray & 0xfdbfffffu) | 0x400000u;
        UpdateNavBlocking();
    }
    m_unk48 = 0.0f;  // +0x48
    m_unkCC = 1;
}

// 0x00426e50 CKHkPressionStone_SetDefaultState: bits 17-21 and 27-29 cleared, bits 19 and 29 set, bit 27 =
// bit 11.
void CKHkPressionStone::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);
    const uint32_t f = m_bitArray;
    m_bitArray = (f & 0xc7c1ffffu) | 0x20080000u | (((f >> 11) & 1) << 27);
}

// 0x00426d20 CKHkPressionStone_ApplyStatePreset_maybe. With a = flags bit 14 (state 0) or 15 (state 1) and b =
// bit 12 (state 0) or 13 (state 1): bits 17 and 18 = a, bit 19 = !a, bits 20 and 21 cleared, bit 27 = b, bit 28
// cleared, bit 29 = !a (the original's rlwimi chain, checked bit by bit).
void CKHkPressionStone::ApplyStatePreset(int32_t state) {
    const uint32_t f = m_bitArray;
    const uint32_t a = (f >> (state == 0 ? 14 : 15)) & 1;
    const uint32_t b = (f >> (state == 0 ? 12 : 13)) & 1;
    uint32_t r = f & ~(0x3e0000u | 0x38000000u);
    r |= (a << 17) | (a << 18) | ((a ^ 1u) << 19) | (b << 27) | ((a ^ 1u) << 29);
    m_bitArray = r;
}

// 0x00427608 CKHkPressionStone_MessageProc
int32_t CKHkPressionStone::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 0;
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_pHero);
    switch (message) {
    case 0x998: {
        m_bitArray = (((m_bitArray | 0x20000u) | 0x40000u) | 0x04000000u) & 0xdff7ffffu;
        m_fRaise = m_fMaxClearance;
        PlaceMovingPartAt(m_fMaxClearance);
        break;
    }
    case 0x999: {
        m_bitArray &= 0xfff9ffffu;
        m_fRaise = 0.0f;  // stw 0
        RwFrame* frame = static_cast<CSGMovable*>(m_unk64)->m_pRwFrame;
        frame->modelling.pos.z = 0.0f;  // the null vector 0x00c50d64 (TOC1 +0x4e34)
        frame->modelling.pos.x = 0.0f;
        frame->modelling.pos.y = 0.0f;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(frame);  // 0x00010698
        break;
    }
    case 0x93f: {
        CKHkS08Hero* sender = static_cast<CKHkS08Hero*>(data);
        if (sender->IsPlayerControlled() == 0 && data == m_pHero && sender->AttachToObject(this, 1) != 0) {  // 0x00362af0, 0x00362360
            hero->SetFlag35CBit0IfAttached(1);  // 0x00363e88
        }
        break;
    }
    case 0x940:
        if (hero != nullptr) {
            hero->DetachFromObject();  // 0x00364608
            m_pHero = nullptr;
        }
        break;
    case 0x996:
        m_bitArray = (m_bitArray & 0xfffbffffu) | 0x40000u;
        break;
    case 0x997:
        m_bitArray &= 0xfffbffffu;
        break;
    case 0x99a:
        if (hero != nullptr && hero->GetAttachedObject() == this) {  // 0x00361d50
            hero->DetachFromObject();  // 0x00364608
            m_pHero = nullptr;
            m_bitArray = (m_bitArray & 0xfdffffffu) | 0x02000000u;
        }
        break;
    case 0x99b:
        m_bitArray = (m_bitArray & 0xefffffffu) | 0x10000000u;
        StartHotspotSequence();  // 0x00427380
        break;
    case 0x99c: {
        const uint32_t bits = m_bitArray;
        m_bitArray = bits & 0xefffffffu;
        if ((m_bitArray & 0x08000000u) != 0) {
            m_bitArray = bits & 0xe7ffffffu;
            StartHotspotSequence();  // 0x00427380
        }
        break;
    }
    default:
        own = 1;
        break;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    return base == 0 ? 0 : own;
}

// 0x004266e0 CKHkPressionStone_GetInfo, with its accessors 0x9c3188 / 0x4268f0 / 0x9c3148 / 0x9c3168 / 0x9c3198 /
// 0x9c31b0 (GetTriggerProp9A, IsOccupiedByHeroProperty_maybe, GetTriggerPropA2 / A3 / A4 / A8).
int32_t CKHkPressionStone::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor) return 1;
    switch (info->m_ui32Id) {
    case 0x9a:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            return (static_cast<CKHkPressionStone*>(o)->m_bitArray >> 17) & 1u;
        }, 0);
    case 0x9b:
        // The hero of dragon index `arg` stands on the stone; `arg` = the hero count (no hero) is true while none does.
        return AnswerInfo(info, [](IKSerializable* o, uint32_t arg) -> uint32_t {
            const CKHkPressionStone* stone = static_cast<CKHkPressionStone*>(o);
            CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);  // +0x08
            const uint8_t count = group->GetHeroCount();  // 0x002ca038
            if (stone->m_pHero == nullptr) return arg == count ? 1u : 0u;
            if (arg == count) return 0;
            return arg == static_cast<CKHkS08Hero*>(stone->m_pHero)->GetDragonIndex() ? 1u : 0u;  // 0x00361960
        }, 0);
    case 0xa2:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            return static_cast<CKHkPressionStone*>(o)->m_pObject != nullptr ? 1u : 0u;
        }, 0);
    case 0xa3:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            return static_cast<CKHkPressionStone*>(o)->m_unk38 != 0 ? 1u : 0u;
        }, 0);
    case 0xa4:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            return (static_cast<CKHkPressionStone*>(o)->m_bitArray >> 27) & 1u;
        }, 0);
    case 0xa8:
        // The spawner of the transportable on the stone (CKHkS08TransportableBase +0x28, 0x4abfb0), else 0. The value is
        // an object compared for (in)equality; the x64 build keeps its low 32 bits.
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) -> uint32_t {
            IKSerializable* object = static_cast<CKHkPressionStone*>(o)->m_pObject;
            if (object == nullptr || object->IsKindOfClass(0x3002) == 0) return 0;  // vt+0x08
            return static_cast<uint32_t>(
                reinterpret_cast<uintptr_t>(static_cast<CKHkS08TransportableBase*>(object)->m_unk28));
        }, 3);
    default:
        return 1;
    }
}

// 0x00426fa0 CKHkPressionStone_OnDeactivate
void CKHkPressionStone::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_pHero);
    if (hero != nullptr && hero->GetAttachedObject() == this) {  // 0x00361d50
        hero->DetachFromObject();                                 // 0x00364608
        m_pHero = nullptr;
    }
    if (m_unk94 == nullptr) return;
    m_unk94->StopAndRelease(this);  // vt+0x58
    m_unk94 = nullptr;
}

// 0x00426658 CKHkPressionStone_Destroy (CKHkActorBase_d82_maybe_ClearReferences 0x3f6e08 first: vt+0xc0, empty here)
void CKHkPressionStone::Destroy() {
    if (m_apUnk80 == nullptr) return;
    Mem_FreeAligned16(m_apUnk80);  // 0x00052fb8
    m_apUnk80 = nullptr;
}

// The node's LTM position (RwFrame +0x80) of a scene node.
static const RwV3d& NodeLtmPosition(IKSerializable* node) {
    return FrameLtm(static_cast<CSGMovable*>(node)->m_pRwFrame)->pos;
}

// The moving part's frame (Update's two copies; g_nullVector 0x00c50d64 the base).
void CKHkPressionStone::PlaceMovingPartAt(float raise) {
    const CVector3 base = {0.0f, 0.0f, 0.0f};
    const RwV3d& up = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->modelling.up;  // RwFrame +0x20
    RwFrame* frame = static_cast<CSGMovable*>(m_unk64)->m_pRwFrame;
    frame->modelling.pos.x = ppc::fmadds(raise, up.x, base.x);
    frame->modelling.pos.y = ppc::fmadds(raise, up.y, base.y);
    frame->modelling.pos.z = ppc::fmadds(raise, up.z, base.z);
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
}

// 0x00425e28 CKHkPressionStone_AcquireInputIconFx_maybe (the data +0x90 is read without a test: Update calls this only
// while the carrier hero marks the stone, +0x98).
void CKHkPressionStone::AcquireInputIconFx() {
    if (m_unk94 != nullptr) return;
    m_unk94 = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(m_unk90), this);
    if (m_unk94 == nullptr) return;
    const RwV3d& ltm = NodeLtmPosition(m_pKGLObject);
    const CVector3 position = {ltm.x, ltm.y, ltm.z};
    static_cast<CKInputIconNodeFx*>(m_unk94)->SetPosition(&position);  // 0x001c45c8
}

// 0x004260d0 CKHkPressionStone_FindPressingObject_maybe. The distance (+0x5c) against 0.0 (TOC +0x4df4); the held
// object's node LTM made current first (vt+0x50); the scan keeps the meca group's list order (null-terminated). The
// active actors are CKHkActorBase hooks (CKHkActorBase::VfA0 lists them).
uint8_t CKHkPressionStone::FindPressingObject() {
    if ((m_bitArray & 0x40u) == 0) return 0;
    const float kNone = 0.0f;
    IKSerializable* object = m_pObject;
    if (object != nullptr) {
        m_unk40 = object;
        IKSerializable* node = static_cast<IKHook*>(object)->m_pKGLObject;
        static_cast<CSGMovable*>(node)->ForceWorldMatrixUpdate();  // vt+0x50
        bool within = true;
        if (m_unk5C != kNone) {
            const RwV3d& a = NodeLtmPosition(m_pKGLObject);
            const RwV3d& b = NodeLtmPosition(node);
            const CVector3 pa = {a.x, a.y, a.z};
            const CVector3 pb = {b.x, b.y, b.z};
            within = Vec3_IsWithinDistance(m_unk5C, &pa, &pb) != 0;  // 0x00244320
        }
        if (((m_bitArray & 0x80u) == 0 || static_cast<CKHkActorBase*>(object)->VfEC() == m_apUnk6C[0]) && within) {
            return 1;  // vt+0xec
        }
        m_pObject = nullptr;
    }
    CKGrpMeca* meca = static_cast<CKGrpMeca*>(g_pEngine->m_gameManager->m_unk04[2]);  // the game manager's +0x0c
    if (meca == nullptr) return 0;
    for (IKHook** actor = meca->m_pUnk2c; *actor != nullptr; ++actor) {
        IKHook* hook = *actor;
        if (hook == this) continue;
        if ((m_bitArray & 0x80u) != 0 && static_cast<CKHkActorBase*>(hook)->VfEC() != m_apUnk6C[0]) continue;  // vt+0xec
        if (m_unk5C != kNone) {
            if (hook->m_pKGLObject == nullptr) continue;
            const RwV3d& a = NodeLtmPosition(m_pKGLObject);
            const RwV3d& b = NodeLtmPosition(hook->m_pKGLObject);
            const CVector3 pa = {a.x, a.y, a.z};
            const CVector3 pb = {b.x, b.y, b.z};
            if (Vec3_IsWithinDistance(m_unk5C, &pa, &pb) == 0) continue;
        }
        m_pObject = hook;
        return 1;
    }
    return 0;
}

// The squared distances against 0.1 (TOC +0x4e38) and 0.25 (TOC +0x4e40), summed as the original does (y first, then
// fused); `blt` (a NaN distance takes the other test).
uint8_t CKHkPressionStone::IsHeroOnStone(CKHkS08Hero* hero) const {
    if ((hero->m_bitArray & 2u) != 0) {
        const float* position = hero->GetPositionPtr();  // 0x00361968
        const RwV3d& node = NodeLtmPosition(hero->m_pKGLObject);
        const float dy = position[1] - node.y;
        const float dx = position[0] - node.x;
        const float dz = position[2] - node.z;
        if (!(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)) < 0.1f)) {
            const RwV3d& stone = NodeLtmPosition(m_pKGLObject);
            const float ey = node.y - stone.y;
            const float ex = node.x - stone.x;
            const float ez = node.z - stone.z;
            return ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, ey * ey)) < 0.25f ? 1 : 0;
        }
    }
    return hero->GetGroundObject() == m_apUnk6C[0] ? 1 : 0;  // 0x00363c40
}

// 0x00427a28 CKHkPressionStone_UpdateStandingHero_maybe. The hero mask +0x4e is shifted by the dragon index (sraw).
uint8_t CKHkPressionStone::UpdateStandingHero() {
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_pHero);
    if (hero != nullptr) m_unk44 = hero;
    if ((m_bitArray & 0x10u) == 0) return 0;
    if (hero != nullptr) {
        if (((m_ui16HerosToTest >> hero->GetDragonIndex()) & 1u) != 0 && IsHeroOnStone(hero) != 0) return 1;
        if (hero->IsPlayerControlled() == 0) {
            m_bitArray &= 0xffefffffu;
            const uint32_t f = m_bitArray;
            if (!((f & 8u) == 0 && (f & 0x20000u) != 0) && (f & 0x200u) != 0) SetNavBox(1);
            hero->MessageProc(0xc3b, nullptr);  // vt+0x1c
        }
        if (hero->GetAttachedObject() == this) hero->DetachFromObject();  // 0x00361d50 / 0x00364608
        m_pHero = nullptr;
    }
    if (g_pEngine->m_gameManager->m_unk04[1] != nullptr) {  // +0x08
        uint8_t index = static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1])->GetHeroCount();  // 0x002ca038
        for (;;) {
            index = static_cast<uint8_t>(index - 1);
            if (index == 0xff) break;
            CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);
            CKHkS08Hero* candidate = static_cast<CKHkS08Hero*>(group->m_apHeros[index]);  // 0x002ca080
            if (((m_ui16HerosToTest >> candidate->GetDragonIndex()) & 1u) == 0) continue;
            if (IsHeroOnStone(candidate) == 0) continue;
            m_pHero = candidate;
            if ((m_bitArray & 0x2000000u) == 0) {
                m_bitArray &= 0xffefffffu;
                return 1;
            }
        }
    }
    if ((m_bitArray & 0x2000000u) == 0) return 0;
    if (m_pHero == nullptr) m_bitArray &= 0xfdffffffu;
    m_pHero = nullptr;
    return 0;
}

void CKHkPressionStone::EmitParticles() {
    CParticlesNodeFx* particles = static_cast<CParticlesNodeFx*>(m_unk78);
    particles->m_sgProperties = (particles->m_sgProperties | 0x600u) & 0xfff7ffffu;
    particles->m_fEmissionSpeedAdjustment = 0.0f;
    particles->m_pRpPrtStdEmitter->flag |= 0xau;
}

void CKHkPressionStone::EmitAtHotspot(uint32_t index) {
    CVector3 position;
    static_cast<CSGHotSpot*>(m_apUnk80[index])->GetWorldPosition(&position);  // 0x000ce790
    const RwV3d& origin = NodeLtmPosition(m_unk68);
    position.x = position.x - origin.x;
    position.y = position.y - origin.y;
    position.z = position.z - origin.z;
    RwFrame* frame = static_cast<CSGMovable*>(m_unk78)->m_pRwFrame;
    frame->modelling.pos.x = position.x;
    frame->modelling.pos.y = position.y;
    frame->modelling.pos.z = position.z;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
    EmitParticles();
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk8C);
    if (sounds->GetSound(1) != nullptr) sounds->GetSound(1)->Play(0.0f);  // 0x00112bc0 / 0x00111230
}

// 0x00427380 CKHkPressionStone_StartHotspotSequence_maybe (0.99 TOC +0x4e30; the count converted exactly: fcfid).
void CKHkPressionStone::StartHotspotSequence() {
    if (m_unk84 > 0.0f) {  // ble: a period not above 0 (or NaN) emits now
        m_unk48 = m_unk84 * (static_cast<float>(m_unk7C) + 0.99f);
        return;
    }
    if (m_unk7C == 0) {
        EmitParticles();
        return;
    }
    for (uint32_t i = 0; static_cast<int32_t>(m_unk7C) > static_cast<int32_t>(i); ++i) EmitAtHotspot(i);
}

// 0x004270b8 CKHkPressionStone_UpdateHotspotSequence_maybe. The steps after and before this frame are the timer over
// the period truncated (fctiwz) plus one, the earlier one as a byte; the hot spots between them emit, from the last
// one (count - step).
void CKHkPressionStone::UpdateHotspotSequence(float dt) {
    if (m_unk7C == 0) {
        const float t = m_unk48 - dt;
        m_unk48 = t;
        if (!(t < 0.0f)) return;  // bge
        m_unk48 = 0.0f;
        EmitParticles();
        CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk8C);
        if (sounds->GetSound(1) != nullptr) sounds->GetSound(1)->Play(0.0f);
        return;
    }
    const float before = m_unk48;
    const float t = before - dt;
    const float period = m_unk84;
    m_unk48 = t;
    uint32_t step;
    if (t < 0.0f) {
        step = 1;
        m_unk48 = 0.0f;
    } else {
        step = static_cast<uint32_t>(ppc::fctiwz(t / period)) + 1;
    }
    const int32_t last = static_cast<int32_t>(static_cast<uint8_t>(ppc::fctiwz(before / period))) + 1;
    uint32_t current = step & 0xffu;
    while (last > static_cast<int32_t>(current)) {
        ++step;
        EmitAtHotspot(static_cast<uint32_t>(m_unk7C) - current);
        current = step & 0xffu;
    }
}

// 0x004284b8 CKHkPressionStone_Update. Flag bits: 24 the activation frame (skipped once), 28 a hot spot sequence to
// start (with 17, or with neither 21 nor 18), 27 the sequence's animation (dictionary +0x88 entry 1, else 0), 17 down,
// 18 / 21 / 3 the press states, 26 kept pressed, 20 an NPC on it, 30..31 who pressed it (1 hero, 2 enemy, 3 object),
// 29 the release signalled, 19 the up signal sent, 22 / 23 / 9 / 6 the nav box. The animation entries are dictionary
// words (CAnimationManager_GetAnimation; -1, absent, is null like the original's PostLoad'ed entries).
void CKHkPressionStone::Update(IKTime* frameClock) {
    // 0x003f6e68 WorldObjectBase_Update_Nop first (the actor base's Update: empty).
    if (m_unk98 == nullptr) {
        if (m_unk94 != nullptr) {
            m_unk94->StopAndRelease(this);  // vt+0x58
            m_unk94 = nullptr;
        }
    } else {
        AcquireInputIconFx();
    }
    const float dt = frameClock->m_afDeltaTime[0];
    uint32_t f = m_bitArray;
    m_unk98 = nullptr;
    if ((f & 0x1000000u) != 0) {
        m_bitArray &= 0xfeffffffu;
        return;
    }
    if ((f & 0x10000000u) != 0 && ((f & 0x20000u) != 0 || ((f & 0x200000u) == 0 && (f & 0x40000u) == 0))) {
        m_bitArray = (m_bitArray & 0xf7ffffffu) | 0x8000000u;
        StartHotspotSequence();
        m_bitArray &= 0xefffffffu;
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_pHero);
        if (hero != nullptr && hero->GetAttachedObject() == this) {
            hero->DetachFromObject();
            m_pHero = nullptr;
        }
    }
    CAnimatedNode* node = static_cast<CAnimatedNode*>(m_unk68);
    if (node != nullptr) {
        if (m_unk48 > 0.0f) {  // ble
            UpdateHotspotSequence(dt);
            node = static_cast<CAnimatedNode*>(m_unk68);
        }
        const bool sequence = (m_bitArray & 0x8000000u) != 0;
        const uint32_t word = static_cast<uint32_t>(static_cast<CAnimationDictionary*>(m_unk88)->m_apAnimations[sequence ? 1 : 0]);
        if (node->GetCurrentAnim() == CAnimationManager_GetAnimation(word)) {  // 0x000c96d8
            if (sequence) return;
        } else {
            if (node->IsAnimEndReached(dt)) {  // 0x000ca368
                node->PlayAnim(0.0, word, 0);  // 0x000c98b8
            } else {
                node->AddAnimTime(dt);  // 0x000c9638
            }
            return;
        }
    }
    f = m_bitArray;
    bool pressed;            // the press path (0x00428910 / 0x00428924)
    bool keepFlags = false;  // 0x00428924 entered with bit 26 already cleared
    if ((f & 0x20000u) == 0) {
        pressed = (f & 0x200000u) != 0;
    } else {
        if ((f & 0x200000u) != 0) return;
        if ((f & 0x40000u) != 0 && (f & 8u) == 0) return;
        pressed = false;
    }
    if (!pressed) {
        // 0x00428788
        const bool down = (f & 0x20000u) != 0;
        const bool risingUnheld = (f & 0x40000u) != 0 && !down;
        if (m_unkCC != 0) {
            m_bitArray &= 0xfbffffffu;
            pressed = down;
            keepFlags = true;
        } else if (risingUnheld || UpdateStandingHero() != 0) {
            pressed = true;
        } else {
            bool enemy = false;
            if ((m_bitArray & 0x20u) != 0) {
                IKHkEnemy* on = static_cast<IKHkEnemy*>(m_unk38);
                if (on != nullptr) {
                    if (on->m_pGroupSquad != nullptr && on->m_GrdContDatasInOut.m_pGround == m_apUnk6C[0]) {
                        enemy = true;
                    } else {
                        m_unk38 = nullptr;
                    }
                }
                IKGrpEnemy* enemies = static_cast<IKGrpEnemy*>(g_pEngine->m_gameManager->m_unk04[0]);  // +0x04
                if (!enemy && enemies != nullptr) {
                    for (uint32_t i = 0; i < enemies->m_ui32NbActiveEnemies; ++i) {
                        IKHkEnemy* candidate = static_cast<IKHkEnemy*>(enemies->m_apActiveEnemies[i]);
                        if (candidate->m_GrdContDatasInOut.m_pGround == m_apUnk6C[0]) {
                            m_unk38 = candidate;
                            enemy = true;
                            break;
                        }
                    }
                }
            }
            if (enemy || FindPressingObject() != 0 || (m_bitArray & 0x4000000u) != 0) {
                pressed = true;
            } else {
                m_bitArray &= 0xfbffffffu;
            }
        }
    }
    if (pressed) {
        if (!keepFlags) m_bitArray &= 0xfbffffffu;  // 0x00428910
        // 0x00428924
        const float raise = m_fRaise;
        const float target = m_fMaxClearance;
        if (target == raise) {
            if ((m_bitArray & 0x20000u) == 0) {
                m_bitArray &= 0xdff7ffffu;
                CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk8C);
                if (sounds->GetSound(0) != nullptr) sounds->GetSound(0)->Play(0.0f);
                CKHkS08Hero* on = static_cast<CKHkS08Hero*>(m_pHero);
                if (on != nullptr && on->IsPlayerControlled() != 0 && (m_bitArray & 0x100u) != 0 &&
                    on->IsPlayerControlled() != 0) {
                    if (m_unk4C != 0xff) {
                        CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);  // +0x08
                        group->RequestDragonSelectionThunk(on->GetDragonIndex(), m_unk4C, 0, 0, 0);  // 0x002ca740
                    }
                    CKHkS08Hero* player = static_cast<CKHkS08Hero*>(m_pHero);
                    if (player->IsPlayerControlled() != 0) player->MessageProc(0xc42, nullptr);  // vt+0x1c
                }
                QueueTriggerSignals(&m_unk9C);  // 0x00236338
            }
            m_bitArray |= 0x60000u;
            if ((m_bitArray & 8u) == 0) {
                if ((m_bitArray & 0x200u) != 0) SetNavBox(0);
                m_bitArray &= 0xff7fffffu;
            }
            CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_pHero);
            if (hero != nullptr && hero->IsPlayerControlled() == 0 && (m_bitArray & 0x400u) != 0 &&
                hero->GetAttachedObject() != this && (m_bitArray & 0x400000u) != 0 && m_unk30 == 0) {
                m_bitArray |= 0x100000u;
                if ((m_bitArray & 0x200u) != 0) SetNavBox(0);
                m_bitArray &= 0xff7fffffu;
                if (static_cast<CKHkS08Hero*>(m_pHero)->AttachToObject(this, 0) != 0) {  // 0x00362360
                    if ((m_bitArray & 0x40u) != 0) {
                        static_cast<CKHkS08Hero*>(m_pHero)->SetLockedToObject(1, nullptr, nullptr);  // 0x003622a8
                    }
                    static_cast<CKHkS08Hero*>(m_pHero)->SetFlag35CBit0IfAttached(1);  // 0x00363e88
                }
            }
            hero = static_cast<CKHkS08Hero*>(m_pHero);
            if (hero != nullptr && hero->IsPlayerControlled() != 0 && hero->GetAttachedObject() == this) {
                hero->DetachFromObject();
            }
            hero = static_cast<CKHkS08Hero*>(m_pHero);
            if (hero != nullptr && (m_bitArray >> 30) != 1) {
                QueueTriggerSignals(&m_unkA4);
                if ((m_bitArray & 0x10000u) != 0 && hero->GetAttachedObject() != this && hero->AttachToObject(this, 0) != 0) {
                    hero->SetAttachedMovementEnabled(1);      // 0x00362050
                    hero->SetUnk530IfAttachedMovement(0.0f);  // 0x003626a0
                    hero->SetAttachedMoveSpeed(0.0f);         // 0x00362670
                    hero->DetachFromObject();
                }
                m_bitArray = (m_bitArray & 0x3fffffffu) | 0x40000000u;
            } else if (m_unk38 != nullptr && (m_bitArray >> 30) != 2) {
                QueueTriggerSignals(&m_unkAC);
                m_bitArray = (m_bitArray & 0x3fffffffu) | 0x80000000u;
            } else if (m_pObject != nullptr && (m_bitArray >> 30) != 3) {
                QueueTriggerSignals(&m_unkB4);
                m_bitArray |= 0xc0000000u;
            }
        } else {
            const float lowered = raise - m_fDownSpeed * dt;
            m_fRaise = lowered;
            if (lowered < target) m_fRaise = target;  // blt
            PlaceMovingPartAt(m_fRaise);
        }
    } else {
        // 0x00428b88: released
        bool held = false;
        if (m_unk40 != nullptr) {
            IKSerializable* objectNode = static_cast<IKHook*>(m_unk40)->m_pKGLObject;
            bool gone = (static_cast<CSGLeaf*>(objectNode)->m_sgProperties & 4u) != 0;
            if (!gone) {
                const RwV3d& a = NodeLtmPosition(m_pKGLObject);
                const RwV3d& b = NodeLtmPosition(objectNode);
                const CVector3 pa = {a.x, a.y, a.z};
                const CVector3 pb = {b.x, b.y, b.z};
                gone = Vec3_IsWithinDistance(m_unk5C, &pa, &pb) == 0;
            }
            if (gone) {
                m_unk40 = nullptr;
                QueueTriggerSignals(&m_unkC4);
                m_bitArray |= 0x20000000u;
            }
            held = m_unk40 != nullptr;
        }
        if (!held) {
            if ((m_bitArray & 0x80000u) == 0) {
                QueueTriggerSignals(&m_unkBC);
                m_bitArray |= 0x80000u;
            }
            if ((m_bitArray & 0x20000000u) == 0 && m_unk44 != nullptr &&
                static_cast<CKHkS08Hero*>(m_unk44)->GetGroundInfo() != m_apUnk6C[0]) {  // 0x00361b68
                QueueTriggerSignals(&m_unkC4);
                m_bitArray |= 0x20000000u;
            }
            m_bitArray &= 0x3ff9ffffu;
            const float kTop = 0.0f;
            if (m_fRaise != kTop) {
                const float raised = ppc::fmadds(m_fUpSpeed, dt, m_fRaise);
                m_fRaise = raised;
                if (raised > kTop) m_fRaise = kTop;  // ble
                PlaceMovingPartAt(m_fRaise);
            }
        }
    }
    // 0x00428ad4
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_pHero);
    const bool npc = hero != nullptr && hero->IsPlayerControlled() == 0;
    const uint32_t npcBit = npc ? 0x100000u : 0u;
    if ((m_bitArray & 0x400000u) != 0 && m_unk30 == 0) {
        f = m_bitArray;
        if ((f & 0x40u) != 0 && (f & 0x800000u) != 0 && (f & 0x200u) != 0) SetNavBox(1);
        const RwV3d& ltm = NodeLtmPosition(m_pKGLObject);
        if (npc) {
            m_vPosition = {ltm.x, ltm.y, ltm.z};
        } else {
            if ((m_bitArray & 0x200u) != 0) SetNavBox(0);
            m_bitArray &= 0xff7fffffu;
            m_vPosition = {ltm.x, ltm.y, ltm.z};
            f = m_bitArray;
            if (!((f & 8u) == 0 && (f & 0x20000u) != 0)) {
                if ((f & 0x200u) != 0) SetNavBox(1);
                m_bitArray &= 0xff7fffffu;
            }
        }
    }
    m_bitArray = (m_bitArray & 0xffefffffu) | npcBit;
    m_unkCC = 0;
}

// 0x00425cd0 CKHkPressionStone_SetOccupant_maybe
uint8_t CKHkPressionStone::SetOccupant(IKSerializable* hero, int32_t set) {
    if (set == 0) {
        if (m_unk30 == hero) {
            m_unk30 = nullptr;
            return 1;
        }
    } else if (m_unk30 == nullptr || hero == m_unk30) {
        m_unk30 = hero;
        return 1;
    }
    return 0;
}

// 0x004275c8 CKHkPressionStone_ClearFlagC28_StartHotspotSequenceIfFlagC27_maybe
void CKHkPressionStone::StopHotspotHold() {
    const uint32_t bits = m_bitArray;
    m_bitArray = bits & 0xefffffffu;
    if ((m_bitArray & 0x08000000u) == 0) return;
    m_bitArray = bits & 0xe7ffffffu;
    StartHotspotSequence();  // 0x00427380
}

// 0x0042a1a8 CKHkPressionStone_SetNavBlockedForGroup_maybe: the box as SetNavBox builds it (the hint 0xffff, half side
// +0x60 * 0.75 (TOC +0x4e3c), the height + 0.0 from a zero stack word), blocked = the byte passed.
void CKHkPressionStone::SetNavBlockedForGroup(IKSerializable* hero, uint8_t blocked) {
    if (m_unk30 != hero) return;
    m_bitArray = (m_bitArray & 0xffbfffffu) | (static_cast<uint32_t>(blocked) << 22);  // rlwinm 22, 2, 9
    if ((m_bitArray & 0x200u) == 0) return;
    SetNavBox(blocked);
}

// 0x00426a20 CKHkPressionStone_AttachSounds
void CKHkPressionStone::KGLObjectAttached(IKSerializable* leaf) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk8C);
    sounds->GetSound(0)->SetAttachObject(m_pKGLObject);  // 0x00112bc0, 0x00111350
    sounds->GetSound(1)->SetAttachObject(m_pKGLObject);
    IKSerializable* ground = m_apUnk6C[1];  // +0x70
    if (ground != nullptr && ground->IsKindOfClass(0x4cc) != 0) {  // vt+0x08: a CDynamicGround
        CDynamicGround* dynamic = static_cast<CDynamicGround*>(ground);
        dynamic->m_pParent = leaf;
        if (leaf == nullptr) {
            CMatrix34* m = dynamic->m_pInvertedWorldMatrix;  // the identity (1.0 TOC +0x4e1c), flags 0x20003
            m->m_ui32Flags = 0x20003u;
            m->m_pos.x = 0.0f;
            m->m_up.x = 0.0f;
            m->m_right.x = 1.0f;
            m->m_at.z = 1.0f;
            m->m_up.y = 1.0f;
            m->m_right.z = 0.0f;
            m->m_right.y = 0.0f;
            m->m_at.y = 0.0f;
            m->m_at.x = 0.0f;
            m->m_up.z = 0.0f;
            m->m_pos.z = 0.0f;
            m->m_pos.y = 0.0f;
        } else {
            Mat4_Invert(dynamic->m_pInvertedWorldMatrix,
                        reinterpret_cast<const CMatrix34*>(&static_cast<CSGMovable*>(leaf)->m_pRwFrame->ltm));  // 0x0023f878
        }
    }
    CSGLeaf* part = static_cast<CSGLeaf*>(m_unk64);
    if (part->m_pParent != nullptr) part->m_pParent->RemoveChild(part);  // vt+0x78
    static_cast<CSGBranch*>(m_pKGLObject)->AddChild(static_cast<CSGLeaf*>(m_unk64));  // vt+0x70
}
