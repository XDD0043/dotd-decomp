// CKSparkFxData.cpp - reconstructed original translation unit 0x1d3908-0x1d3e68 (GAME_TOC1, main_toc1), 11 functions, 9 live.
// Primary owner: CKSparkFxData (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1d3908  CKSparkFxData_ConstructBase_maybe
//   [x] 0x1d3930  CKSparkFxData_GetNodeClassKey
//   [ ] 0x1d3938  KStub_Nop_1d3938  [dead]
//   [x] 0x1d3940  CKSparkFxData_PostLoad
//   [x] 0x1d39c8  CKSparkFxData_Load
//   [ ] 0x1d3a88  CKSparkFxData_Save
//   [x] 0x1d3ab0  CKSparkFxData_LevelReset  (RecursiveRegistration: KStub_Return1_1d8340, nothing: the IKSerializable default slot)
//   [ ] 0x1d3ad8  CKSparkFxData_ConstructBase_2_maybe  [dead]
//   [x] 0x1d3b00  CKSparkFxData_HandleMessage  (MessageProc)
//   [x] 0x1d3e18  CKSparkFxData_vf40  (GetInfo: 1, the default)
//   [x] 0x1d3e20  CKSparkFxData_ClearReferences  (Destroy)
//
//   [ ] 0x9ad310  CKSparkFxData_IsKindOf  [inline]
//   [x] 0x9ad348  CKSparkFxData_GetClassGroup  [inline]
//   [x] 0x9ad350  CKSparkFxData_GetClassId  [inline]
//   [ ] 0x9ad358  CKSparkFxData_DeletingDestructor  [inline]
//   [ ] 0x9ad3b0  CKSparkFxData_Destructor  [inline]
#include "k2000/fx/CKSparkFxData.h"
#include "Renderware/rwcore/RwMatrix.h"

#include <cstring>

#include "k2000/fx/IKFx.h"
#include "k2000/io/IKFile.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/math/Quat.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvFx.h"

// 0x001d3908 CKSparkFxData_ConstructBase_maybe, in its store order.
CKSparkFxData::CKSparkFxData() {
    m_unk14 = nullptr;
    m_pSparkParam = nullptr;
    m_unk0c = nullptr;
    m_unk10 = nullptr;
}

// 0x001d39c8 CKSparkFxData_Load
int32_t CKSparkFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pSparkParam);
    return 1;
}

// 0x001d3940 CKSparkFxData_PostLoad (TOC1 -0x19ec 1.0): the matrix's flags 0x20003, rows identity, position 0.
int32_t CKSparkFxData::PostLoad(int32_t type) {
    if (type != 0) return 1;
    RwMatrix* m = RwMatrixCreate();  // 0x0023fa68
    m_unk14 = m;
    m->flags = 0x20003u;
    m->right = {1.0f, 0.0f, 0.0f};
    m->pos = {0.0f, 0.0f, 0.0f};
    m->at = {0.0f, 0.0f, 1.0f};
    m->up = {0.0f, 1.0f, 0.0f};
    return 1;
}

// 0x001d3e20 CKSparkFxData_ClearReferences (Destroy)
void CKSparkFxData::Destroy() {
    if (m_unk14 == nullptr) return;
    RwMatrixDestroy(static_cast<RwMatrix*>(m_unk14));  // RwMatrixDestroy_Thunk 0x23f968
    m_unk14 = nullptr;
}

namespace {
// The 0x1b00 payload (as CKShockWaveFxData's): a position at +0x04 and a quaternion at +0x10.
struct SparkPlacement {
    uint32_t m_unk00;
    float m_pos[3];   // +0x04
    float m_quat[4];  // +0x10
};
}  // namespace

// 0x001d3b00 CKSparkFxData_HandleMessage (MessageProc)
int32_t CKSparkFxData::MessageProc(uint16_t message, void* data) {
    if (message != 0x1b00) return 1;
    const SparkPlacement* object = nullptr;
    std::memcpy(&object, data, sizeof(object));
    if (object == nullptr) return 0;
    CMatrix34* matrix = static_cast<CMatrix34*>(m_unk14);
    Quat_ToMatrixNormalizing(object->m_quat, matrix);  // 0x241d78
    matrix->m_pos = CVector3{object->m_pos[0], object->m_pos[1], object->m_pos[2]};
    matrix->m_ui32Flags &= ~0x20000u;
    IKFx* node = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(this, this);  // TOC1 -0x19e8 -> +0x60
    // BUG(original): the release goes through the found effect even when none was free (null: a fault on the PS3);
    // natively skipped.
    if (node != nullptr) node->ReleaseReservation(this);  // vt+0x54
    return 0;
}
