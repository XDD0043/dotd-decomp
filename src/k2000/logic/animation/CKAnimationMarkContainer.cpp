// CKAnimationMarkContainer.cpp - reconstructed original translation unit 0x7d350-0x7e318 (GAME_TOC1, main_toc1), 40 functions, 28 live.
// Primary class: CKAnimationMarkContainer  key 0x898c  category Logic  size 0x10  vtable 0xb166f8
// Other owners: CinematicStreamEvent (3), CinematicStreamKey (3), CinematicStream (3), AnimMark (2), CinematicStreamChunk (2), CKCinematicStreamCpnt (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x7d350  CKAnimationMarkContainer_Delete
//   [ ] 0x7d3a0  CKAnimationMarkContainer_Construct  [dead]
//   [ ] 0x7d3c0  CKAnimationMarkContainer_Construct_2  [dead]
//   [ ] 0x7d3e0  RegisterCKAnimationMarkContainerClass
//   [ ] 0x7d458  _GLOBAL__I_7d458
//   [ ] 0x7d468  CKAnimationMarkContainer_Clear_2  [dead]
//   [x] 0x7d568  CKAnimationMarkContainer_DeleteArray
//   [x] 0x7d608  CKAnimationMarkContainer_CreateArray
//   [x] 0x7d6b8  CKAnimationMarkContainer_Create
//   [x] 0x7d708  CKAnimationMarkContainer_Save
//   [x] 0x7d710  CKAnimationMarkContainer_RecursiveRegistration  (returns 1: the default slot)
//   [x] 0x7d718  CKAnimationMarkContainer_DeletingDestructor  (the destructor 0x7d798; delete)
//   [x] 0x7d798  CKAnimationMarkContainer_Destructor
//   [ ] 0x7d800  CKAnimationMarkContainer_Destructor_2  [dead]
//   [x] 0x7d868  CKAnimationMarkContainer_Load
//   [x] 0x7db98  CKAnimationMarkContainer_Destroy
//   [x] 0x7dc98  AnimMark_SaveChannel
//   [x] 0x7dcf8  AnimMark_LoadChannel
//   [x] 0x7dd60  KStub_Nop_7dd60  (AnimMark::ClearKeys: empty)
//   [ ] 0x7dd68  CinematicStreamChunk_Construct_2_maybe  [dead]
//   [x] 0x7dd88  CinematicStreamChunk_Construct_maybe  (CKCinematicStreamCpnt::SChunk::Construct)
//   [x] 0x7dda8  CinematicStreamEvent_Construct_maybe
//   [ ] 0x7ddb8  CinematicStreamKey_Construct_2_maybe  [dead]
//   [x] 0x7ddd8  CinematicStreamKey_Construct_maybe
//   [ ] 0x7ddf8  FUN_0007ddf8  [dead]
//   [x] 0x7de18  CinematicStreamKey_Load_maybe
//   [ ] 0x7dee8  KStub_Return1_7dee8  [dead]
//   [ ] 0x7def0  FUN_0007def0  [dead]
//   [x] 0x7df20  CKCinematicStreamCpnt_FreeEntryBuffers_maybe
//   [ ] 0x7dfa8  CinematicStreamEvent_Construct_2_maybe  [dead]
//   [ ] 0x7dfb8  FUN_0007dfb8  [dead]
//   [ ] 0x7dfd8  FUN_0007dfd8  [dead]
//   [x] 0x7dff8  CinematicStreamEvent_Load_maybe
//   [x] 0x7e0a0  CKCinematicStreamCpnt_AllocStreamBuffer_maybe
//   [x] 0x7e1d8  CinematicStream_ResolveCamera_maybe
//   [x] 0x7e258  KStub_Return1_7e258
//   [x] 0x7e260  KStub_Return1_7e260
//   [x] 0x7e268  CinematicStream_ResetTrackBufferPtr_maybe
//   [x] 0x7e290  KStub_Return0_7e290
//   [x] 0x7e298  CinematicStream_FreeTrackBuffer_maybe
//
//   [ ] 0x999910  CKAnimationMarkContainer_GetClassType  [inline]
//   [ ] 0x999918  CKAnimationMarkContainer_GetClassID  [inline]
//   [ ] 0x999920  KStub_Return4_999920  [inline]
//   [ ] 0x999928  KStub_Return3_999928  [inline]
//   [ ] 0x999930  KStub_Return1_999930  [inline]
//   [ ] 0x999938  AnimMarkConst1_ValueAt  [inline]
//   [ ] 0x999940  AnimMarkConst1_MaxInRange  [inline]
//   [ ] 0x999948  AnimMarkConst1_MinInRange  [inline]
//   [ ] 0x999950  AnimMarkConst1_CrossedValue  [inline]
//   [ ] 0x999958  AnimMarkConst1_GetKeyValue  [inline]
//   [ ] 0x999960  KStub_Return0_999960  [inline]
//   [ ] 0x999968  AnimMarkConst0_ValueAt  [inline]
//   [ ] 0x999970  AnimMarkConst0_MaxInRange  [inline]
//   [ ] 0x999978  AnimMarkConst0_MinInRange  [inline]
//   [ ] 0x999980  AnimMarkConst0_CrossedValue  [inline]
//   [ ] 0x999988  AnimMarkConst0_GetKeyValue  [inline]
//   [ ] 0x999990  KStub_Return2_999990  [inline]
//   [x] 0x999998  AnimMarkKeys2_ClearKeys  [inline]
//   [x] 0x9999f8  AnimMarkKeys4_ClearKeys  [inline]
//   [ ] 0x999a58  AnimMarkKeys3_GetKeyValue  [inline]
//   [ ] 0x999a70  AnimMarkKeys4_GetKeyValue  [inline]
//   [x] 0x999aa0  AnimMarkKeys2_ValueAt  [inline]  (inline in the header)
//   [ ] 0x999b70  AnimMarkKeys3_ValueAt  [inline]
//   [x] 0x999c40  AnimMarkKeys4_ValueAt  [inline]  (inline in the header)
//   [ ] 0x999d38  AnimMarkKeys4_CrossedValue  [inline]
//   [ ] 0x999e10  AnimMarkKeys3_CrossedValue  [inline]
//   [ ] 0x999f58  AnimMarkKeys3_MinInRange  [inline]
//   [ ] 0x99a088  AnimMarkKeys3_MaxInRange  [inline]
//   [x] 0x99a1b8  AnimMarkKeys2_CrossedValue  [inline]  (inline in the header)
//   [ ] 0x99a300  AnimMarkKeys2_MinInRange  [inline]
//   [x] 0x99a430  AnimMarkKeys2_MaxInRange  [inline]  (inline in the header)
//   [ ] 0x99a560  AnimMarkKeys4_MinInRange  [inline]
//   [ ] 0x99a6b8  AnimMarkKeys4_MaxInRange  [inline]
//   [ ] 0x99a810  CKAnimationMarkContainer_IsKindOfClass  [inline]
//   [ ] 0x99a838  AnimMarkKeys3_ClearKeys  [inline]
//   [x] 0x99a898  AnimMarkConst1_Save  [inline]
//   [x] 0x99a910  AnimMarkKeys2_Save  [inline]
//   [x] 0x99aa78  AnimMarkKeys3_Save  [inline]
//   [x] 0x99abe0  AnimMarkKeys4_Save  [inline]
//   [x] 0x99ad48  AnimMarkConst0_Load  [inline]
//   [x] 0x99add0  AnimMarkConst0_Save  [inline]
//   [x] 0x99ae50  AnimMarkConst1_Load  [inline]
//   [x] 0x99aed8  AnimMarkKeys2_Load  [inline]
//   [x] 0x99b0a8  AnimMarkKeys3_Load  [inline]
//   [x] 0x99b278  AnimMarkKeys4_Load  [inline]
#include "k2000/logic/animation/CKAnimationMarkContainer.h"

