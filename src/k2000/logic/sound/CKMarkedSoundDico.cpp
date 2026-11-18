// CKMarkedSoundDico.cpp - reconstructed original translation unit 0x5cdee0-0x5ceb68 (GAME_TOC2, main_toc2), 22 functions, 19 live.
// Primary class: CKMarkedSoundDico  key 0xab0c  category Logic  size ?  vtable 0xb30180
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5cdee0  CKMarkedSoundDico_Delete
//   [ ] 0x5cdf30  CKMarkedSoundDico_Construct  [dead]
//   [ ] 0x5cdf50  CKMarkedSoundDico_SetAnimatedNode_maybe  [dead]
//   [x] 0x5cdf58  CKMarkedSoundDico_SetTimeline_maybe
//   [x] 0x5cdf60  CKMarkedSoundDico_SetSourceMode_maybe
//   [x] 0x5cdf68  CKMarkedSoundDico_SetPositionCallback_maybe
//   [ ] 0x5cdf80  CKMarkedSoundDico_Construct_2  [dead]
//   [x] 0x5cdfa0  CKMarkedSoundDico_PlaySoundsForMark_maybe
//   [x] 0x5ce118  CKMarkedSoundDico_DeleteArray
//   [ ] 0x5ce1c0  RegisterCKMarkedSoundDicoClass
//   [ ] 0x5ce248  _GLOBAL__D_5ce248
//   [ ] 0x5ce258  _GLOBAL__I_5ce258
//   [x] 0x5ce268  CKMarkedSoundDico_UpdateFromAnimMarks_maybe
//   [x] 0x5ce4f0  CKMarkedSoundDico_CreateArray
//   [x] 0x5ce5a8  CKMarkedSoundDico_Create
//   [ ] 0x5ce5f8  CKMarkedSoundDico_Save
//   [x] 0x5ce600  CKMarkedSoundDico_RecursiveRegistration  (IKSerializable's empty default)
//   [x] 0x5ce608  CKMarkedSoundDico_Destroy
//   [x] 0x5ce678  CKMarkedSoundDico_Load
//   [x] 0x5cea18  CKMarkedSoundDico_DeletingDestructor  (the deleting form of 0x5cea98)
//   [x] 0x5cea98  CKMarkedSoundDico_Destructor
//   [x] 0x5ceb00  CKMarkedSoundDico_Destructor_2  (the same as 0x5cea98 CKMarkedSoundDico_Destructor)
//
//   [ ] 0x9cd680  CKMarkedSoundDico_GetClassType  [inline]
//   [ ] 0x9cd688  CKMarkedSoundDico_GetClassID  [inline]
//   [ ] 0x9cd690  CKMarkedSoundDico_IsKindOfClass  [inline]
#include "k2000/logic/sound/CKMarkedSoundDico.h"

#include "k2000/components/CKCinematicStreamCpnt.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/animation/CKAnimationMarkContainer.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/system/IKTime.h"
#include "Spyro2008/logic/CKS08GameManager.h"

// 0x005ce5a8 CKMarkedSoundDico_Create (the constructor inlined)
CKMarkedSoundDico::CKMarkedSoundDico() {
    m_apIds = nullptr;
    m_idsCapacity = 1;
    m_idsCount = 0;
}

// 0x005cea98 CKMarkedSoundDico_Destructor
CKMarkedSoundDico::~CKMarkedSoundDico() {
    if (m_apIds != nullptr) Mem_FreeAligned16(m_apIds);
    m_idsCount = 0;
    m_apIds = nullptr;
}

// 0x005ce608 CKMarkedSoundDico_Destroy (a do-while behind the count test, the count read again after each delete)
void CKMarkedSoundDico::Destroy() {
    if (m_idsCount == 0) return;
    uint32_t i = 0;
    do {
        ::operator delete(m_apIds[i]);  // OperatorDelete
        ++i;
    } while (i < m_idsCount);
}

