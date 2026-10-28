// IKSerializable.h - the serialised objects (key 0xc; XXL2: K/KCore/Interfaces/IKSerializable.h).
//
// Every class a KP3 file holds derives from it (557 of the registered classes), so the loader works on
// IKSerializable pointers. Slots +0x24..+0x4c are the same in XXL2. The defaults are the shared stubs at
// 0x990b48..0x990d58. XXL2's IKSerializable also has a debug pointer (m_pDbgObjectInfos) that the PS3
// build does not: on the PS3 the class is only the vtable pointer.
#pragma once
#include <cstdint>

#include "k2000/core/IKBaseClass.h"

class IKFile;

// C2.2 gm: XXL2 SApplyGameState (8 bytes): the info id and the game-state id an object is set to
// (CKGameModule's ApplyLeft / ApplyDone pass {m_ui32Ident, m_ui32StateIdForLeft / ForDone}).
struct SApplyGameState {
    uint32_t m_ui32InfoId;       // +0x00
    uint32_t m_ui32GameStateId;  // +0x04
};

// The serialisation type a Load/Save/PostLoad is called with (XXL2 SerializationType.h; the PS3 values
// 7 and 8 are DotD's: 8 is the game-structure block).
enum ESerializationType : int32_t {
    K_LEVEL_PLATEFORMS = 0,     // a level or sector file (LVLnnn.KP3, STRnn_nn)
    K_GAME_PLATEFORMS = 1,      // GAME.KP3
    K_LEVEL_LOCALIZATION = 2,   // nnLLCnnn.KP3
    K_GAME_LOCALIZATION = 3,    // nnGLC.KP3
    K_LEVEL_MEMCARD = 4,
    K_GAME_MEMCARD = 5,
    K_OPTIONS_MEMCARD = 6,
};

// Abstract: there is no PS3 vtable of its own; every registered class's IsKindOfClass tests 0xc itself.
class IKSerializable : public IKBaseClass {
public:
    // vt+0x24  0x990b48. XXL2: RecursiveRegistration(ESerializationType): registers the object (and the
    // objects it owns) with the saving manager.
    virtual void RecursiveRegistration(int32_t /*type*/) {}
    virtual int32_t Save(IKFile* /*file*/) { return 1; }      // vt+0x28  0x990b50 (arguments unverified)
    // vt+0x2c  0x990b58. Reads this object's data from the file; 1 = ok. type: ESerializationType, or
    // DotD's 7/8 (8 = the game-structure block).
    virtual int32_t Load(IKFile* /*file*/, int32_t /*type*/) { return 1; }
    virtual int32_t PostLoad(int32_t /*type*/) { return 1; }  // vt+0x30  0x990b60
    virtual int32_t GetSerializationFlags() { return 1; }      // vt+0x34  0x990b68
    virtual void SetDefaultState(int32_t /*flag*/) {}         // vt+0x38  0x990b70 (XXL2: Bool)
    virtual int32_t SetGameState(const SApplyGameState* /*state*/) { return 1; }  // vt+0x3c  0x990b78 (XXL2: const SApplyGameState*)
    virtual int32_t GetInfo() { return 1; }                    // vt+0x40  0x990b80 (XXL2: IKInfo*, EGetInfoRequestType)
    // vt+0x44  0x990b88 (default: null). GUID classes (IKGameObject) return this+4 (0x993d60).
    virtual const uint32_t* GetGuid() { return nullptr; }
    // vt+0x48  0x990ce8 (default: nothing). GUID classes copy it to this+4 (0x993dc8).
    virtual void SetGuid(const uint32_t* /*guid*/) {}
    virtual const char* GetName();                            // vt+0x4c  0x990d58 (IKSerializable.cpp)
};
