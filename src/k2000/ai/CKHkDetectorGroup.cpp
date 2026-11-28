// CKHkDetectorGroup.cpp - reconstructed original translation unit 0x5bc3e0-0x5bdfd8 (GAME_TOC2, main_toc2), 33 functions, 29 live.
// Primary owner: CKHkDetectorGroup (not a registered class)
// Other owners: RegisterCKHkDetectorGroupClass (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5bc3e0  CKHkDetectorGroup_Destroy
//   [x] 0x5bc430  CKHkDetectorGroup_Construct  [dead]
//   [ ] 0x5bc480  CKHkDetectorGroup_IsPointInDetectorVolume_maybe  [dead]
//   [ ] 0x5bc5a0  RegisterCKHkDetectorGroupClass
//   [ ] 0x5bc618  _GLOBAL__I_5bc618
//   [x] 0x5bc628  CKHkDetectorGroup_PostLoad
//   [x] 0x5bc6c0  CKHkDetectorGroup_DestroyArray
//   [ ] 0x5bc760  CKHkDetectorGroup_Construct_2  [dead]
//   [x] 0x5bc7b0  CKHkDetectorGroup_vf40
//   [x] 0x5bc840  CKHkDetectorGroup_HandleMessage
//   [x] 0x5bca38  CKHkDetectorGroup_RestoreCheckpointState_maybe
//   [x] 0x5bcb48  CKHkDetectorGroup_ResetToInitialState_maybe
//   [x] 0x5bcc30  CKHkDetectorGroup_vf78  (Resume, vt+0x78, empty)
//   [x] 0x5bcc38  CKHkDetectorGroup_vf68  (Stop, vt+0x68, empty)
//   [x] 0x5bcc40  CKHkDetectorGroup_vf70  (Pause, vt+0x70, empty)
//   [x] 0x5bcc48  CKHkDetectorGroup_ClearReferences  (Destroy, vt+0x10)
//   [x] 0x5bccd0  CKHkDetectorGroup_vf50
//   [x] 0x5bcce0  CKHkDetectorGroup_vf54
//   [x] 0x5bcd00  CKHkDetectorGroup_OnActivate
//   [x] 0x5bcd10  CKHkDetectorGroup_OnDeactivate (empty: IKLife's)
//   [x] 0x5bcd18  CKHkDetectorGroup_LoadDetector_maybe
//   [x] 0x5bcf88  CKHkDetectorGroup_CreateArray
//   [x] 0x5bd050  CKHkDetectorGroup_Create
//   [x] 0x5bd0b8  CKHkDetectorGroup_Load
//   [x] 0x5bd430  CKHkDetectorGroup_LevelReset  (RecursiveRegistration, vt+0x24)
//   [ ] 0x5bd458  CKHkDetectorGroup_Save
//   [x] 0x5bd480  CKHkDetectorGroup_Destructor  (the implicit destructor)
//   [x] 0x5bd4a0  CKHkDetectorGroup_TestDetector_maybe
//   [x] 0x5bda08  CKHkDetectorGroup_EvaluateConditions_maybe
//   [x] 0x5bdc38  CKHkDetectorGroup_IsTriggered_maybe
//   [x] 0x5bdc60  CKHkDetectorGroup_Update
//   [x] 0x5bdf68  CKHkDetectorGroup_DeletingDestructor  (the implicit destructor)
//   [ ] 0x5bdfb8  CKHkDetectorGroup_Destructor_2  [dead]
//
//   [ ] 0x9ccfe0  CKHkDetectorGroup_GetClassGroup  [inline]
//   [ ] 0x9ccfe8  CKHkDetectorGroup_GetClassId  [inline]
//   [ ] 0x9ccff0  CKHkDetectorGroup_vfC0  [inline]
//   [ ] 0x9cd000  CKHkDetectorGroup_vfC8  [inline]
//   [x] 0x9cd008  CKHkDetectorGroup_GetTriggerProp4  [inline]
//   [x] 0x9cd050  CKHkDetectorGroup_GetTriggerProp5  [inline]
//   [ ] 0x9cd060  CKHkDetectorGroup_IsKindOf  [inline]
//   [ ] 0x9cd0a8  KBase2D82_Destructor  [inline]
//   [ ] 0x9cd0c8  KBase2D82_DeletingDestructor  [inline]
//   [ ] 0x9cd110  KBase9B0C_vf8  [inline]
//   [ ] 0x9cd138  KBase9B0C_vf14  [inline]
//   [ ] 0x9cd140  KBase9B0C_vf18  [inline]
#include "k2000/ai/CKHkDetectorGroup.h"

