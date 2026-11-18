// CKMarkedTrigger.cpp - reconstructed original translation unit 0x5d1748-0x5d2510 (GAME_TOC2, main_toc2), 26 functions, 19 live.
// Primary class: CKMarkedTrigger  key 0xb08c  category Logic  size ?  vtable 0xb30238
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5d1748  CKMarkedTrigger_Delete
//   [x] 0x5d1798  CKMarkedTrigger_Construct  [dead]
//   [ ] 0x5d17b8  KStub_Nop_5d17b8  [dead]
//   [ ] 0x5d17c0  KStub_Nop_5d17c0  [dead]
//   [ ] 0x5d17c8  KStub_Nop_5d17c8  [dead]
//   [ ] 0x5d17d0  KStub_Nop_5d17d0  [dead]
//   [ ] 0x5d17d8  KStub_Nop_5d17d8  [dead]
//   [ ] 0x5d17e0  CKMarkedTrigger_Construct_2  [dead]
//   [ ] 0x5d1800  RegisterCKMarkedTriggerClass
//   [ ] 0x5d1878  _GLOBAL__I_5d1878
//   [x] 0x5d1888  CKMarkedTrigger_FireMatchingEntries_maybe
//   [x] 0x5d1948  CKMarkedTrigger_DeleteArray
//   [x] 0x5d19f0  CKMarkedTrigger_CreateArray
//   [x] 0x5d1aa8  CKMarkedTrigger_Create
//   [x] 0x5d1af8  CKMarkedTrigger_GetInfo  (1: the inherited default)
//   [ ] 0x5d1b00  CKMarkedTrigger_Save
//   [x] 0x5d1b08  CKMarkedTrigger_RecursiveRegistration  (1: the inherited default)
//   [x] 0x5d1b10  CKMarkedTrigger_PostLoad  (empty / no effect: inherited)
//   [x] 0x5d1b90  CKMarkedTrigger_Destroy
//   [x] 0x5d1c10  CKMarkedTrigger_Load
//   [x] 0x5d1f48  CKMarkedTrigger_FireMark_maybe
//   [x] 0x5d2068  CKMarkedTrigger_UpdateFromAnimMarks_maybe
//   [x] 0x5d23b8  CKMarkedTrigger_DeletingDestructor  (the same as 0x5d2438 CKMarkedTrigger_Destructor)
//   [x] 0x5d2438  CKMarkedTrigger_Destructor
//   [x] 0x5d24a0  CKMarkedTrigger_Destructor_2  (the same as 0x5d2438 CKMarkedTrigger_Destructor)
//   [x] 0x5d2508  KStub_Return0_5d2508  (returns 0; no live reference)
//
//   [ ] 0x9cd6f0  CKMarkedTrigger_GetClassType  [inline]
//   [ ] 0x9cd6f8  CKMarkedTrigger_GetClassID  [inline]
//   [ ] 0x9cd700  CKMarkedTrigger_IsKindOfClass  [inline]
#include "k2000/logic/CKMarkedTrigger.h"

#include "Renderware/rtanim/RtAnim.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKMarkedFX.h"
#include "k2000/logic/animation/CKAnimationMarkContainer.h"
#include "k2000/memory/Mem.h"
#include "k2000/scenegraph/CAnimatedNode.h"

namespace {
const float kZero = 0.0f;  // TOC2 -0x5d7c
}  // namespace

// 0x005d2068 CKMarkedTrigger_UpdateFromAnimMarks_maybe. The node's current animation (+0x58; without one the evaluated
// +0x5c, without that nothing); the time now (+0x50) wrapped into it (bge / cror lt|eq: a NaN gets one add and stays).
// At time 0 with an evaluated animation other than the current one (a change this frame) the marks run from the
// evaluated time wrapped into the evaluated animation to that animation's end; else from the evaluated time (+0x54,
// wrapped into the current one) to the time now; a window that runs backwards starts at 0, an empty one does nothing.
void CKMarkedTrigger::UpdateFromAnimMarks(IKTime* /*clock*/) {
    const CAnimatedNode* node = static_cast<const CAnimatedNode*>(m_unk10);
    RtAnimAnimation* evaluated = node->ActiveController()->m_unk5c;  // 0x000c9720 GetActiveAnim_maybe
    RtAnimAnimation* current = node->GetCurrentAnim();                // 0x000c96d8
    RtAnimAnimation* animation = node->GetCurrentAnim();
    if (animation == nullptr) {
        animation = node->ActiveController()->m_unk5c;
        if (animation == nullptr) return;
    }
    float to = node->GetAnimTimeNow();  // 0x000c95f0
    float duration = animation->duration;  // +0x10
    if (!(to >= kZero)) {
        do {
            to = to + duration;
        } while (to < kZero);
    }
    float end = duration + kZero;
    if (end < to || end == to) {
        do {
            to = to - duration;
        } while (end < to || end == to);
    }
    float from;
    if (to == kZero && evaluated != nullptr && evaluated != current) {
        from = node->GetCurrentAnimTime();  // 0x000c95a8
        to = evaluated->duration;
        if (!(from >= kZero)) {
            do {
                from = from + to;
            } while (from < kZero);
        }
        end = to + kZero;
        if (from > end || from == end) {
            do {
                from = from - to;
            } while (end < from || end == from);
        }
        animation = evaluated;
    } else {
        from = node->GetCurrentAnimTime();
        duration = animation->duration;
        if (!(from >= kZero)) {
            do {
                from = from + duration;
            } while (from < kZero);
        }
        end = duration + kZero;
        if (from > end || from == end) {
            do {
                from = from - duration;
            } while (end < from || end == from);
        }
    }
    if (to < from) from = kZero;
    if (to == from) return;
    for (uint32_t id = 0; id < 37; ++id) {
        if (!IsIntegerAnimMark(id)) continue;  // strcmp 0x0095f1a0 with "MarkI" (the names at 0x00b012c0)
        AnimMark* mark = Anim_GetMarkById(animation, id);  // 0x00078830
        if (mark == nullptr) continue;
        const uint32_t value = AnimMark_CrossedValueR3(mark, from, to);  // vt+0x1c
        if (value == 0) continue;
        for (uint32_t i = 0; i < m_vMarks.m_ui32NbUsedElt; ++i) {
            Mark* entry = m_vMarks.m_pBlock[i];
            if (entry->m_unk0c != value || entry->m_unk08 != id) continue;
            QueueTriggerSignals(&entry->m_tsStarter);  // TocBridge 0x009901b0 -> 0x00236338
        }
    }
}

