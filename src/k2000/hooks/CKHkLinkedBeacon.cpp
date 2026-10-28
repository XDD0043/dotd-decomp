// CKHkLinkedBeacon.cpp - reconstructed original translation unit 0x44ae90-0x450480 (GAME_TOC1, main_toc1), 36 functions, 33 live.
// Primary class: CKHkLinkedBeacon  key 0x1002  category Hook  size 0xf4  vtable 0xb26cb8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x44ae90  RegisterCKHkLinkedBeaconClass
//   [ ] 0x44af08  _GLOBAL__I_44af08
//   [ ] 0x44af18  CKHkLinkedBeacon_ShowInputIcon_maybe
//   [ ] 0x44b2b0  CKHkLinkedBeacon_GetInfo
//   [ ] 0x44b3e0  CKHkLinkedBeacon_BeginLinkStage_maybe
//   [ ] 0x44b710  CKHkLinkedBeacon_Resume
//   [ ] 0x44b738  CKHkLinkedBeacon_Pause
//   [ ] 0x44b760  CKHkLinkedBeacon_Stop
//   [x] 0x44b788  CKHkLinkedBeacon_Start
//   [ ] 0x44b810  CKHkLinkedBeacon_PostLoad
//   [ ] 0x44b838  CKHkLinkedBeacon_Save
//   [ ] 0x44b860  CKHkLinkedBeacon_RecursiveRegistration
//   [ ] 0x44b888  CKHkLinkedBeacon_Destroy
//   [x] 0x44b940  CKHkLinkedBeacon_DeleteArray
//   [x] 0x44b9e0  CKHkLinkedBeacon_Construct  [dead]
//   [ ] 0x44ba18  CKHkLinkedBeacon_DeletingDestructor
//   [ ] 0x44ba60  CKHkLinkedBeacon_Destructor
//   [ ] 0x44ba90  CKHkLinkedBeacon_BaseDestructor
//   [ ] 0x44bac0  CKHkLinkedBeacon_Construct_2  [dead]
//   [ ] 0x44baf8  CKHkLinkedBeacon_vfC8
//   [x] 0x44bb58  CKHkLinkedBeacon_SetDefaultState
//   [x] 0x44bbd8  CKHkLinkedBeacon_Create
//   [x] 0x44bc30  CKHkLinkedBeacon_CreateArray
//   [ ] 0x44bce0  CKHkLinkedBeacon_SaveLinkRecord_maybe  [dead]
//   [ ] 0x44be70  CKHkLinkedBeacon_OnActivate
//   [x] 0x44bf20  CKHkLinkedBeacon_Restart
//   [x] 0x44c0b8  CKHkLinkedBeacon_LoadLinkRecord_maybe
//   [x] 0x44c240  CKHkLinkedBeacon_Load
//   [ ] 0x44cbb8  CKHkLinkedBeacon_SwitchOn_maybe
//   [ ] 0x44d518  CKHkLinkedBeacon_SwitchOff_maybe
//   [ ] 0x44d838  CKHkLinkedBeacon_OnDeactivate
//   [ ] 0x44d908  CKHkLinkedBeacon_ExecuteLinkAction_maybe
//   [ ] 0x44dee0  CKHkLinkedBeacon_UpdateConditionalLinks_maybe
//   [ ] 0x44e2c8  CKHkLinkedBeacon_MessageProc
//   [ ] 0x44eb40  CKHkLinkedBeacon_UpdateCurrentStage_maybe
//   [ ] 0x44f620  CKHkLinkedBeacon_Update
//
//   [ ] 0x9c3c18  CKHkLinkedBeacon_IsKindOfClass  [inline]
//   [ ] 0x9c3c70  CKHkLinkedBeacon_GetClassType  [inline]
//   [ ] 0x9c3c78  CKHkLinkedBeacon_GetClassID  [inline]
//   [ ] 0x9c3c80  CKHkLinkedBeacon_GetTriggerPropA7  [inline]
//   [ ] 0x9c3c90  CKHkLinkedBeacon_GetTriggerPropA6  [inline]
#include "k2000/hooks/CKHkLinkedBeacon.h"

#include <cstring>

#include "k2000/io/IKFile.h"
#include "k2000/core/Stub.h"
#include "k2000/logic/ai/CKKLBCharacterBase.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/logic/sound/CKSound.h"

namespace {
// One 12-byte read, then each word byte-swapped (the PS3's Read(0xc) + three lwbrx).
void ReadVector3Words(IKFile* file, CVector3* v) {
    uint32_t w[3];
    ReadU32LEWords(file, w, 3);
    std::memcpy(v, w, sizeof(w));
}
}  // namespace

// 0x0044c0b8 CKHkLinkedBeacon_LoadLinkRecord_maybe: a reference, then five single bytes (+4, +6, +5, +7, +8).
void CKHkLinkedBeacon::LoadLinkRecord(IKFile* file, LinkRecord* record, int32_t /*unused*/) {
    IKFile_ReadRef(file, &record->m_pTarget);
    ReadU8(file, &record->m_unk4);
    ReadU8(file, &record->m_unk6);
    ReadU8(file, &record->m_unk5);
    ReadU8(file, &record->m_unk7);
    ReadU8(file, &record->m_unk8);
}