// 0x005ce678 CKMarkedSoundDico_Load
int32_t CKMarkedSoundDico::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unk08);
    IKFile_ReadRef(file, &m_unk1c);
    IKFile_ReadRef(file, &m_unk20);
    ReadU8(file, &m_unk18);
    IKFile_ReadRef(file, &m_unk04);
    ReadU32LE(file, &m_idCount);
    // The vector is re-created (capacity 1); its count is not reset (BUG(original) if loaded twice).
    m_idsCapacity = 1;
    m_apIds = static_cast<uint32_t**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(uint32_t*))));
    for (uint32_t i = 0; i < m_idCount; ++i) {
        uint32_t* id = static_cast<uint32_t*>(::operator new(4));  // OperatorNew(4)
        ReadU32LE(file, id);
        if (m_idsCapacity == m_idsCount) {  // push_back: grow by one
            uint32_t grown = m_idsCount + 1;
            m_apIds = static_cast<uint32_t**>(Mem_ReallocAligned16(m_apIds, grown * static_cast<uint32_t>(sizeof(uint32_t*))));
            m_idsCapacity = grown;
        }
        m_apIds[m_idsCount] = id;
        ++m_idsCount;
    }
    return 1;
}

// 0x005cdfa0 CKMarkedSoundDico_PlaySoundsForMark_maybe: the ids in order (the count read again after each one). An id
// equal to `value` takes the dictionary's (+0x08) sound value - 1; when it exists the callback (+0x24 on the owner
// +0x04 plus +0x28) gives its position, then it plays from 0 (TOC1 -0x5e84).
void CKMarkedSoundDico::PlaySoundsForMark(uint32_t value) {
    for (uint32_t i = 0; i < m_idsCount; ++i) {
        if (*m_apIds[i] != value) continue;
        CKSound* sound = static_cast<CKSoundDictionaryID*>(m_unk08)->GetSound(value - 1);  // 0x00112bc0
        if (sound == nullptr) continue;
        CVector3 position;
        // The pointer to member's call (a function descriptor at +0x24 when its bit 0 is clear, else the owner's vtable
        // entry at +0x24 - 1): DotD's is always the function SetPositionCallback stored.
        m_pfnPosition(&position, m_unk04, value - 1);
        sound->SetPosition(&position);  // 0x00110fa0
        sound->Play(0.0f);              // 0x00111230
    }
}

// vt+0x50 0x005ce268 CKMarkedSoundDico_UpdateFromAnimMarks_maybe. From the node (+0x18 clear): its current animation's
// sound mark crossed between the evaluated time and the time now brought into [0, duration) (TOC1 -0x5e84 0.0; bge /
// ble with cror: a NaN stays). From the stream (+0x18 set): channel 0's mark list (CKAnimationMarkContainer), the
// sound mark searched from the last, crossed between the stream time (+0x30, a double rounded to a float) and that
// time plus the frame's dt (+0x1c). A crossed value plays its sounds.
void CKMarkedSoundDico::UpdateFromAnimMarks(IKTime* clock) {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);  // TOC1 -0x5e5c -> +0x8c
    uint32_t value;
    if (m_unk18 == 0) {
        CAnimatedNode* node = static_cast<CAnimatedNode*>(m_unk1c);
        if (node == nullptr) return;
        RtAnimAnimation* animation = node->GetCurrentAnim();  // 0x000c96d8
        if (animation == nullptr) return;
        AnimMark* mark = Anim_GetMarkById(animation, manager->GetSoundMarkChannel());  // vt+0x258, 0x00078830
        if (mark == nullptr) return;
        float t = node->GetAnimTimeNow();                      // 0x000c95f0
        const float duration = node->GetCurrentAnimDuration();  // 0x000c9768
        while (t < 0.0f) t = t + duration;
        const float end = duration + 0.0f;
        while (end <= t) t = t - duration;
        value = AnimMark_CrossedValueR3(mark, node->GetCurrentAnimTime(), t);  // 0x000c95a8, vt+0x1c
    } else {
        CKCinematicStreamCpnt* stream = static_cast<CKCinematicStreamCpnt*>(m_unk20);
        if (stream == nullptr) return;
        const CKAnimationMarkContainer* list =
            static_cast<const CKAnimationMarkContainer*>(stream->GetChannelMarkList(0));  // 0x00081130
        if (list == nullptr) return;
        const uint32_t channel = manager->GetSoundMarkChannel();  // vt+0x258
        AnimMark* mark = nullptr;
        for (uint32_t i = list->m_count; i != 0; --i) {
            if (list->m_ppMarks[i - 1]->m_channel == channel) {
                mark = list->m_ppMarks[i - 1];
                break;
            }
        }
        if (mark == nullptr) return;
        const float t = static_cast<float>(stream->m_d30);
        value = AnimMark_CrossedValueR3(mark, t, t + clock->m_afDeltaTime[0]);  // vt+0x1c
    }
    if (value == 0) return;
    PlaySoundsForMark(value);
}