#include <cstring>
#include <new>

#include "k2000/components/CKCinematicStreamCpnt.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Mat4.h"

// 0x0007d6b8 CKAnimationMarkContainer_Create
CKAnimationMarkContainer::CKAnimationMarkContainer() {
    m_ppMarks = nullptr;
    m_capacity = 1;
    m_count = 0;
}

// 0x0007d868 CKAnimationMarkContainer_Load
int32_t CKAnimationMarkContainer::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        uint32_t count;
        ReadU32LE(file, &count);
        if (count == 0) {
            m_capacity = 1;
            m_ppMarks = static_cast<AnimMark**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(AnimMark*))));
        } else {
            m_capacity = count;
            m_ppMarks = static_cast<AnimMark**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(AnimMark*))));
        }
        if (m_capacity < count) {  // the inlined reserve; never true here
            uint32_t grown = count + 1;
            m_ppMarks = static_cast<AnimMark**>(Mem_ReallocAligned16(m_ppMarks, grown * static_cast<uint32_t>(sizeof(AnimMark*))));
            m_capacity = grown;
        }
        m_count = count;
        for (uint32_t i = 0; i < count; ++i) {
            uint32_t markType;
            ReadU32LE(file, &markType);
            switch (markType) {  // jump table 0x7d9ec
                case 0: m_ppMarks[i] = new AnimMarkConst0(); break;  // 0x7da00 OperatorNew(0xc)
                case 1: m_ppMarks[i] = new AnimMarkConst1(); break;  // 0x7db1c OperatorNew(0xc)
                case 2: m_ppMarks[i] = new AnimMarkKeys2(); break;   // 0x7db48 OperatorNew(0x14)
                case 3: m_ppMarks[i] = new AnimMarkKeys3(); break;   // 0x7daa8 OperatorNew(0x14)
                case 4: m_ppMarks[i] = new AnimMarkKeys4(); break;   // 0x7daf0 OperatorNew(0x14)
                default: break;  // BUG(original): the slot keeps whatever the block held and is called below
            }
            m_ppMarks[i]->Load(file);  // the mark's vt+0x8
        }
    }
    return 1;
}

