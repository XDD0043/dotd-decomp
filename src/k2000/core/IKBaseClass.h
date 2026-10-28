// IKBaseClass.h - the root of the K engine class tree (XXL2: K/KCore/Interfaces/IKBaseClass.h).
//
// Names from the XXL2 Mac debug symbols (outputs/remake/research/xxl2-symbols.md): XXL2 runs the same
// engine, its vtables match ours slot for slot, and it uses the same class keys.
//
// Class keys: key = (id << 6) | category. IsKindOfClass(key) at vt+0x08 compares against the class's
// own key and every ancestor's. IKBaseClass has no key; the first keyed class is IKSerializable (0xc).
// Only IKSerializable, IKLoadingInterfaces (0x93e, CKLoadingManager) and IKSavingInterfaces
// (CKSavingManager) derive from IKBaseClass directly. The PS3 vtable of IKBaseClass is 0xb12ab8 (9 slots).
//
// Virtual methods are declared in vtable slot order. Argument lists marked "unverified" have not been
// checked against a PS3 implementation yet. The out-of-line bodies of the shared stubs (KStub_* at
// 0x990b00..0x990c08) are inline here.
#pragma once
#include <cstdint>

class IKSerializable;

// Class categories (XXL2 CKClassInfo::m_eClassType; the names are ours, XXL2 keeps them in macros).
enum KClassCategory : int32_t {
    kCategoryManager = 0,
    kCategoryService = 1,
    kCategoryHook = 2,
    kCategoryHookLife = 3,
    kCategoryGroup = 4,
    kCategoryGroupLife = 5,
    kCategoryComponent = 6,
    kCategoryCamera = 7,
    kCategoryCinematic = 8,
    kCategoryDictionary = 9,
    kCategoryGeometry = 10,
    kCategoryNode = 11,
    kCategoryLogic = 12,
    kCategoryGraphical = 13,
    kCategoryError = 14,
    kCategoryCount = 15,  // ClassManager keeps 15 tables (0..14)
};

constexpr uint32_t MakeClassKey(uint32_t category, uint32_t id) { return (id << 6) | category; }
constexpr uint32_t ClassKeyCategory(uint32_t key) { return key & 0x3f; }
constexpr uint32_t ClassKeyId(uint32_t key) { return (key >> 6) & 0x7ff; }

// Declares the class key (category, id) of a registered class (XXL2: CLASS_INFO CLASS_TYPE / CLASS_ID).
#define DOTD_CLASS_KEY(category, id)                                       \
    static constexpr uint32_t kClassKey = MakeClassKey((category), (id)); \
    int32_t GetClassType() override { return (category); }               \
    int32_t GetClassID() override { return (id); }

// The registry factories of a class (XXL2 CKClassInfo m_pfnCreateClass, m_pfnDeleteClass,
// m_pfnCreateArrayClass, m_pfnDeleteArrayClass): Create (new T), Delete, CreateArray (new T[count],
// the element size written to *elementSize: the stride references use) and DeleteArray. This is what
// every original Create<Class>/CreateArray<Class> pair does (operator new / new[] plus the constructor).
#define DOTD_DECLARE_FACTORIES(Class)                                                    \
    static IKBaseClass* Create() { return new Class(); }                                 \
    static void Delete(IKBaseClass* object) { delete object; }                           \
    static IKBaseClass* CreateArray(uint32_t count, uint16_t* elementSize) {             \
        if (elementSize != nullptr) *elementSize = static_cast<uint16_t>(sizeof(Class)); \
        return new Class[count];                                                         \
    }                                                                                    \
    static void DeleteArray(IKBaseClass* first) { delete[] static_cast<Class*>(first); }

// vtable 0xb12ab8 (9 slots, +0x00..+0x20).
class IKBaseClass {
public:
    virtual ~IKBaseClass() {}                                      // vt+0x00 / +0x04  0x990cd8 / 0x990ca8
    virtual int32_t IsKindOfClass(uint32_t /*key*/) { return 0; }  // vt+0x08  0x990b00 (root: 0)
    virtual void DestroyGame() {}                                  // vt+0x0c  0x990b08
    virtual void Destroy() {}                                      // vt+0x10  0x990b10
    virtual int32_t GetClassType() = 0;                            // vt+0x14
    virtual int32_t GetClassID() = 0;                              // vt+0x18
    // vt+0x1c  0x990b18. XXL2: MessageProc(UInt16, void*); the PS3 passes the same two (KBase730C_MessageProc
    // 0x515b78 tests the id's high byte 0x23 and compares the pointer with its CKFlashMessageIn references).
    virtual int32_t MessageProc(uint16_t /*message*/, void* /*data*/) { return 1; }
    // vt+0x20  0x990b20 (root: 0). The owner of non-recreatable (global) instances hands them to the
    // loader (Engine_GetGlobalInstances). out points to the slot to fill: for count 1 it
    // receives the object, for count > 1 it holds a pointer array that receives count objects.
    // Returns 1 when provided. XXL2: (UInt32, UInt32, UInt32, IKSerializable**&).
    virtual uint8_t FindNonRecreableInstances(int32_t /*category*/, uint32_t /*id*/, uint32_t /*count*/,
                                              void* /*out*/) {
        return 0;
    }
};