// 0x0044c240 CKHkLinkedBeacon_Load
int32_t CKHkLinkedBeacon::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadVector3Words(file, &m_unk20);
    ReadVector3Words(file, &m_unk2C);
    ReadU32LE(file, &m_unk38);
    ReadU8(file, &m_unk50);
    IKFile_ReadRef(file, &m_unk54);
    IKFile_ReadRef(file, &m_unk58);
    IKFile_ReadRef(file, &m_unkC8);
    ReadF32LE(file, &m_unk3C);
    ReadU32LE(file, &m_unk40);
    ReadU32LE(file, &m_unk44);
    ReadF32LE(file, &m_unk48);
    ReadF32LE(file, &m_unk4C);
    m_unk88.Load(file, K_LEVEL_PLATEFORMS);
    m_unk90.Load(file, K_LEVEL_PLATEFORMS);
    m_unk98.Load(file, K_LEVEL_PLATEFORMS);
    m_unkA0.Load(file, K_LEVEL_PLATEFORMS);
    m_unkA8.Load(file, K_LEVEL_PLATEFORMS);
    IKFile_ReadRef(file, &m_unkB0);
    if ((m_bitArray & 0x10u) == 0) {
        m_unk68 = 0;
        m_unk6C = 0x1.99999ap-1f;  // 0.8f (TOC 0x3f4ccccd)
        m_unk64 = nullptr;
    } else {
        IKFile_ReadRef(file, &m_unk64);
        ReadU8(file, &m_unk68);
        ReadF32LE(file, &m_unk6C);
    }
    ReadS32LE(file, &m_unk5C);
    m_apUnk60 = new IKSerializable*[static_cast<uint32_t>(m_unk5C)];  // OperatorNewArray(count * 4)
    for (int32_t i = 0; i < m_unk5C; ++i) IKFile_ReadRef(file, &m_apUnk60[i]);
    ReadS32LE(file, &m_unkB4);
    m_apLinks = new LinkRecord*[static_cast<uint32_t>(m_unkB4)];  // OperatorNewArray(count * 4)
    for (int32_t i = 0; i < m_unkB4; ++i) {
        LinkRecord* record = new LinkRecord;  // OperatorNew(0xc), +8, +0, +4 = 0
        record->m_pTarget = nullptr;
        std::memset(&record->m_unk4, 0, 8);
        m_apLinks[i] = record;
        LoadLinkRecord(file, m_apLinks[i], 0);
    }
    ReadU8(file, &m_unkBC);
    ReadF32LE(file, &m_unk70);
    ReadU8(file, &m_unk74);
    ReadVector3Words(file, &m_unk78);
    ReadU32LE(file, &m_unk84);
    IKFile_ReadRef(file, &m_unkC0);
    IKFile_ReadRef(file, &m_unkC4);
    return 1;
}

// 0x0044b788 CKHkLinkedBeacon_Start: the character's Start (vt+0x50 of m_unkC8), the icon effect forgotten,
// then vt+0x54.
void CKHkLinkedBeacon::Start() {
    CKHkActorBase::Start();
    static_cast<CKKLBCharacterBase*>(m_unkC8)->Vf50();
    m_pInputIconFx = nullptr;
    Restart();
}

// 0x0044bb58 CKHkLinkedBeacon_SetDefaultState: state 0, or a beacon with bit 11, gets bit 18 set.
void CKHkLinkedBeacon::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);
    if (flag == 0 || (m_bitArray & 0x800) != 0) m_bitArray = (m_bitArray & 0xfffbffffu) | 0x40000u;
}

// 0x0044af18 CKHkLinkedBeacon_ShowInputIcon_maybe. STUB(C2.2): see the header.
void CKHkLinkedBeacon::ShowInputIcon(int32_t on) {
    if (on != 0) DOTD_STUB_ONCE("CKHkLinkedBeacon_ShowInputIcon_maybe: acquire the input-icon effect (C2.2, services)");
    if (on == 0) m_pInputIconFx = nullptr;
}

// 0x0044bf20 CKHkLinkedBeacon_Restart. A beacon that is not finished (bit 2 clear): when it was active (bit 17)
// its marker byte (+0x2d bit 1 of m_unkB0's object), sound and sekens are stopped, the character restarted
// (vt+0x54 of m_unkC8) and the icon hidden; then the active bits become 0x800000 (bit 23 only among the
// cleared mask 0xe345ffff), the sekens and the link-state marker reset and every link record's byte +9
// cleared. STUB(C2.2): CKSekensLauncherCpnt_StopSekens_maybe (needs CKSrvSekensor's cancel) is not ported.
void CKHkLinkedBeacon::Restart() {
    if ((m_bitArray & 4) != 0) return;
    if ((m_bitArray & 0x20000) != 0) {
        if (m_unkB0 != nullptr) {
            // The object is not identified in the structure draft: its byte at +0x2d loses bit 1.
            uint8_t* flags = reinterpret_cast<uint8_t*>(m_unkB0) + 0x2d;
            *flags = static_cast<uint8_t>(*flags & 0xfc | (*flags & 1));
        }
        if (m_unkC4 != nullptr) {
            CKSoundDictionaryID* dictionary = static_cast<CKSoundDictionaryID*>(m_unkC4);
            if (CKSoundDictionaryID_GetSound(dictionary, 0) != nullptr) {
                Sound_Stop(CKSoundDictionaryID_GetSound(dictionary, 0), 0);
            }
        }
        if (m_pSekens != nullptr) {
            DOTD_STUB_ONCE("CKSekensLauncherCpnt_StopSekens_maybe (C2.2)");
            m_pSekens = nullptr;
        }
        static_cast<CKKLBCharacterBase*>(m_unkC8)->Vf54();  // vt+0x54
        ShowInputIcon(0);
    }
    m_bitArray = (m_bitArray & 0xe345ffffu) | 0x800000u;
    m_pSekens = nullptr;
    m_unkEC = 0xff;
    for (int32_t i = 0; i < m_unkB4; ++i) m_apLinks[i]->m_unk9 = 0;
}
