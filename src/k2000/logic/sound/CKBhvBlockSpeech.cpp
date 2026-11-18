// CKBhvBlockSpeech.cpp - reconstructed original translation unit 0x5c4e50-0x5c5788 (GAME_TOC2, main_toc2), 19 functions, 19 live.
// Primary class: CKBhvBlockSpeech  key 0xa54c  category Logic  size ?  vtable 0xb2fcf0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5c4e50  CKBhvBlockSpeech_Delete
//   [ ] 0x5c4ea0  RegisterCKBhvBlockSpeechClass
//   [ ] 0x5c4f18  _GLOBAL__I_5c4f18
//   [x] 0x5c4f28  CKBhvBlockSpeech_Update
//   [x] 0x5c4fe8  CKBhvBlockSpeech_Stop_maybe
//   [x] 0x5c5040  CKBhvBlockSpeech_IsFinished_maybe
//   [x] 0x5c50c8  CKBhvBlockSpeech_StartSpeech_maybe
//   [ ] 0x5c51d8  CKBhvBlockSpeech_Save
//   [x] 0x5c5200  CKBhvBlockSpeech_RecursiveRegistration  (only calls KBase9C8C's 0x5c57b8: inherited)
//   [x] 0x5c5228  CKBhvBlockSpeech_Destroy  (only calls KStub_Nop_5c57c0: inherited)
//   [x] 0x5c5250  CKBhvBlockSpeech_DeletingDestructor  (the deleting form of 0x5c5298)
//   [x] 0x5c5298  CKBhvBlockSpeech_Destructor  (the vtable, then KBase9C8C's 0x5c5820: ~CKBhvBlockSpeech)
//   [x] 0x5c52c8  CKBhvBlockSpeech_BaseDestructor  (the same as 0x5c5298 CKBhvBlockSpeech_Destructor)
//   [x] 0x5c52f8  CKBhvBlockSpeech_Construct_2  (the same as 0x5c5330 CKBhvBlockSpeech_Construct)
//   [x] 0x5c5330  CKBhvBlockSpeech_Construct
//   [x] 0x5c5368  CKBhvBlockSpeech_DeleteArray
//   [x] 0x5c5410  CKBhvBlockSpeech_Create
//   [x] 0x5c5468  CKBhvBlockSpeech_CreateArray
//   [x] 0x5c5520  CKBhvBlockSpeech_Load
//
//   [ ] 0x9cd450  CKBhvBlockSpeech_IsKindOfClass  [inline]
//   [ ] 0x9cd488  CKBhvBlockSpeech_GetClassType  [inline]
//   [ ] 0x9cd490  CKBhvBlockSpeech_GetClassID  [inline]
#include "k2000/logic/sound/CKBhvBlockSpeech.h"

#include "k2000/components/CKSekensLauncherCpnt.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/KBase9CCC.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/system/IKTime.h"

namespace {
KBase9CCC* User(IKSerializable* user) { return static_cast<KBase9CCC*>(user); }
CKSekensLauncherCpnt* Launcher(IKSerializable* launcher) { return static_cast<CKSekensLauncherCpnt*>(launcher); }
}  // namespace

// 0x005c4f28 CKBhvBlockSpeech_Update
void CKBhvBlockSpeech::Update(IKTime* clock) {
    static_cast<CAnimatedNode*>(User(m_unk04)->GetAnimatedNode())->AddAnimTime(clock->m_afDeltaTime[0]);  // vt+0x54, 0x000c9638
    if (Launcher(m_unk0c)->IsEntryDone(0) != 0) User(m_unk04)->OnBlockDone(this);  // 0x001f79b0, vt+0x64
}

// 0x005c4fe8 CKBhvBlockSpeech_Stop_maybe
void CKBhvBlockSpeech::Leave(IKSerializable* user) {
    if (m_unk04 != user || m_unk10 == 0) return;
    Launcher(m_unk0c)->StopSekens(0, 0);  // 0x001f7a18
}

// 0x005c5040 CKBhvBlockSpeech_IsFinished_maybe
uint8_t CKBhvBlockSpeech::CanLeave(IKSerializable* /*user*/) {
    if (Launcher(m_unk0c)->IsEntryDone(0) != 0) return 1;  // 0x001f79b0
    if (Launcher(m_unk0c)->IsSekensLineFinished(0) == 0) return 0;  // 0x001f78d8
    return m_unk11;
}

// 0x005c50c8 CKBhvBlockSpeech_StartSpeech_maybe. The original tests the word against 0; dotd keeps the dictionary's words
// and asks the animation manager (TOC2 -0x600c 0.0; fcmpu with cror lt|eq: a NaN blend time blends).
void CKBhvBlockSpeech::Enter(IKSerializable* user) {
    const uint32_t word = static_cast<uint32_t>(static_cast<CAnimationDictionary*>(m_unk08)->m_apAnimations[0]);
    if (CAnimationManager_GetAnimation(word) != nullptr) {
        CAnimatedNode* node = static_cast<CAnimatedNode*>(User(user)->GetAnimatedNode());  // vt+0x54
        if (m_unk14 <= 0.0f) {
            node->PlayAnim(0.0, word, 0);  // 0x000c98b8
        } else {
            node->CrossfadeToAnim(m_unk14, 0.0, word, 1);  // 0x000c8eb0
        }
    }
    if (Launcher(m_unk0c)->HasSekens(0) != 0) Launcher(m_unk0c)->PlaySekens(0);  // 0x001f78a8, 0x001f7730
}

// 0x005c5520 CKBhvBlockSpeech_Load
int32_t CKBhvBlockSpeech::Load(IKFile* file, int32_t type) {
    KBase9C8C::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk04);
        IKFile_ReadRef(file, &m_unk08);
        IKFile_ReadRef(file, &m_unk0c);
        ReadU8(file, &m_unk10);
        ReadU8(file, &m_unk11);
        ReadF32LE(file, &m_unk14);
    }
    return 1;
}
