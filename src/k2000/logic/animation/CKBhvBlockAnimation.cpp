// CKBhvBlockAnimation.cpp - reconstructed original translation unit 0x5c17a0-0x5c2868 (GAME_TOC2, main_toc2), 26 functions, 26 live.
// Primary class: CKBhvBlockAnimation  key 0x9d0c  category Logic  size ?  vtable 0xb2fb40
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5c17a0  CKBhvBlockAnimation_Delete
//   [x] 0x5c17f0  CKBhvBlockAnimation_vf5C
//   [ ] 0x5c17f8  RegisterCKBhvBlockAnimationClass
//   [ ] 0x5c1870  _GLOBAL__I_5c1870
//   [x] 0x5c1880  CKBhvBlockAnimation_vf74
//   [x] 0x5c18d0  CKBhvBlockAnimation_vf70
//   [x] 0x5c1940  CKBhvBlockAnimation_UpdateCinematicStream_maybe
//   [x] 0x5c19a8  CKBhvBlockAnimation_vf68
//   [x] 0x5c1a60  CKBhvBlockAnimation_vf64
//   [x] 0x5c1d20  CKBhvBlockAnimation_vf58
//   [x] 0x5c1d48  CKBhvBlockAnimation_vf54
//   [x] 0x5c1d70  CKBhvBlockAnimation_ResetRuntime
//   [ ] 0x5c1d98  CKBhvBlockAnimation_Save
//   [x] 0x5c1dc0  CKBhvBlockAnimation_RecursiveRegistration  (KBase9C8C_vf24: returns 1; the default slot)
//   [x] 0x5c1de8  CKBhvBlockAnimation_Destroy  (the base's KStub_Nop_5c57c0: the default slot)
//   [x] 0x5c1e10  CKBhvBlockAnimation_DeletingDestructor  (the destructor; delete)
//   [x] 0x5c1e58  CKBhvBlockAnimation_Construct_2  (the constructor, CKBhvBlockAnimation.h)
//   [x] 0x5c1e90  CKBhvBlockAnimation_Construct
//   [x] 0x5c1ec8  CKBhvBlockAnimation_DeleteArray
//   [x] 0x5c1f70  CKBhvBlockAnimation_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x5c1fa0  CKBhvBlockAnimation_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x5c1fd0  CKBhvBlockAnimation_Update
//   [x] 0x5c2260  CKBhvBlockAnimation_PostLoad
//   [x] 0x5c22a8  CKBhvBlockAnimation_CreateArray
//   [x] 0x5c2360  CKBhvBlockAnimation_Create
//   [x] 0x5c23b8  CKBhvBlockAnimation_Load
//
//   [ ] 0x9cd330  CKBhvBlockAnimation_IsKindOfClass  [inline]
//   [ ] 0x9cd368  CKBhvBlockAnimation_GetClassType  [inline]
//   [ ] 0x9cd370  CKBhvBlockAnimation_GetClassID  [inline]
//   [x] 0x9cd378  CKBhvBlockAnimation_vf7C  [inline]
#include "k2000/logic/animation/CKBhvBlockAnimation.h"

#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/components/CKCinematicStreamCpnt.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKMarkedFX.h"
#include "k2000/logic/KBase9CCC.h"
#include "k2000/logic/ai/CKMarkerBeacon.h"
#include "k2000/logic/sound/CKMarkedSoundDico.h"
#include "k2000/math/Quat.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"
#include "k2000/ui/CKHkScriptedNPC.h"

// 0x005c23b8 CKBhvBlockAnimation_Load
int32_t CKBhvBlockAnimation::Load(IKFile* file, int32_t type) {
    KBase9C8C::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk10);
        ReadU8(file, &m_unk19);
        IKFile_ReadRef(file, &m_unk0c);
        ReadU8(file, &m_unk1a);
        ReadU8(file, &m_unk24);
        ReadF32LE(file, &m_unk1c);
        IKFile_ReadRef(file, &m_unk28);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk30), 3);  // one 0xc read, swapped
        ReadU8(file, &m_unk2c);
        ReadU8(file, &m_unk3c);
        ReadF32LE(file, &m_unk40);
        IKFile_ReadRef(file, &m_unk14);
        ReadU8(file, &m_unk18);
        IKFile_ReadRef(file, &m_unk08);
        IKFile_ReadRef(file, &m_unk04);
    }
    return 1;
}

