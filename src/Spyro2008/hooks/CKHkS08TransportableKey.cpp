// CKHkS08TransportableKey.cpp - reconstructed original translation unit 0x4ac580-0x4b08d8 (GAME_TOC1, main_toc1), 52 functions, 49 live.
// Primary class: CKHkS08TransportableKey  key 0x3082  category Hook  size 0x130  vtable 0xb28c08
// Other owners: Vec3 (1), CKHkS08TransportableWeight (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4ac580  CKHkS08TransportableKey_vf124
//   [ ] 0x4ac5d0  CKHkS08TransportableKey_vf120
//   [ ] 0x4ac610  CKHkS08TransportableKey_vf17C
//   [ ] 0x4ac888  CKHkS08TransportableKey_vf180
//   [ ] 0x4ac8f0  CKHkS08TransportableKey_vf16C
//   [ ] 0x4ac920  CKHkS08TransportableKey_ProbeGroundAtPoint_maybe  [dead]
//   [ ] 0x4ac9a8  Vec3_YawDifferenceWrapped_4_maybe  [dead]
//   [ ] 0x4aca38  CKHkS08TransportableKey_UpdateGroundAttachment_maybe
//   [ ] 0x4acdc0  CKHkS08TransportableKey_Resume
//   [ ] 0x4acde8  CKHkS08TransportableKey_Pause
//   [ ] 0x4ace10  CKHkS08TransportableKey_Stop
//   [ ] 0x4ace38  CKHkS08TransportableKey_Save
//   [ ] 0x4ace60  CKHkS08TransportableKey_RecursiveRegistration
//   [ ] 0x4ace88  CKHkS08TransportableKey_Destroy
//   [x] 0x4aced0  CKHkS08TransportableKey_Construct
//   [x] 0x4acf40  CKHkS08TransportableKey_DeleteArray
//   [x] 0x4acfe0  CKHkS08TransportableKey_PostLoad
//   [ ] 0x4ad0b0  CKHkS08TransportableKey_State0_maybe
//   [x] 0x4ad128  CKHkS08TransportableWeight_ConstructBase_maybe
//   [ ] 0x4ad198  CKHkS08TransportableKey_vf178
//   [ ] 0x4ad1e0  CKHkS08TransportableKey_vf110
//   [ ] 0x4ad1f8  CKHkS08TransportableKey_vfF4
//   [ ] 0x4ad220  RegisterCKHkS08TransportableKeyClass
//   [ ] 0x4ad2a8  _GLOBAL__D_4ad2a8
//   [ ] 0x4ad2b8  _GLOBAL__I_4ad2b8
//   [ ] 0x4ad2c8  CKHkS08TransportableKey_OnActivate
//   [ ] 0x4ad3e0  CKHkS08TransportableKey_vf154
//   [ ] 0x4ad4b0  CKHkS08TransportableKey_vfFC
//   [ ] 0x4ad5b0  CKHkS08TransportableKey_vf170
//   [ ] 0x4ad5e0  CKHkS08TransportableKey_vf174
//   [ ] 0x4ad610  CKHkS08TransportableKey_BaseDestructor
//   [ ] 0x4ad640  CKHkS08TransportableKey_DeletingDestructor
//   [ ] 0x4ad688  CKHkS08TransportableKey_Destructor
//   [ ] 0x4ad6b8  CKHkS08TransportableKey_State1
//   [ ] 0x4ad8f0  CKHkS08TransportableKey_OnDeactivate
//   [ ] 0x4ada30  CKHkS08TransportableKey_vf164
//   [ ] 0x4adb08  CKHkS08TransportableKey_Restart
//   [ ] 0x4adcf0  CKHkS08TransportableKey_vf160
//   [ ] 0x4ae250  CKHkS08TransportableKey_PlayImpactFeedback_maybe
//   [ ] 0x4ae688  CKHkS08TransportableKey_State2
//   [x] 0x4aebf8  CKHkS08TransportableKey_Create
//   [x] 0x4aec80  CKHkS08TransportableKey_CreateArray
//   [ ] 0x4aed80  CKHkS08TransportableKey_FindGroundPointByRaising_maybe  [dead]
//   [x] 0x4aeee8  CKHkS08TransportableKey_Load
//   [x] 0x4af358  CKHkS08TransportableKey_Start
//   [ ] 0x4af510  CKHkS08TransportableKey_vf10C
//   [ ] 0x4af670  CKHkS08TransportableKey_vf108
//   [ ] 0x4af750  CKHkS08TransportableKey_vf134
//   [ ] 0x4af8e8  CKHkS08TransportableKey_ResetStateMachine_maybe
//   [ ] 0x4af9a8  CKHkS08TransportableKey_vfF8
//   [ ] 0x4afd08  CKHkS08TransportableKey_vfF0
//   [ ] 0x4aff00  CKHkS08TransportableKey_Update
//
//   [ ] 0x9c52f8  CKHkS08TransportableKey_vf12C  [inline]
//   [ ] 0x9c5300  CKHkS08TransportableKey_vf130  [inline]
//   [ ] 0x9c5308  CKHkS08TransportableKey_vf140  [inline]
//   [ ] 0x9c5350  CKHkS08TransportableKey_vf144  [inline]
//   [ ] 0x9c5358  CKHkS08TransportableKey_vf148  [inline]
//   [ ] 0x9c5360  CKHkS08TransportableKey_vf14C  [inline]
//   [ ] 0x9c5368  CKHkS08TransportableKey_vf150  [inline]
//   [ ] 0x9c53b8  CKHkS08TransportableKey_IsKindOfClass  [inline]
//   [ ] 0x9c5418  CKHkS08TransportableKey_GetClassType  [inline]
//   [ ] 0x9c5420  CKHkS08TransportableKey_GetClassID  [inline]
//   [ ] 0x9c5428  CKHkS08TransportableKey_vf114  [inline]
//   [ ] 0x9c5430  CKHkS08TransportableKey_vf118  [inline]
//   [ ] 0x9c5438  CKHkS08TransportableKey_vf138  [inline]
//   [ ] 0x9c5440  CKHkS08TransportableKey_vf13C  [inline]
//   [ ] 0x9c5448  CKHkS08TransportableKey_vf158  [inline]
//   [ ] 0x9c5450  CKHkS08TransportableKey_vf15C  [inline]
//   [ ] 0x9c5458  CKHkS08TransportableKey_vf184  [inline]
//   [ ] 0x9c5460  CKHkS08TransportableKey_vf104  [inline]
#include "Spyro2008/hooks/CKHkS08TransportableKey.h"
#include "k2000/core/Ps3MemberFn.h"
#include "Spyro2008/groups/C22SpyroShims.h"

