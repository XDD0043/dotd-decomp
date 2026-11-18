// CLocManager.h - localisation (key 0xecc, vtable 0xb14668, size 0xc8). Original unit: CLocManager.cpp.
// XXL2: K/KCore/Localisation/CLocManager.h (CLocManager::SLanguageData m_CurrentLanguage, the language
// tables, m_vTRCTexts); DotD keeps the text objects themselves and gives each its string.
//
// GAME (type 1) lists the localised text objects (CKStdText) and the TRC texts by id; a game
// localisation file (GLC, type 3) gives the language table and every text's string, stored in two
// UTF-16 blocks: each CKLocText (+0x18) then points into them.
#pragma once
#include <cstdint>

#include "k2000/core/IKUpdatable.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKLocText;
class CKTrcText;

// The u32-keyed hash table embedded at +0x14 (vtable 0xb146c8): TRC text id -> CKTrcText. Names from
// Ghidra (HashTableU32_*); nodes are 0xc-byte {key, value, next} (operator new).
class HashTableU32 {
public:
    struct Node {
        uint32_t m_key;        // +0x00
        CKLocText* m_value;    // +0x04
        Node* m_next;          // +0x08
    };

    virtual ~HashTableU32() {}                                                   // vt+0x00 / +0x04 0x994668 / 0x9947a8
    virtual uint32_t HashKey(uint32_t key) { return key % m_bucketCount; }      // vt+0x08 0x994618
    // vt+0x0c 0x994630: 1 when the keys are equal.
    virtual uint8_t KeysEqual(uint32_t a, uint32_t b) {
        const uint32_t sign = static_cast<uint32_t>(static_cast<int32_t>(a ^ b) >> 31);
        return static_cast<uint8_t>((((sign ^ a ^ b) - sign) - 1) >> 31);
    }
    virtual void InitNode(Node* node, uint32_t key, CKLocText* value) {          // vt+0x10 0x994658
        node->m_value = value;
        node->m_key = key;
    }
    virtual void ReleaseNode(Node*) {}                                           // vt+0x14 0x994650 (empty)

    uint32_t m_count;        // +0x04
    uint32_t m_bucketCount;  // +0x08 37
    Node** m_buckets;        // +0x0c new[37], cleared
};