// The cinematic stream's keys, events and channel buffers (CKCinematicStreamCpnt.h).

// 0x0007de18 CinematicStreamKey_Load_maybe
int32_t CKCinematicStreamCpnt::SKey::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_fTime);  // one byte-swapped word
        ReadS32LE(file, &m_id);
    }
    return 1;
}

// 0x0007df20 CKCinematicStreamCpnt_FreeEntryBuffers_maybe
void CKCinematicStreamCpnt::SChannel::FreeBuffers() {
    if (m_pBuffer != nullptr) {
        ::operator delete[](m_pBuffer);  // OperatorDelete_Bridge on the OperatorNewArray block (one heap on the PS3)
        m_pBuffer = nullptr;
    }
    if (m_pMatrix10 != nullptr) {
        RwMatrixDestroy_Thunk(m_pMatrix10);
        m_pMatrix10 = nullptr;
    }
    if (m_pMatrix24 != nullptr) {
        RwMatrixDestroy_Thunk(m_pMatrix24);
        m_pMatrix24 = nullptr;
    }
}

// 0x0007dff8 CinematicStreamEvent_Load_maybe
int32_t CKCinematicStreamCpnt::SEvent::Load(IKFile* file, int32_t type) {
    const int32_t result = m_tsTriggers.Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) ReadS32LE(file, &m_id);
    return result;
}

// 0x0007e0a0 CKCinematicStreamCpnt_AllocStreamBuffer_maybe
void CKCinematicStreamCpnt::SChannel::AllocBuffer(uint32_t size) {
    FreeBuffers();  // the same three frees, inlined
    if (size == 0) {
        m_pBuffer = nullptr;
    } else {
        m_pBuffer = ::operator new[](size);  // OperatorNewArray
        std::memset(m_pBuffer, 0, size);
    }
    m_pMatrix10 = RwMatrixCreate_Thunk();
    m_pMatrix24 = RwMatrixCreate_Thunk();
}

// 0x0007e258 KStub_Return1_7e258
int32_t CinematicStream_LoadNothing(void* /*buffer*/, IKFile* /*file*/, int32_t /*type*/) { return 1; }

// 0x0007e290 KStub_Return0_7e290
uint32_t CinematicStream_GetNoBufferSize() { return 0; }

// 0x0007e260 KStub_Return1_7e260: channel type 1's save slot (+0x30, not called).
int32_t CinematicStream_SaveNothing(void* /*buffer*/, IKFile* /*file*/) { return 1; }

// 0x0007e1d8 CinematicStream_ResolveCamera_maybe (type 1's slot +0x34, not called): a camera (0x47) or null.
IKSerializable* CinematicStream_ResolveCamera(IKSerializable* object) {
    if (object == nullptr) return nullptr;
    return object->IsKindOfClass(0x47) != 0 ? object : nullptr;
}

// 0x0007e268 CinematicStream_ResetTrackBufferPtr_maybe (type 1's slot +0x00): the track's keys right behind its header. 1.
uint8_t CinematicStream_ResetTrackBufferPtr(SCinematicStreamTrackType* type, void* /*data*/) {
    SCinematicCameraTrack* track = static_cast<SCinematicCameraTrack*>(type->m_pChunk->m_pData);
    track->m_pKeys = reinterpret_cast<SCinematicCameraKey*>(track + 1);
    type->m_pChunk->m_pData = track;
    return 1;
}

// 0x0007e298 CinematicStream_FreeTrackBuffer_maybe (type 1's slot +0x04: no code calls it): the keys freed as an array
// (OperatorDeleteArray on their cookie, 4 bytes before them), the track deleted.
void CinematicStream_FreeTrackBuffer(SCinematicStreamTrackType* type) {
    SCinematicCameraTrack* track = static_cast<SCinematicCameraTrack*>(type->m_pChunk->m_pData);
    if (track == nullptr) return;
    if (track->m_pKeys != nullptr) {
        ::operator delete[](reinterpret_cast<uint8_t*>(track->m_pKeys) - 4);
        track->m_pKeys = nullptr;
    }
    ::operator delete(track);  // OperatorDelete_Bridge
    type->m_pChunk->m_pData = nullptr;
}

// 0x0007db98 CKAnimationMarkContainer_Destroy
void CKAnimationMarkContainer::Destroy() {
    for (uint32_t i = 0; i < m_count; ++i) {
        m_ppMarks[i]->ClearKeys();
        AnimMark* mark = m_ppMarks[i];
        if (mark != nullptr) delete mark;  // the base vtable stored, then OperatorDelete
    }
    if (m_ppMarks != nullptr) {
        Mem_FreeAligned16(m_ppMarks);
        m_ppMarks = nullptr;
    }
    m_count = 0;
    m_ppMarks = nullptr;
}
