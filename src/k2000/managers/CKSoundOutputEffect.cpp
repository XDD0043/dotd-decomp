// CKSoundOutputEffect.cpp - reconstructed original translation unit 0x115058-0x115b70 (GAME_TOC1, main_toc1), 15 functions, 14 live.
// Primary class: CKSoundOutputEffect  key 0x140  category Manager  size 0xc  vtable 0xb199a8
// Other owners: PtrList (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x115058  CKSoundOutputEffect_Delete
//   [x] 0x1150a8  CKSoundOutputEffect_RecursiveRegistration  (CKSoundOutputEffect::RecursiveRegistration)
//   [ ] 0x115108  RegisterCKSoundOutputEffectClass
//   [ ] 0x115180  _GLOBAL__I_115180
//   [x] 0x115190  CKSoundOutputEffect_DeleteArray
//   [x] 0x115238  CKSoundOutputEffect_CreateArray
//   [x] 0x1152e0  CKSoundOutputEffect_Create
//   [x] 0x115320  CKSoundOutputEffect_GetInfo  (GetInfo: 1, IKSerializable's default)
//   [x] 0x115328  CKSoundOutputEffect_MessageProc  (CKSoundOutputEffect::MessageProc)
//   [x] 0x115398  CKSoundOutputEffect_PostLoad  (PostLoad: 1, IKSerializable's default)
//   [x] 0x1153a0  CKSoundOutputEffect_Destroy
//   [x] 0x1153c8  CKSoundOutputEffect_Load
//   [ ] 0x115768  CKSoundOutputEffect_Save
//   [x] 0x115b00  KStub_Nop_115b00  (empty)
//   [ ] 0x115b08  PtrList_FindByHash_maybe  [dead]
//
//   [ ] 0x9a6c18  CKSoundOutputEffect_GetClassType  [inline]
//   [ ] 0x9a6c20  CKSoundOutputEffect_GetClassID  [inline]
//   [x] 0x9a6c28  CKSoundOutputEffect_Destructor  [inline]
//   [ ] 0x9a6c40  CKSoundOutputEffect_IsKindOfClass  [inline]
//   [x] 0x9a6c60  CKSoundOutputEffect_DeletingDestructor  [inline]
#include "k2000/managers/CKSoundOutputEffect.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/sound/CKSoundOutput.h"

// 0x001152e0 CKSoundOutputEffect_Create (the constructor is inlined there)
CKSoundOutputEffect::CKSoundOutputEffect() { m_rwaOutputEffect = nullptr; }

// 0x00115328 CKSoundOutputEffect_MessageProc
int32_t CKSoundOutputEffect::MessageProc(uint16_t message, void* /*data*/) {
    if (message != 0x100) return 1;
    g_pEngine->m_soundManager->m_pOutput->SetCurrentEffect(this);  // 0x00114578
    return 0;
}

// 0x001150a8 CKSoundOutputEffect_RecursiveRegistration
void CKSoundOutputEffect::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}

// 0x001153c8 CKSoundOutputEffect_Load: one 4-byte read per field, each swapped.
int32_t CKSoundOutputEffect::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU32LE(file, &m_unk08);
        RwaEnvironment* environment = static_cast<RwaEnvironment*>(Mem_AllocAligned16(sizeof(RwaEnvironment)));
        m_rwaOutputEffect = environment;
        ReadS32LE(file, &environment->room);
        ReadS32LE(file, &m_rwaOutputEffect->roomHF);
        ReadF32LE(file, &m_rwaOutputEffect->roomRolloffFactor);
        ReadF32LE(file, &m_rwaOutputEffect->decayTime);
        ReadF32LE(file, &m_rwaOutputEffect->decayHFRatio);
        ReadS32LE(file, &m_rwaOutputEffect->reflections);
        ReadF32LE(file, &m_rwaOutputEffect->reflectionsDelay);
        ReadS32LE(file, &m_rwaOutputEffect->reverb);
        ReadF32LE(file, &m_rwaOutputEffect->reverbDelay);
        ReadF32LE(file, &m_rwaOutputEffect->diffusion);
        ReadF32LE(file, &m_rwaOutputEffect->density);
        ReadF32LE(file, &m_rwaOutputEffect->hfReference);
    }
    return 1;
}

// 0x001153a0 CKSoundOutputEffect_Destroy
void CKSoundOutputEffect::Destroy() { Mem_FreeAligned16(m_rwaOutputEffect); }