class CLocManager : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x3b)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xecc || key == 0xc; }  // vt+0x08 0x994788

    // A text variable of GAME's list (+0xbc), 0xc bytes (DotD): the value the texts' variable tokens show,
    // the variable's name hash (Str_HashXor4) and a third word (CLocManager_GetTextVariable / Set).
    struct STrcRecord {
        uint32_t m_unk0;  // +0x00 the value (CLocManager_SetTextVariableValue_maybe)
        uint32_t m_unk4;  // +0x04 the name hash (CLocManager_FindTextVariable_maybe)
        uint32_t m_unk8;  // +0x08 CLocManager_GetTextVariable / SetTextVariable
    };

    CLocManager();  // 0x00037488 CLocManager_Construct (inlined in CLocManager_Create 0x37b28)
    ~CLocManager() override;

    static IKBaseClass* Create();                       // 0x00037b28 CLocManager_Create
    static void Delete(IKBaseClass* object);            // 0x00036f28 CLocManager_Delete (vt+0x04)
    static IKBaseClass* CreateArray(uint32_t count, uint16_t* elementSize);  // 0x00037958 CLocManager_CreateArray
    static void DeleteArray(IKBaseClass* first);                            // 0x000373e8 CLocManager_DeleteArray

    // vt+0x0c 0x00037238 CLocManager_DestroyGame: both text blocks freed, the default TRC text destroyed (its Destroy,
    // then ClassRegistry_DestroyObject), the TRC records' block freed. The texts and the hash table stay.
    void DestroyGame() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00037c20 CLocManager_Load
    int32_t GetSerializationFlags() override { return 0; }  // vt+0x34 0x994610
    // vt+0x50 0x36fb8 CLocManager_vf50 (empty): Engine_ReloadLocalizedData calls it first.
    virtual void UpdateLocalizedData() {}
    // vt+0x54 0x000378e8 CLocManager_UnloadLocalizedData: the GLC data marked invalid and both text blocks
    // freed (the texts keep pointing into them until the next GLC load).
    virtual void UnloadLocalizedData();

    // 0x00037028 CLocManager_GetText: the TRC text `id`, else the default one.
    CKLocText* GetText(uint32_t id);
    // The text variables (+0xbc). 0x00037328 CLocManager_FindTextVariable_maybe: the index of the variable
    // named `name`, -1 for none (or a null name).
    int32_t FindTextVariable(const char* name);
    uint32_t GetTextVariable(uint32_t index);                // 0x00037578 CLocManager_GetTextVariable: 0 past the end
    uint8_t SetTextVariable(uint32_t index, uint32_t value);  // 0x000375b0 CLocManager_SetTextVariable
    // 0x000375f8 CLocManager_SetTextVariableValueByName_maybe: a changed value posts the 2D manager's event 5
    // (the texts refreshed). 1 when the variable exists.
    uint8_t SetTextVariableValueByName(const char* name, int32_t value);
    int32_t GetTextVariableValue(uint32_t index);            // 0x000376f8 CLocManager_GetTextVariableValue_maybe
    // 0x00037730 CLocManager_SetTextVariableValue_maybe: as SetTextVariableValueByName, by index.
    uint8_t SetTextVariableValue(uint32_t index, int32_t value);
    // 0x000377c0 CLocManager_GetVoiceLanguageIndex_maybe: the current language's +0x30 entry (the language
    // whose speech it uses), the current language itself when that is -1 or out of the table.
    uint32_t GetVoiceLanguageIndex();

    // 0x00036fc8 CLocManager_GetSystemLanguageIndex_maybe: the index of the system language in the
    // language table GLC loads (searched from the last), else the default (+0xb8).
    uint32_t GetSystemLanguageIndex();

    TVector<CKLocText*, 10> m_vpTexts;      // +0x04 GAME's text objects (CKStdText), in file order
    CKTrcText* m_pDefaultTrcText;           // +0x10 created by the Load (key 0x684c); its text is "-NO TRC DEFINED-"
    HashTableU32 m_trcTexts;                // +0x14 TRC id -> CKTrcText
    uint16_t* m_wszAllTexts;                // +0x24 XXL2 m_CurrentLanguage.m_wszAllTexts: the texts' block
    uint16_t* m_wszAllTRCTexts;             // +0x28 XXL2 m_CurrentLanguage.m_wszAllTRCTexts: the TRC texts' block
    uint16_t m_ui16NbLanguage;              // +0x2c XXL2 m_ui16NbLanguage
    uint16_t m_pad2e;
    int32_t m_ai32TextId[16];               // +0x30 XXL2 m_ai32TextId (read second in DotD)
    int32_t m_ai32SystemLanguage[16];       // +0x70 XXL2 m_ai32SystemLanguage (read first; GetSystemLanguageIndex)
    uint8_t m_bGameLocalizedDataValid;      // +0xb0 XXL2 m_bGameLocalizedDataValid: 1 after GLC
    uint8_t m_padB1;                        // +0xb1 never written
    uint16_t m_languageIndex;               // +0xb2 XXL2 m_ui16CurrentLanguageIndex: the language whose loc files are loaded
    int32_t m_systemLanguage;               // +0xb4 XXL2 m_eBootSystemLanguageId: cellSysutilGetSystemParamInt(LANG), 1 if it fails
    uint32_t m_defaultLanguageIndex;        // +0xb8 GLC: the language used when the system's is not in the table; name ours
    TVector<STrcRecord, 5> m_vTrcRecords;   // +0xbc GAME
};
DOTD_ASSERT_SIZE(CLocManager, 0xc8);
DOTD_ASSERT_OFFSET(CLocManager, m_vpTexts, 0x04);
DOTD_ASSERT_OFFSET(CLocManager, m_pDefaultTrcText, 0x10);
DOTD_ASSERT_OFFSET(CLocManager, m_trcTexts, 0x14);
DOTD_ASSERT_OFFSET(CLocManager, m_wszAllTexts, 0x24);
DOTD_ASSERT_OFFSET(CLocManager, m_ui16NbLanguage, 0x2c);
DOTD_ASSERT_OFFSET(CLocManager, m_ai32TextId, 0x30);
DOTD_ASSERT_OFFSET(CLocManager, m_ai32SystemLanguage, 0x70);
DOTD_ASSERT_OFFSET(CLocManager, m_bGameLocalizedDataValid, 0xb0);
DOTD_ASSERT_OFFSET(CLocManager, m_languageIndex, 0xb2);
DOTD_ASSERT_OFFSET(CLocManager, m_systemLanguage, 0xb4);
DOTD_ASSERT_OFFSET(CLocManager, m_defaultLanguageIndex, 0xb8);
DOTD_ASSERT_OFFSET(CLocManager, m_vTrcRecords, 0xbc);