namespace {
KBase9CCC* User(IKSerializable* user) { return static_cast<KBase9CCC*>(user); }
CKCinematicStreamCpnt* Stream(IKSerializable* stream) { return static_cast<CKCinematicStreamCpnt*>(stream); }
}  // namespace

// 0x005c2260 CKBhvBlockAnimation_PostLoad: the sound marks' position callback set to the NPC's anchor (the pointer to
// member 0x00bf45d8_00000000: CKHkScriptedNPC_GetAnchorPosition_maybe 0x5c8c88, no adjustment).
int32_t CKBhvBlockAnimation::PostLoad(int32_t /*type*/) {
    static_cast<CKMarkedSoundDico*>(m_unk08)->SetPositionCallback(&CKHkScriptedNPC::GetAnchorPosition, 0);  // 0x005cdf68
    return 1;
}

// 0x005c1d70 CKBhvBlockAnimation_ResetRuntime: the marked effects' channels forgotten (0x005cf1c0).
void CKBhvBlockAnimation::ResetRuntime() { static_cast<CKMarkedFX*>(m_unk04)->ResetChannels(); }

// 0x005c1d48 CKBhvBlockAnimation_vf54: the marked effects' channel effects stopped (0x005cfb70).
void CKBhvBlockAnimation::Vf54() { static_cast<CKMarkedFX*>(m_unk04)->StopAllChannelNodes2(); }

// 0x005c1d20 CKBhvBlockAnimation_vf58: the same, and the animation forgotten (0x005cfcb0).
void CKBhvBlockAnimation::Vf58() { static_cast<CKMarkedFX*>(m_unk04)->StopAllChannelNodesAndReset(); }

// 0x005c1a60 CKBhvBlockAnimation_vf64: the block entered. The user's (+0x0c) node is placed: at the marker beacon
// (+0x28, with +0x2c: its quaternion as the rotation, CSGMovable_SetLocalMatrix_maybe) or at the position (+0x30, with
// +0x3c: the frame's modelling position, the identity flag cleared, the frame marked dirty). Without a stream (+0x18)
// the user's stream is cleared (vt+0x5c) and the dictionary's first word (+0x10) plays on the node of `user` (vt+0x54):
// cut from 0 (CAnimatedNode_PlayAnim_maybe) when the blend time +0x40 is not above 0 (fcmpu + cror: a NaN blends),
// else blended (CAnimatedNode_CrossfadeToAnim_maybe, mode 1); the timer +0x20 restarts. KStub_Nop_5cebf0 (the marked
// effects and the user's vt+0x50) does nothing.
void CKBhvBlockAnimation::Enter(IKSerializable* user) {
    if (m_unk2c != 0) {
        const CKMarkerBeacon* marker = static_cast<const CKMarkerBeacon*>(m_unk28);
        alignas(16) CMatrix34 matrix;
        float q[4];
        std::memcpy(q, marker->m_qOrientation, sizeof q);
        Quat_ToMatrixNormalizing(q, &matrix);  // 0x00241d78 (on +0x10)
        const CVector3 p = marker->m_v3Position;  // +0x04
        matrix.m_pos.z = p.z;
        matrix.m_pos.x = p.x;
        matrix.m_pos.y = p.y;
        matrix.m_ui32Flags &= 0xfffdffffu;
        CSGMovable* node = static_cast<CSGMovable*>(User(m_unk0c)->GetMovable());  // vt+0x58
        node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));          // 0x000d0be8
    } else if (m_unk3c != 0) {
        CSGMovable* node = static_cast<CSGMovable*>(User(m_unk0c)->GetMovable());  // vt+0x58
        RwFrame* frame = node->m_pRwFrame;
        frame->modelling.pos.z = m_unk30.z;
        frame->modelling.pos.x = m_unk30.x;
        frame->modelling.pos.y = m_unk30.y;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(frame);  // 0x00010698
    }
    if (m_unk18 != 0) return;
    const uint32_t word = static_cast<uint32_t>(static_cast<CAnimationDictionary*>(m_unk10)->m_apAnimations[0]);
    User(m_unk0c)->SetStream(nullptr);  // vt+0x5c
    if (CAnimationManager_GetAnimation(word) == nullptr) return;  // resolved entry (dotd keeps the words)
    CAnimatedNode* node = static_cast<CAnimatedNode*>(User(user)->GetAnimatedNode());  // vt+0x54
    if (m_unk40 <= 0.0f) {  // TOC1 -0x60f0 0.0
        node->PlayAnim(0.0, word, 0);  // 0x000c98b8
    } else {
        node->CrossfadeToAnim(m_unk40, 0.0, word, 1);  // 0x000c8eb0
    }
    m_unk20 = 0.0f;
}