#include "k2000/core/IKInfo.h"

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"

// 0x005bcd18 CKHkDetectorGroup_LoadDetector_maybe
int32_t CKHkDetectorGroup::LoadDetector(IKFile* file, int32_t /*type*/, Detector* detector) {
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(detector->m_aBox), 6);  // one Read(0x18), then swaps
    ReadU8(file, &detector->m_unk18[0]);
    ReadU8(file, &detector->m_unk18[1]);
    ReadU8(file, &detector->m_unk18[2]);
    ReadU8(file, &detector->m_unk18[3]);
    // Read into a local, +0x1c = 0, then +0x1c = the swapped word.
    uint32_t value = 0;
    ReadU32LE(file, &value);
    detector->m_unk1C = 0;
    detector->m_unk1C = value;
    IKFile_ReadRef(file, &detector->m_pUnk20);
    return 1;
}

// 0x005bd0b8 CKHkDetectorGroup_Load
int32_t CKHkDetectorGroup::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);  // through TocBridge_CKHook_Load
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_ui8NbDetectors[0]);
    ReadU8(file, &m_ui8NbDetectors[1]);
    ReadU8(file, &m_ui8NbDetectors[2]);
    ReadU8(file, &m_unk30);
    ReadU8(file, &m_unk31);
    ReadU8(file, &m_unk44);
    ReadF32LE(file, &m_unk48);
    m_tsUnk34.Load(file, 0);
    m_tsUnk3C.Load(file, 0);
    for (int32_t list = 0; list < 3; ++list) {
        m_apDetectors[list] = static_cast<Detector*>(
            Mem_AllocAligned16(static_cast<uint32_t>(m_ui8NbDetectors[list]) * static_cast<uint32_t>(sizeof(Detector))));
        for (int32_t i = 0; i < static_cast<int32_t>(m_ui8NbDetectors[list]); ++i) {
            LoadDetector(file, 0, &m_apDetectors[list][i]);
        }
    }
    return 1;
}

namespace {
// The three detector lists' run-time byte (+0x24) set to 1 (every detector armed).
void ArmDetectors(CKHkDetectorGroup* group) {
    for (int list = 0; list < 3; ++list) {
        for (int i = 0; i < group->m_ui8NbDetectors[list]; ++i) group->m_apDetectors[list][i].m_unk24 = 1;
    }
}
}  // namespace

// 0x005bcc48 CKHkDetectorGroup_Destroy (vt+0x10)
void CKHkDetectorGroup::Destroy() {
    for (Detector*& list : m_apDetectors) {
        if (list != nullptr) {
            Mem_FreeAligned16(list);
            list = nullptr;
        }
    }
}

// 0x005bcb48 CKHkDetectorGroup_SetDefaultState: only state 0: bit 1 of +0x4c = the byte m_unk30 shifted (a byte,
// not normalised), every detector armed.
void CKHkDetectorGroup::SetDefaultState(int32_t flag) {
    if (flag != 0) return;
    m_unk4C[0] = (m_unk4C[0] & 0xfffffffdu) | (static_cast<uint32_t>(m_unk30) << 1);
    ArmDetectors(this);
}

// 0x005bca38 CKHkDetectorGroup_RestoreCheckpointState_maybe: bit 1 of +0x4c = whether the flag byte (m_unk30 for
// state 0, else m_unk31) is set, every detector armed. Returns 1.
int32_t CKHkDetectorGroup::RestoreCheckpointState(uint32_t stateIdForLeft) {
    const uint8_t flag = stateIdForLeft == 0 ? m_unk30 : m_unk31;
    m_unk4C[0] = (m_unk4C[0] & 0xfffffffdu) | (flag != 0 ? 2u : 0u);
    ArmDetectors(this);
    return 1;
}