#include "k2000/io/IKFile.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/geometry/CGeometry.h"

// 0x004acfe0 CKHkS08TransportableKey_PostLoad: KBase3002_PostLoad; for the level type two RwMatrixCreate_Thunk matrices
// (+0xec, orthonormalised in place, and +0x108), +0x40 = 0 and bit 2 (hidden) of the hook's scene node (+0x1c); for
// the other types only +0x40 = 0.
int32_t CKHkS08TransportableKey::PostLoad(int32_t type) {
    CKHkS08TransportableBase::PostLoad(type);
    if (type != K_LEVEL_PLATEFORMS) {
        m_unk40 = 0;
        return 1;
    }
    CMatrix34* matrix = RwMatrixCreate_Thunk();
    m_unkEC = matrix;
    Mat4_OrthoNormalizeInPlace(matrix);
    m_unk108 = RwMatrixCreate_Thunk();
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    m_unk40 = static_cast<uint32_t>(type);
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
    return 1;
}

// 0x004aeee8 CKHkS08TransportableKey_Load
int32_t CKHkS08TransportableKey::Load(IKFile* file, int32_t type) {
    CKHkS08TransportableBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_unk78);
        ReadF32LE(file, &m_unk7c);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk98), 3);
        ReadF32LE(file, &m_unkB4);
        ReadF32LE(file, &m_unkB8);
        ReadF32LE(file, &m_unkE8);
        ReadF32LE(file, &m_unkF8);
        ReadF32LE(file, &m_unkF4);
        ReadF32LE(file, &m_unkF0);
        IKFile_ReadRef(file, &m_unk44);
        IKFile_ReadRef(file, &m_unk34);
        IKFile_ReadRef(file, &m_unk3c);
        IKFile_ReadRef(file, &m_unk38);
    }
    return 1;
}