// 0x005c19a8 CKBhvBlockAnimation_vf68: the block left. A stream is finished and stopped and the user's stream cleared
// (vt+0x5c). KStub_Nop_5cebf8 (the marked effects and the user's vt+0x50) does nothing.
void CKBhvBlockAnimation::Leave(IKSerializable* /*user*/) {
    if (m_unk18 == 0) return;
    Stream(m_unk14)->Finish();  // 0x00082a88
    Stream(m_unk14)->Stop();    // 0x00082008
    User(m_unk0c)->SetStream(nullptr);
}

// 0x005c1fd0 CKBhvBlockAnimation_Update: with a time limit (+0x1c above 0; ble: a NaN is none) the timer +0x20 takes the
// frame's dt. The animation (no stream; nothing at all without one in the dictionary) ends past the limit, or at its
// end unless +0x19; else it advances by dt. The stream ends when UpdateStream answers 0 or past the limit; else it is
// updated. An end stops the stream (vt+0x74) and tells the user (vt+0x64). Then the sound marks (their source and
// stream set, vt+0x50) and the marked effects (0x005d0640).
void CKBhvBlockAnimation::Update(IKTime* clock) {
    const float limit = m_unk1c;
    const float dt = clock->m_afDeltaTime[0];  // +0x1c
    if (limit > 0.0f) m_unk20 = m_unk20 + dt;
    bool ended = false;
    if (m_unk18 == 0) {
        if (CAnimationManager_GetAnimation(static_cast<uint32_t>(static_cast<CAnimationDictionary*>(m_unk10)->m_apAnimations[0])) == nullptr) return;  // resolved entry (dotd keeps the words)
        if (limit > 0.0f && m_unk20 > limit) {
            ended = true;
        } else {
            CAnimatedNode* node = static_cast<CAnimatedNode*>(User(m_unk0c)->GetAnimatedNode());  // vt+0x54
            if (node->IsAnimEndReached(dt) && m_unk19 == 0) {  // 0x000ca368
                ended = true;
            } else {
                static_cast<CAnimatedNode*>(User(m_unk0c)->GetAnimatedNode())->AddAnimTime(dt);  // 0x000c9638
            }
        }
    } else {
        if (Stream(m_unk14)->UpdateStream(clock) == 0) {  // 0x00083f18
            ended = true;
        } else if (m_unk1c > 0.0f && m_unk20 > m_unk1c) {
            ended = true;
        } else {
            Stream(m_unk14)->Update(clock);  // 0x00083820
        }
    }
    if (ended) {
        Unprepare();                         // vt+0x74
        User(m_unk0c)->OnBlockDone(this);    // vt+0x64
    }
    CKMarkedSoundDico* sounds = static_cast<CKMarkedSoundDico*>(m_unk08);
    sounds->SetSourceMode(m_unk18);  // 0x005cdf60
    sounds->SetTimeline(m_unk14);    // 0x005cdf58
    sounds->UpdateFromAnimMarks(clock);  // vt+0x50
    static_cast<CKMarkedFX*>(m_unk04)->UpdateFromAnimMarks(clock);  // 0x005d0640
}

// 0x005c18d0 CKBhvBlockAnimation_vf70: prepared as the next block: a stream starts (without its media) and becomes
// the user's (vt+0x5c).
void CKBhvBlockAnimation::Prepare() {
    if (m_unk18 == 0) return;
    Stream(m_unk14)->StartStream(0);  // 0x00084ca8
    User(m_unk0c)->SetStream(m_unk14);
}

// 0x005c1880 CKBhvBlockAnimation_vf74: a stream finished and stopped.
void CKBhvBlockAnimation::Unprepare() {
    if (m_unk18 == 0) return;
    Stream(m_unk14)->Finish();
    Stream(m_unk14)->Stop();
}

// 0x005c1940 CKBhvBlockAnimation_UpdateCinematicStream_maybe: while the current block runs, the next block's stream
// reads on (with a clock, unless its +0xfc bit 10).
void CKBhvBlockAnimation::PreUpdate(IKTime* clock) {
    if (m_unk18 == 0 || clock == nullptr) return;
    if ((Stream(m_unk14)->m_unkfc & 0x400u) != 0) return;
    Stream(m_unk14)->UpdateStream(clock);
}