namespace {

// The detector's volume test, which the original inlines for each of the three positions TestDetector tests (the given
// point, the object's position, each hero's): the box (min <= v <= max for x, z, then y) narrowed by the shape byte
// +0x18 (signed): 1 a vertical cylinder and 2 a sphere, both centred in the box with half its x extent as radius
// (the half constant is the library TOC's 0.5f, -0x6288); 0 the box itself; any other value is never inside.
bool DetectorContains(const CKHkDetectorGroup::Detector* detector, float x, float y, float z) {
    const float* box = detector->m_aBox;
    const float minX = box[3];
    const float maxX = box[0];
    if (!(minX <= x) || !(x <= maxX)) return false;
    const float minZ = box[5];
    const float maxZ = box[2];
    if (!(minZ <= z) || !(z <= maxZ)) return false;
    const float minY = box[4];
    const float maxY = box[1];
    if (!(minY <= y) || !(y <= maxY)) return false;
    const int8_t shape = static_cast<int8_t>(detector->m_unk18[0]);
    if (shape == 1) {
        const float sumZ = minZ + maxZ;
        const float sumX = minX + maxX;
        const float extent = maxX - minX;
        float dz = ppc::fmsubs(sumZ, 0.5f, z);
        float dx = ppc::fmsubs(sumX, 0.5f, x);
        float radius = extent * 0.5f;
        dz = dz * dz;
        radius = radius * radius;
        dx = ppc::fmadds(dx, dx, dz);
        return dx <= radius;
    }
    if (shape == 2) {
        const float sumY = minY + maxY;
        const float sumX = minX + maxX;
        const float sumZ = minZ + maxZ;
        const float extent = maxX - minX;
        float dy = ppc::fmsubs(sumY, 0.5f, y);
        float dx = ppc::fmsubs(sumX, 0.5f, x);
        float dz = ppc::fmsubs(sumZ, 0.5f, z);
        float radius = extent * 0.5f;
        dy = dy * dy;
        radius = radius * radius;
        dx = ppc::fmadds(dx, dx, dy);
        dz = ppc::fmadds(dz, dz, dx);
        return dz <= radius;
    }
    return shape == 0;
}

// 0x002ca0f8 CKGrpS08Hero_GetFocusedHero (local copy; CKGrpS08Hero.cpp, not ported there yet): the focused dragon
// (+0x66, -1 none) among the group's heroes (+0x30).
IKSerializable* FocusedHeroOf(const IKGrpHero* group) {
    const int8_t index = static_cast<int8_t>(group->m_ui8FocusedDragon);
    if (index == -1) return nullptr;
    return group->m_apHeros[index];
}

// 0x00361968 CKHkS08Hero_GetPositionPtr (local copy; IKHkHero_2.cpp, not ported there yet): the hero's position
// (+0x54c) unless m_bitArray bit 1 is set and the hero's vt+0x164 (CKHkS08Hero_vf164 0x009bd700: +0xed4 bit 4) is
// clear; then the LTM position (+0x80) of its scene node's frame (m_pKGLObject +4), as stored (FrameLtm).
const float* HeroPositionOf(CKHkS08Hero* hero) {
    if ((hero->m_bitArray & 2u) == 0 || ((hero->m_ui32StatusFlagsED4 >> 4) & 1u) != 0) return &hero->m_unk54c;
    return &FrameLtm(static_cast<CSGMovable*>(hero->m_pKGLObject)->m_pRwFrame)->pos.x;
}

}  // namespace

