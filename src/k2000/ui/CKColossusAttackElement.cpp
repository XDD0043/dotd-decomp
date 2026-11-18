//
// Reconstructed original translation unit: 0x9c4338-0x9d0110 (GAME_TOC2, tail_toc2), 53 functions, 52 live.
// Primary owner: CKColossusAttackElement (not a registered class)
// Other owners: GolemPhaseCondBase (2), KBaseE8D (2), CgGLState (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x9c4338  CKColossusAttackElement_IsSpyroWithinRadiusXZ_maybe  (ColossusCond_IsHeroWithinRadiusXZ)
//   [x] 0x9c43e8  CKColossusAttackElement_IsSpyroBeyondRadius_maybe  (ColossusCond_IsHeroBeyondRadius)
//   [x] 0x9c5848  GolemPhaseCondBase_DeletingDestructor  (GolemPhaseCond's virtual destructor, then delete: GolemPhaseCondAnd.h)
//   [x] 0x9c5878  GolemPhaseCondBase_Destructor  (GolemPhaseCond's virtual destructor (the vtable only): GolemPhaseCondAnd.h)
//   [x] 0x9c8618  KBaseE8D_DeletingDestructor  (~KBaseE8D, then delete: KBaseE8D.h)
//   [x] 0x9c8658  KBaseE8D_vf0  (~KBaseE8D: KBaseE8D.h)
//   [ ] 0x9cd728  CgGLState_EnableFlag_Reset_maybe  [platform]  (the Cg runtime's GL state assignments (cgGL state tables at 0xc1fca8 / 0xc1fcac): the GL port binds its own state (platform/gfx))
//   [ ] 0x9cd7c8  CgGLState_EnableFlag_Set_maybe  [platform]  (the Cg runtime's GL state assignments (cgGL state tables at 0xc1fca8 / 0xc1fcac): the GL port binds its own state (platform/gfx))
//   [ ] 0x9cd960  FUN_009cd960  [dead]
//   [ ] 0x9cda78  KStub_ReturnM1_9cda78  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cda80  KStub_Return0_9cda80  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cda88  std_codecvt_char_do_unshift_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cda98  std_codecvt_char_do_out_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cdaa8  std_codecvt_char_do_in_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cdab8  std_codecvt_char_do_length_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cdad0  KStub_Return0_9cdad0  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cdad8  KStub_Nop_9cdad8  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cdae0  KStub_Nop_9cdae0  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cdd88  std_basic_ios_DeletingDestructor_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cddd0  std_basic_ios_Destructor_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cde00  std_streambuf_Unlock_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cde30  std_streambuf_Lock_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cde60  KStub_ReturnM1_9cde60  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cde68  KStub_ReturnM1_9cde68  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cde70  std_filebuf_sync_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cdef8  std_streambuf_xsputn_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9ce020  std_streambuf_seekoff_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9ce078  std_streambuf_seekpos_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9ce0e0  std_filebuf_underflow_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9ce1d8  std_ctype_char_do_tolower_range_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9ce230  std_ctype_char_do_toupper_range_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9ce288  std_filebuf_pbackfail_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9ce440  std_streambuf_uflow_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9ce4d0  std_streambuf_xsgetn_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9ce620  std_codecvt_base_DeletingDestructor_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9ce650  std_codecvt_base_Destructor_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9ce660  std_codecvt_char_Destructor_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cec40  std_codecvt_char_DeletingDestructor_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cec80  std_ctype_char_DeletingDestructor_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9ced28  std_ctype_char_Destructor_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cedb0  std_filebuf_setbuf_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cef68  std_filebuf_imbue_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cf1f0  std_stream_DeletingDestructor_VirtualThunk_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cf208  std_stream_DeletingDestructor_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cf268  std_stream_Destructor_VirtualThunk_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cf280  std_stream_Destructor_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cf2c0  std_streambuf_DeletingDestructor_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cf3d8  std_streambuf_Destructor_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cf4e8  std_filebuf__Endwrite_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cf950  std_filebuf_seekpos_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cfb50  std_filebuf_seekoff_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cfd28  std_filebuf_DeletingDestructor_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)
//   [ ] 0x9cff28  std_filebuf_Destructor_maybe  [platform]  (the C++ runtime's std::codecvt / ctype / basic_ios / streambuf / filebuf (vtables 0xb30648..0xb32830): the host standard library)

#include "k2000/ui/CKColossusAttackElement.h"

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwTypes.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "crt/ppc_ops.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGLeaf.h"

namespace {
const float kZero = 0.0f;  // TOC1 +0x587c (0x00000000)

// The hook's node frame position (hook +0x1c, node +0x04 frame, modelling +0x40).
const RwV3d& NodePosition(IKHook* hook) { return static_cast<CSGLeaf*>(hook->m_pKGLObject)->m_pRwFrame->modelling.pos; }
// Hero 0 (GetHeroByDragonIndex 0x2ca080 of the game manager's hero group, +0x8c -> +0x08).
IKHook* Hero0() {
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);
    return static_cast<CKHkS08Hero*>(group->m_apHeros[0]);  // 0x002ca080
}
}  // namespace

// 0x009c4338 CKColossusAttackElement_IsSpyroWithinRadiusXZ_maybe
bool ColossusCond_IsHeroWithinRadiusXZ(IKHook* hook, float radius) {
    const RwV3d& hero = NodePosition(Hero0());
    const RwV3d& at = NodePosition(hook);
    const float r2 = radius * radius;
    const float dx = hero.x - at.x;
    const float dz = hero.z - at.z;
    const float d2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, kZero));
    return d2 < r2;  // blt
}

// 0x009c43e8 CKColossusAttackElement_IsSpyroBeyondRadius_maybe
bool ColossusCond_IsHeroBeyondRadius(IKHook* hook, float radius) {
    const RwV3d& hero = NodePosition(Hero0());
    const RwV3d& at = NodePosition(hook);
    const float r2 = radius * radius;
    const float dy = hero.y - at.y;
    const float dx = hero.x - at.x;
    const float dz = hero.z - at.z;
    const float d2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
    return d2 > r2;  // bgt
}