namespace {
// DOTD: the key's state handlers by descriptor (k2000/core/Ps3MemberFn.h; the table Start builds at +0x118).
Ps3MemberFnEntry<CKHkS08TransportableKey::StateFn> g_keyStates[] = {
    {0x00bc7420u, nullptr, "CKHkS08TransportableKey_State0_maybe 0x4ad0b0 (C2.8: carrying)", false},
    {0x00bc74c0u, nullptr, "CKHkS08TransportableKey_State1 0x4ad6b8 (C2.8: carrying)", false},
    {0x00bc7578u, nullptr, "CKHkS08TransportableKey_State2 0x4ae688 (C2.8: carrying)", false},
};
}  // namespace

uint8_t CKHkS08TransportableKey::CallState(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other) {
    StateFn fn = ResolvePs3MemberFn(g_keyStates, pair, "CKHkS08TransportableKey state handler");
    if (fn == nullptr) return other;
    return (this->*fn)(clock, phase, other);
}

// 0x004af358 CKHkS08TransportableKey_Start
void CKHkS08TransportableKey::Start() {
    CKHkS08TransportableBase::Start();  // 0x004ac060: +0x25 = 1, +0x28 = 0, vt+0x144 with 0

    // The state engine: a table of three handlers at +0x118 (the PS3 descriptors of the key's State0 / State1 /
    // State2, TOC +0x63c4 / +0x63c0 / +0x63c8), which +0x110 points to.
    // CallState maps them to the native handlers (g_keyStates; the update that runs them is C2.8).
    m_unk118[0] = 0x00bc7420u;
    m_unk118[2] = 0x00bc74c0u;
    m_unk118[4] = 0x00bc7578u;
    m_unk118[3] = 0;
    m_unk118[1] = 0;
    m_unk118[5] = 0;
    m_unk115 = 3;
    m_unk114 = 0xff;
    m_pUnk110 = &m_unk118[0];
    m_unk48 = 0;
    m_GContactInOut.m_eContactStatus = 3;
    m_GContactInOut.m_ui8SectorNumber = 0;
    m_GContactInOut.m_pGround = nullptr;
    m_GContactInOut.m_i32FaceIndex = -1;
    m_unk24 = 0;
    c22spyro::SetBeByte(m_unkBC[0], 1, 0);  // the byte at +0xbd
    m_unkBC[1] = 0;                          // +0xc0
    m_unkBC[2] = 0x7f7fffffu;  // +0xc4..+0xcc: FLT_MAX x3 (the vector 0xc50da0, set by StaticInitAndDestruction_11578)
    m_unkBC[3] = 0x7f7fffffu;
    m_unkBC[4] = 0x7f7fffffu;
    m_unkBC[5] = 0;  // +0xd0..+0xd8: the zero vector 0xc50d64
    m_unkBC[6] = 0;
    m_unkBC[7] = 0;
    m_unkBC[8] = 0xffffffffu;  // +0xdc
    m_unkBC[10] = 0;           // +0xe4
    c22spyro::SetBeByte(m_unkBC[9], 0, 0);  // the byte at +0xe0
    m_unkFC[0] = 0x7f7fffffu;  // +0xfc..+0x104: FLT_MAX x3 (the vector 0xc50da0)
    m_unkFC[1] = 0x7f7fffffu;
    m_unkFC[2] = 0x7f7fffffu;
    c22spyro::SetBeByte(m_unk10C, 0, 0);  // the byte at +0x10c
    m_pad2D[0] = 0;                       // the byte at +0x2d
    m_unk30 = 0;
    if (m_unk38 != nullptr) {
        // The node's geometries that are of render kind 2 (bits 8-9 of their properties) get the low six bits 0x2e.
        CNode* node = static_cast<CNode*>(m_unk38);
        for (CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList); geometry != nullptr;
             geometry = geometry->m_pNext) {
            if (((geometry->m_BitProperties >> 8) & 3u) == 2u) {
                geometry->m_BitProperties = (geometry->m_BitProperties & 0xffffffc0u) | 0x2eu;
            }
        }
        node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
    }
}