// 0x005d1798 CKMarkedTrigger_Construct (also inlined in 0x005d1aa8 CKMarkedTrigger_Create).
CKMarkedTrigger::CKMarkedTrigger() {
    m_vMarks.m_pBlock = nullptr;
    m_vMarks.m_ui32NbUsedElt = 0;
    m_vMarks.m_ui32NbElt = 1;
}

// 0x005d1c10 CKMarkedTrigger_Load: a one-slot block, then each mark pushed back (grow by one).
int32_t CKMarkedTrigger::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    m_vMarks.m_ui32NbElt = 1;
    m_vMarks.m_pBlock = static_cast<Mark**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Mark*))));
    for (uint32_t i = 0; i < count; ++i) {
        Mark* mark = static_cast<Mark*>(::operator new(sizeof(Mark)));  // OperatorNew(0x10)
        ReadU32LE(file, &mark->m_unk08);
        ReadU32LE(file, &mark->m_unk0c);
        mark->m_tsStarter.Load(file, K_LEVEL_PLATEFORMS);
        const uint32_t used = m_vMarks.m_ui32NbUsedElt;
        if (m_vMarks.m_ui32NbElt == used) {
            uint32_t capacity = used + 1;
            if (capacity == 0) capacity = 1;
            m_vMarks.m_pBlock = static_cast<Mark**>(
                Mem_ReallocAligned16(m_vMarks.m_pBlock, capacity * static_cast<uint32_t>(sizeof(Mark*))));
            m_vMarks.m_ui32NbElt = capacity;
        }
        m_vMarks.m_pBlock[m_vMarks.m_ui32NbUsedElt] = mark;
        m_vMarks.m_ui32NbUsedElt = m_vMarks.m_ui32NbUsedElt + 1;
    }
    IKFile_ReadRef(file, &m_unk10);
    IKFile_ReadRef(file, &m_unk14);
    ReadU32LE(file, &m_unk18);
    return 1;
}

// 0x005d2438 CKMarkedTrigger_Destructor
CKMarkedTrigger::~CKMarkedTrigger() {
    if (m_vMarks.m_pBlock != nullptr) Mem_FreeAligned16(m_vMarks.m_pBlock);
    m_vMarks.m_ui32NbUsedElt = 0;
    m_vMarks.m_pBlock = nullptr;
}

// 0x005d1b90 CKMarkedTrigger_Destroy (OperatorDelete)
void CKMarkedTrigger::Destroy() {
    for (uint32_t i = 0; i < m_vMarks.m_ui32NbUsedElt; ++i) {
        if (m_vMarks.m_pBlock[i] != nullptr) ::operator delete(m_vMarks.m_pBlock[i]);
    }
    m_vMarks.m_ui32NbUsedElt = 0;
}

// 0x005d1888 CKMarkedTrigger_FireMatchingEntries_maybe (QueueTriggerSignals through its TOC bridge; the count read again
// after each queue)
void CKMarkedTrigger::FireMatchingEntries(uint32_t id, uint32_t value) {
    for (uint32_t i = 0; i < m_vMarks.m_ui32NbUsedElt; ++i) {
        Mark* entry = m_vMarks.m_pBlock[i];
        if (entry->m_unk0c != value || entry->m_unk08 != id) continue;
        QueueTriggerSignals(&entry->m_tsStarter);
    }
}

// 0x005d1f48 CKMarkedTrigger_FireMark_maybe (Anim_GetMarkById 0x00078830 through its TOC bridge)
void CKMarkedTrigger::FireMark(uint32_t id, RtAnimAnimation* animation, const float* t0, const float* t1) {
    AnimMark* mark = Anim_GetMarkById(animation, id);
    if (animation == nullptr || mark == nullptr) return;
    const uint32_t value = AnimMark_CrossedValueR3(mark, *t0, *t1);  // vt+0x1c
    if (value == 0) return;
    FireMatchingEntries(id, value);
}
