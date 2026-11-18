// CKSavingManager.h - save-game serialisation (key 0x18c, vtable 0xb13e78, size 0x24). Original unit:
// CKSavingManager.cpp. C2.8 save-menu: SaveObjects and its writers are ported (WriteAsContiguousHandles 0x2c890 and
// WriteTexture 0x2cae8 are not: no save of LVL010 writes them).
//
// XXL2 (K/KCore/Serialization): CKSavingManager : IKSavingInterfaces : IKBaseClass, not IKSerializable.
// The PS3 slots +0x48..+0x58 are XXL2's slots 17..21, one later: DotD inserted a slot between +0x28 and
// +0x44 (outputs/remake/research/xxl2-symbols.md).
#pragma once
#include <cstdint>

#include "k2000/core/IKBaseClass.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class IKFile;
class IKSerializable;

// What an IKFile calls back into when it saves (IKFile::m_pSavingInterfaces).
class IKSavingInterfaces : public IKBaseClass {
public:
    // vt+0x24 (XXL2: IKSerializable*, IKSerializable*; pure in XXL2). CKSavingManager's: 0x2bdb8.
    virtual void RegisterSerializableObject(IKSerializable* /*object*/, IKSerializable* /*owner*/) {}
};

class CKSavingManager : public IKSavingInterfaces {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 6)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x18c; }  // vt+0x08 0x993d08

    CKSavingManager();
    ~CKSavingManager() override;

    static IKBaseClass* Create();                       // 0x0002bfa0 CKSavingManager_Create
    static void Delete(IKBaseClass* object);
    // 0x0002c000 CKSavingManager_CreateArray / 0x0002bef8 CKSavingManager_DeleteArray: new[] / delete[] (the constructor's
    // stores per element).
    static IKBaseClass* CreateArray(uint32_t count, uint16_t* elementSize);
    static void DeleteArray(IKBaseClass* first);

    // vt+0x24 0x0002bdb8 CKSavingManager_RegisterSerializableObject (XXL2 RegisterSerializableObject(
    // IKSerializable*, IKSerializable*)): while a save runs (m_eCurrentSerializationType 4..7), `object` is
    // added to m_vMemCardRegistred unless it is there already (the block grows by 10). The owner is not read.
    void RegisterSerializableObject(IKSerializable* object, IKSerializable* owner) override;

    // C2.8 save-menu: the slots +0x28..+0x44 (inline in the original).
    virtual void SetCurrentStream(int8_t stream) { m_i8CurrentStream = stream; }  // vt+0x28 0x993c78
    virtual int8_t GetCurrentStream() { return m_i8CurrentStream; }             // vt+0x2c 0x993c80
    virtual int32_t Vf30() { return 0; }                                        // vt+0x30 0x993be8
    virtual int32_t Vf34() { return 0; }                                        // vt+0x34 0x993bf0
    virtual int32_t Vf38() { return 0; }  // vt+0x38 0x993cc0 ("K_Err: K_ERROR" to the empty log KStub_Nop_10b60)
    virtual int32_t Vf3C() { return 0; }  // vt+0x3c 0x993c90 (the same)
    virtual int32_t GetTargetPlateform() { return m_eTargetPlateform; }        // vt+0x40 0x993c68
    virtual uint32_t Vf44() { return m_unk0c; }                                 // vt+0x44 0x993c70

    // vt+0x48 0x0002c748 CKSavingManager_WriteAsHandle (XXL2 WriteAsHandle(IKFile*, IKSerializable*)): the object's
    // reference id (CKLoadingManager_GetObjectRefId while a save runs, else -1) as a little-endian word; for -3 (an
    // object known by its UUID) the UUID follows (Uuid_Write). Returns the first write's byte count.
    uint32_t WriteAsHandle(IKFile* file, IKSerializable* object);
    // vt+0x4c 0x0002c890 CKSavingManager_WriteAsContiguousHandles: WriteAsHandle of each of `count` objects; the byte
    // count of the handle words (the UUIDs are not counted).
    uint32_t WriteAsContiguousHandles(IKFile* file, IKSerializable* const* objects, uint32_t count);
    // vt+0x50 0x0002cae8 CKSavingManager_WriteTexture: the texture's name length (a little-endian half word) and its
    // name; a null texture writes a 0 length and nothing. Returns the bytes written.
    uint32_t WriteTexture(IKFile* file, const struct RwTexture* texture);
    // 0x0002bd60 CKSavingManager_GetObjectRefId: the loading manager's id while a save runs (types 4..7), else -1.
    int32_t GetObjectRefId(IKSerializable* object);
    // 0x0002c248 CKSavingManager_WriteObjectList: the count (little-endian), then per object its handle (WriteAsHandle,
    // or the 4 bytes of the pointer without saving interfaces), a word for the end offset, the object's Save(file,
    // type) and the end offset written back (absolute position, little-endian).
    int32_t WriteObjectList(IKFile* file, IKSerializable** objects, uint32_t count, int32_t type);

    // vt+0x54 0x993c18 CKSavingManager_KUInitialize: InitializeCKGameLoopSubsystems calls it once after
    // creating the manager; returns 1 (XXL2: KError).
    virtual int32_t KUInitialize() { return 1; }
    virtual void KUDestroy() {}                         // vt+0x58 0x993c20
    // vt+0x5c 0x0002c538 CKSavingManager_SaveObjects (C2.8 save-menu): the registered-object list (re)started with room
    // for 10, the save type set; the game loop's and the core manager's RecursiveRegistration(type) list the objects
    // (RegisterSerializableObject), WriteObjectList writes them; then the list freed and the type back to 8.
    virtual int32_t SaveObjects(IKFile* file, int32_t type, uint32_t size);

    // XXL2 members (CKSavingManager.h), at the PS3 offsets CKSavingManager_Create stores them.
    int8_t m_i8CurrentStream;                            // +0x04 not set by Create
    uint8_t m_pad05[3];
    int32_t m_eTargetPlateform;                          // +0x08 Create: 8
    uint32_t m_unk0c;                                    // +0x0c (DotD) not set by Create
    int8_t m_i8NbStream;                                 // +0x10 Create: 0
    uint8_t m_pad11[3];
    TVector<IKSerializable*, 10> m_vMemCardRegistred;    // +0x14 Create: no block, capacity 10, empty
    int32_t m_eCurrentSerializationType;                 // +0x20 Create: 8 (no save running)
};
DOTD_ASSERT_SIZE(CKSavingManager, 0x24);
DOTD_ASSERT_OFFSET(CKSavingManager, m_eTargetPlateform, 0x08);
DOTD_ASSERT_OFFSET(CKSavingManager, m_i8NbStream, 0x10);
DOTD_ASSERT_OFFSET(CKSavingManager, m_vMemCardRegistred, 0x14);
DOTD_ASSERT_OFFSET(CKSavingManager, m_eCurrentSerializationType, 0x20);