// 0x005bd4a0 CKHkDetectorGroup_TestDetector_maybe
int32_t CKHkDetectorGroup::TestDetector(const Detector* detector, const float* point) const {
    if (detector->m_unk24 == 0) return 0;  // not armed
    if (point != nullptr) return DetectorContains(detector, point[0], point[1], point[2]) ? 1 : 0;
    if (detector->m_pUnk20 != nullptr) {
        // The object's +4 frame's LTM position (+0x80; the original reads the stored LTM).
        const RwMatrix* ltm = FrameLtm(static_cast<CSGMovable*>(detector->m_pUnk20)->m_pRwFrame);
        return DetectorContains(detector, ltm->pos.x, ltm->pos.y, ltm->pos.z) ? 1 : 0;
    }
    // The heroes: the hero group is the game manager's +0x08 (the engine through the library TOC, -0x6244).
    IKGrpHero* group = static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]);
    if (group == nullptr) return 0;
    IKSerializable* chosen = nullptr;  // the first player-controlled hero inside, or the focused one (never read after)
    uint8_t focusedInside = 0;         // the focused hero is a player-controlled hero inside
    uint8_t playerInside = 0;          // a player-controlled hero is inside
    int32_t inside = 0;                // the heroes of the mask inside
    for (int32_t i = 0; static_cast<int32_t>(group->GetHeroCount()) > i; ++i) {  // 0x002ca038: vt+0xf4 every pass
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(group->m_apHeros[static_cast<uint8_t>(i)]);  // 0x002ca080
        const float* position = HeroPositionOf(hero);
        if ((ppc::slw(1u, static_cast<uint32_t>(i)) & detector->m_unk1C) == 0) continue;
        if (!DetectorContains(detector, position[0], position[1], position[2])) continue;
        ++inside;
        // 0x00362af0 CKHkS08Hero_IsPlayerControlled: the hero is its own tracked leader (+0x24 == +0x25).
        if (hero->m_ui8Hero != hero->m_ui8TrackedLeader) continue;
        if (chosen == nullptr || hero == FocusedHeroOf(group)) chosen = hero;
        playerInside = 1;
        if (hero == FocusedHeroOf(group)) focusedInside = 1;
    }
    const int32_t threshold = detector->m_unk18[1];
    switch (static_cast<int8_t>(detector->m_unk18[3])) {
        case 0:
            if (threshold > inside) return 0;
            break;
        case 1:
            if (threshold != inside) return 0;
            break;
        case 2:
            if (!(threshold >= inside)) return 0;
            break;
        default:
            return 0;
    }
    switch (static_cast<int8_t>(detector->m_unk18[2])) {
        case 3: return focusedInside & 1;
        case 0: return playerInside & 1;
        case 1: return (playerInside ^ 1) & 0xff;
        default: return 1;
    }
}

// 0x005bda08 CKHkDetectorGroup_EvaluateConditions_maybe. The lists: 0 (+0x24, count +0x20) all, 1 (+0x28, count +0x21)
// any, 2 (+0x2c, count +0x22) none.
int32_t CKHkDetectorGroup::EvaluateConditions(const float* point, int32_t requireEnabled) const {
    if (requireEnabled != 0 && (m_unk4C[0] & 2u) == 0) return 0;
    if (m_ui8NbDetectors[2] != 0) {
        bool hit = false;
        for (int32_t i = 0; static_cast<int32_t>(m_ui8NbDetectors[2]) > i; ++i) {
            if (static_cast<uint8_t>(TestDetector(&m_apDetectors[2][i], point)) != 0) {
                hit = true;
                break;
            }
        }
        if (hit) return 0;
    }
    // The word at +0x20 tested with 0xffff0000: the counts of lists 0 and 1.
    if (m_ui8NbDetectors[0] == 0 && m_ui8NbDetectors[1] == 0) return 0;
    if (m_ui8NbDetectors[0] != 0) {
        bool all = true;
        for (int32_t i = 0; static_cast<int32_t>(m_ui8NbDetectors[0]) > i; ++i) {
            if (static_cast<uint8_t>(TestDetector(&m_apDetectors[0][i], point)) == 0) {
                all = false;
                break;
            }
        }
        if (!all) return 0;
    }
    if (m_ui8NbDetectors[1] == 0) return 1;
    bool any = false;
    for (int32_t i = 0; static_cast<int32_t>(m_ui8NbDetectors[1]) > i; ++i) {
        if (static_cast<uint8_t>(TestDetector(&m_apDetectors[1][i], point)) != 0) {
            any = true;
            break;
        }
    }
    return any ? 1 : 0;
}

// 0x005bdc38 CKHkDetectorGroup_IsTriggered_maybe (vt+0xc4)
uint8_t CKHkDetectorGroup::IsTriggered(const float* point) const {
    return static_cast<uint8_t>(EvaluateConditions(point, 1));
}

// 0x005bc840 CKHkDetectorGroup_MessageProc
int32_t CKHkDetectorGroup::MessageProc(uint16_t message, void* data) {
    if (message == 0x497) {
        m_unk4C[0] &= 0xfffffffcu;
        return 0;
    }
    if (message == 0x496) {
        m_unk4C[0] = (m_unk4C[0] & 0xfffffffdu) | 2u;
        return 0;
    }
    if (message != 0x498 && message != 0x499) return 1;
    const uint8_t armed = message == 0x498 ? 1 : 0;
    const uint64_t index = *static_cast<const uint32_t*>(data);
    const uint64_t first = m_ui8NbDetectors[0];
    const uint64_t second = first + m_ui8NbDetectors[1];
    if (index < second + m_ui8NbDetectors[2]) {
        if (index < first) {
            m_apDetectors[0][index].m_unk24 = armed;
        } else if (index < second) {
            m_apDetectors[1][index - first].m_unk24 = armed;
        } else {
            m_apDetectors[2][index - second].m_unk24 = armed;
        }
    }
    return 0;  // an index outside the lists answers 0 as well
}

