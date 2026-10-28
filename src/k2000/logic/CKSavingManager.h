// CKSavingManager.h - save-game serialisation (key 0x18c, vtable 0xb13e78, size 0x24). Original unit:
// CKSavingManager.cpp. STUB(save data): nothing is saved yet.
//
// XXL2 (K/KCore/Serialization): CKSavingManager : IKSavingInterfaces : IKBaseClass, not IKSerializable.
// The PS3 slots +0x48..+0x58 are XXL2's slots 17..21, one later: DotD inserted a slot between +0x28 and
// +0x44 (outputs/remake/research/xxl2-symbols.md).
#pragma once
#include "k2000/core/IKBaseClass.h"

class IKFile;
class IKSerializable;

// What an IKFile calls back into when it saves (IKFile::m_pSavingInterfaces).
class IKSavingInterfaces : public IKBaseClass {
public:
    // vt+0x24 0x2bdb8 CKSavingManager_RegisterSerializableObject (XXL2: IKSerializable*, IKSerializable*).
    // STUB(save data): nothing is registered yet.
    virtual void RegisterSerializableObject(IKSerializable* /*object*/, IKSerializable* /*owner*/) {}
};

class CKSavingManager : public IKSavingInterfaces {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 6)

    CKSavingManager();
    ~CKSavingManager() override;

    static IKBaseClass* Create();                       // 0x0002bfa0 CKSavingManager_Create
    static void Delete(IKBaseClass* object);

    // vt+0x54 0x993c18 CKSavingManager_KUInitialize: InitializeCKGameLoopSubsystems calls it once after
    // creating the manager; returns 1 (XXL2: KError). The slots in between are not ported yet.
    virtual int32_t KUInitialize() { return 1; }
    virtual void KUDestroy() {}                         // vt+0x58 0x993c20
};