// 0x005bc7b0 CKHkDetectorGroup_vf40 (GetInfo)
int32_t CKHkDetectorGroup::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor) return 1;
    if (info->m_ui32Id == 4) {
        // vt+0xc0 0x9ccff0 (+0x4c bit 0; IKHook declares no slot past vt+0xbc yet).
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) { return static_cast<CKHkDetectorGroup*>(o)->m_unk4C[0] & 1u; }, 0);
    }
    if (info->m_ui32Id == 5) {
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) { return (static_cast<CKHkDetectorGroup*>(o)->m_unk4C[0] >> 1) & 1u; }, 0);
    }
    return 1;
}

// 0x005bc628 CKHkDetectorGroup_PostLoad
int32_t CKHkDetectorGroup::PostLoad(int32_t type) {
    PostLoadLife(type);         // TocBridge_IKLife_PostLoad
    m_tsUnk34.PostLoad(type);   // TocBridge_TriggerEventList_PostLoad_maybe
    m_tsUnk3C.PostLoad(type);
    if (type == 0) m_unk4C[0] = 0;
    return 1;
}

// 0x005bccd0 CKHkDetectorGroup_vf50
void CKHkDetectorGroup::Start() { m_fHoldTime = 0.0f; }

// 0x005bcce0 CKHkDetectorGroup_vf54
void CKHkDetectorGroup::Restart() {
    m_unk4C[0] &= 0xfffffffeu;
    m_fHoldTime = 0.0f;
}

// 0x005bcd00 CKHkDetectorGroup_OnActivate
void CKHkDetectorGroup::VfA0() { m_unk4C[0] &= 0xfffffffeu; }

// 0x005bdc60 CKHkDetectorGroup_Update
void CKHkDetectorGroup::Update(IKTime* clock) {
    if ((m_unk4C[0] & 2u) == 0 || m_unk44 != 0) return;
    bool holds = false;
    bool excluded = false;
    for (uint32_t i = 0; i < m_ui8NbDetectors[2]; ++i) {  // any detector of list 2 holding excludes
        if (static_cast<uint8_t>(TestDetector(&m_apDetectors[2][i], nullptr)) != 0) {
            excluded = true;
            break;
        }
    }
    if (!excluded && (m_ui8NbDetectors[0] != 0 || m_ui8NbDetectors[1] != 0)) {
        bool all = true;
        for (uint32_t i = 0; i < m_ui8NbDetectors[0]; ++i) {
            if (static_cast<uint8_t>(TestDetector(&m_apDetectors[0][i], nullptr)) == 0) {
                all = false;
                break;
            }
        }
        if (all) {
            holds = true;
            if (m_ui8NbDetectors[1] != 0) {
                holds = false;
                for (uint32_t i = 0; i < m_ui8NbDetectors[1]; ++i) {
                    if (static_cast<uint8_t>(TestDetector(&m_apDetectors[1][i], nullptr)) != 0) {
                        holds = true;
                        break;
                    }
                }
            }
        }
    }
    const float delay = m_unk48;
    bool enter;
    if (!(delay > 0.0f)) {  // ble: not greater (a NaN delay is no delay)
        enter = holds;
    } else if (holds) {
        m_fHoldTime = m_fHoldTime + clock->m_afDeltaTime[0];  // the clock's +0x1c
        enter = !(delay > m_fHoldTime);  // bgt
    } else {
        m_fHoldTime = 0.0f;  // the float at library TOC -0x6240
        enter = false;
    }
    if (enter) {
        if ((m_unk4C[0] & 1u) != 0) return;  // vt+0xc0 0x9ccff0
        QueueTriggerSignals(&m_tsUnk34);     // TocBridge_QueueTriggerSignals
        m_unk4C[0] = (m_unk4C[0] & 0xfffffffeu) | 1u;
        return;
    }
    if ((m_unk4C[0] & 1u) == 0) return;
    QueueTriggerSignals(&m_tsUnk3C);
    m_unk4C[0] &= 0xfffffffeu;
}
