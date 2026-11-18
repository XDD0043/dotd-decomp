// CLocManager.cpp - reconstructed original translation unit 0x36fc8-0x38cf0 (GAME_TOC1, main_toc1), 26 functions, 25 live.
// Primary class: CLocManager  key 0xecc  category Logic  size 0xc8  vtable 0xb14668
// Other owners: TriggerPropertyRequest (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x36fc8  CLocManager_GetSystemLanguageIndex_maybe
//   [x] 0x37020  CLocManager_RecursiveRegistration  (IKSerializable's empty default)
//   [x] 0x37028  CLocManager_GetText
//   [ ] 0x37140  RegisterCLocManagerClass
//   [ ] 0x371b8  _GLOBAL__I_371b8
//   [ ] 0x371c8  CLocManager_FreeTextTableBuffers_maybe  [dead]
//   [x] 0x37238  CLocManager_DestroyGame
//   [x] 0x37328  CLocManager_FindTextVariable_maybe
//   [x] 0x373e8  CLocManager_DeleteArray
//   [x] 0x37488  CLocManager_Construct
//   [x] 0x37578  CLocManager_GetTextVariable
//   [x] 0x375b0  CLocManager_SetTextVariable
//   [x] 0x375f8  CLocManager_SetTextVariableValueByName_maybe
//   [x] 0x376f8  CLocManager_GetTextVariableValue_maybe
//   [x] 0x37730  CLocManager_SetTextVariableValue_maybe
//   [ ] 0x377b8  CLocManager_Save
//   [x] 0x377c0  CLocManager_GetVoiceLanguageIndex_maybe
//   [x] 0x377f8  CLocManager_Construct_2  (the same as 0x37488 CLocManager_Construct)
//   [x] 0x378e8  CLocManager_UnloadLocalizedData
//   [x] 0x37958  CLocManager_CreateArray
//   [x] 0x37b28  CLocManager_Create
//   [x] 0x37c20  CLocManager_Load
//   [x] 0x38860  CLocManager_DeletingDestructor  (the deleting form of 0x389e8)
//   [x] 0x389e8  CLocManager_Destructor
//   [x] 0x38b60  CLocManager_Destructor_2_maybe  (the same as 0x389e8 CLocManager_Destructor)
//   [x] 0x38cd8  TriggerPropertyRequest_SetGetter_maybe  (IKInfo.h AnswerInfo stands for it: the accessor (+0x04 / +0x08) and the value type (+0x0c))
//
//   [ ] 0x994600  CLocManager_GetClassType  [inline]
//   [ ] 0x994608  CLocManager_GetClassID  [inline]
//   [ ] 0x994610  CLocManager_GetSerializationFlags  [inline]
//   [x] 0x994618  HashTableU32_HashKey_2  [inline]
//   [x] 0x994630  HashTableU32_KeysEqual_2  [inline]
//   [x] 0x994650  KStub_Nop_994650  [inline]
//   [ ] 0x994668  HashTableU32_Destructor_2  [inline]
//   [ ] 0x994788  CLocManager_IsKindOfClass  [inline]
//   [ ] 0x9947a8  HashTableU32_DeletingDestructor_2  [inline]
#include "k2000/logic/ui/CLocManager.h"

#include <cstring>

#include "k2000/io/IKFile.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/logic/ui/CKLocText.h"
#include "k2000/logic/ui/CKTrcText.h"
#include "k2000/memory/Mem.h"
#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "platform/cell/sysutil.h"

namespace {
// The TRC texts' default (TOC -0x776c -> 0xc2964c, UTF-16).
const uint16_t kNoTrcDefined[] = {'-', 'N', 'O', ' ', 'T', 'R', 'C', ' ', 'D', 'E', 'F', 'I', 'N', 'E', 'D', '-', 0};

// 0x00010a18 Wcs_Length
uint32_t Wcs_Length(const uint16_t* s) {
    uint32_t n = 0;
    while (s[n] != 0) ++n;
    return n;
}

// 0x00010a40 WStr_CopyReturnEnd (the end is not used here)
uint16_t* WStr_CopyReturnEnd(uint16_t* dst, const uint16_t* src) {
    while ((*dst = *src) != 0) {
        ++dst;
        ++src;
    }
    return dst;
}

// The inlined TVector sizing of the Load: a block of exactly count elements (one when count is 0), the
// growth to (count / Grow + 1) * Grow when the capacity is smaller (never after that allocation), then
// the length.
template <class T, uint32_t Grow>
void LocVector_Allocate(TVector<T, Grow>* vector, uint32_t count) {
    if (count == 0) {
        vector->m_ui32NbElt = 1;
        vector->m_pBlock = static_cast<T*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(T))));
    } else {
        vector->m_ui32NbElt = count;
        vector->m_pBlock = static_cast<T*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(T))));
    }
    if (vector->m_ui32NbElt < count) {
        uint32_t capacity = (count / Grow) * Grow + Grow;
        if (capacity == 0) capacity = Grow;
        vector->m_pBlock = static_cast<T*>(Mem_ReallocAligned16(vector->m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        vector->m_ui32NbElt = capacity;
    }
    vector->m_ui32NbUsedElt = count;
}

// count UTF-16 units into dst, swapped from the file's little-endian order.
void ReadWideText(IKFile* file, uint16_t* dst, uint32_t count) {
    file->Read(dst, count * 2);
    for (uint32_t i = 0; i < count; ++i) {
        const uint8_t* b = reinterpret_cast<const uint8_t*>(dst + i);
        dst[i] = static_cast<uint16_t>(b[0] | (b[1] << 8));
    }
}
}  // namespace

// 0x00037488 CLocManager_Construct (the same stores inlined in CLocManager_Create 0x37b28)
CLocManager::CLocManager() {
    m_vpTexts.m_pBlock = nullptr;
    m_vpTexts.m_ui32NbElt = 10;
    m_vpTexts.m_ui32NbUsedElt = 0;
    m_trcTexts.m_bucketCount = 0x25;
    m_trcTexts.m_count = 0;
    m_trcTexts.m_buckets = new HashTableU32::Node*[0x25];
    std::memset(m_trcTexts.m_buckets, 0, m_trcTexts.m_bucketCount * sizeof(HashTableU32::Node*));
    m_vTrcRecords.m_ui32NbElt = 5;
    m_vTrcRecords.m_pBlock = nullptr;
    m_vTrcRecords.m_ui32NbUsedElt = 0;
    m_pDefaultTrcText = nullptr;
    m_bGameLocalizedDataValid = 0;
    m_languageIndex = 0;
    m_ui16NbLanguage = 0;
    m_wszAllTexts = nullptr;
    m_wszAllTRCTexts = nullptr;
    int32_t language = 1;
    cellSysutilGetSystemParamInt(CELL_SYSUTIL_SYSTEMPARAM_ID_LANG, &language);
    m_systemLanguage = language;
}

// 0x00037b28 CLocManager_Create (the constructor inlined)
IKBaseClass* CLocManager::Create() { return new CLocManager(); }

// 0x00036f28 CLocManager_Delete (CKTrcText.cpp's range): the deleting destructor when not null.
void CLocManager::Delete(IKBaseClass* object) { delete object; }

// 0x00037958 CLocManager_CreateArray (the constructor inlined per element, the array cookie before them)
IKBaseClass* CLocManager::CreateArray(uint32_t count, uint16_t* elementSize) {
    if (elementSize != nullptr) *elementSize = 200;
    return new CLocManager[count];
}

// 0x000373e8 CLocManager_DeleteArray (each element's vt+0x00 from the last, then the cookie block)
void CLocManager::DeleteArray(IKBaseClass* first) { delete[] static_cast<CLocManager*>(first); }

// 0x000389e8 CLocManager_Destructor (0x38860 deleting, 0x38b60 the same): the TRC records' block freed, the hash
// table's nodes released (vt+0x14, empty) and deleted bucket by bucket, its buckets deleted, the texts' block freed.
CLocManager::~CLocManager() {
    if (m_vTrcRecords.m_pBlock != nullptr) Mem_FreeAligned16(m_vTrcRecords.m_pBlock);
    m_vTrcRecords.m_ui32NbUsedElt = 0;
    m_vTrcRecords.m_pBlock = nullptr;
    // The hash table's destructor, inlined (vtable 0xb146c8).
    for (uint32_t bucket = 0; bucket < m_trcTexts.m_bucketCount; ++bucket) {
        while (HashTableU32::Node* node = m_trcTexts.m_buckets[bucket]) {
            m_trcTexts.m_buckets[bucket] = node->m_next;
            m_trcTexts.ReleaseNode(node);  // vt+0x14
            ::operator delete(node);       // OperatorDelete
        }
    }
    m_trcTexts.m_count = 0;
    if (m_trcTexts.m_buckets != nullptr) delete[] m_trcTexts.m_buckets;  // OperatorDeleteArray
    m_trcTexts.m_buckets = nullptr;  // DOTD: ~HashTableU32 runs after this body
    if (m_vpTexts.m_pBlock != nullptr) Mem_FreeAligned16(m_vpTexts.m_pBlock);
    m_vpTexts.m_ui32NbUsedElt = 0;
    m_vpTexts.m_pBlock = nullptr;
}

// 0x00037238 CLocManager_DestroyGame
void CLocManager::DestroyGame() {
    if (m_wszAllTexts != nullptr) {
        Mem_FreeAligned16(m_wszAllTexts);
        m_wszAllTexts = nullptr;
    }
    if (m_wszAllTRCTexts != nullptr) {
        Mem_FreeAligned16(m_wszAllTRCTexts);
        m_wszAllTRCTexts = nullptr;
    }
    if (m_pDefaultTrcText != nullptr) {
        m_pDefaultTrcText->Destroy();                   // vt+0x10
        ClassRegistry_DestroyObject(m_pDefaultTrcText);  // 0x00011420
        m_pDefaultTrcText = nullptr;
    }
    if (m_vTrcRecords.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vTrcRecords.m_pBlock);
        m_vTrcRecords.m_pBlock = nullptr;
    }
    m_vTrcRecords.m_ui32NbUsedElt = 0;
    m_vTrcRecords.m_pBlock = nullptr;
}

// 0x00036fc8 CLocManager_GetSystemLanguageIndex_maybe
uint32_t CLocManager::GetSystemLanguageIndex() {
    for (uint32_t i = m_ui16NbLanguage; i != 0;) {
        --i;
        if (m_systemLanguage == m_ai32SystemLanguage[i]) return i;
    }
    return m_defaultLanguageIndex;
}

// 0x00037028 CLocManager_GetText
CKLocText* CLocManager::GetText(uint32_t id) {
    for (HashTableU32::Node* node = m_trcTexts.m_buckets[m_trcTexts.HashKey(id)]; node != nullptr; node = node->m_next) {
        if (m_trcTexts.KeysEqual(id, node->m_key) != 0) return node->m_value;
    }
    return m_pDefaultTrcText;
}

namespace {
// Local copy of 0x000107d8 Str_HashXor4 (misc/Wcs.cpp, not ported yet; CKInput.cpp and
// SoundEmitterArray.cpp keep the same copy): the bytes XORed into four accumulators, a little-endian word.
uint32_t LocStr_HashXor4(const char* s) {
    uint8_t acc[4] = {0, 0, 0, 0};
    for (uint32_t i = 0; s[i] != 0; ++i) acc[i & 3] ^= static_cast<uint8_t>(s[i]);
    return static_cast<uint32_t>(acc[0]) | (static_cast<uint32_t>(acc[1]) << 8) | (static_cast<uint32_t>(acc[2]) << 16) |
           (static_cast<uint32_t>(acc[3]) << 24);
}
}  // namespace

// 0x00037328 CLocManager_FindTextVariable_maybe
int32_t CLocManager::FindTextVariable(const char* name) {
    if (name == nullptr) return -1;
    const uint32_t hash = LocStr_HashXor4(name);
    for (uint32_t i = 0; i < m_vTrcRecords.m_ui32NbUsedElt; ++i) {
        if (m_vTrcRecords.m_pBlock[i].m_unk4 == hash) return static_cast<int32_t>(i);
    }
    return -1;
}

// 0x00037578 CLocManager_GetTextVariable
uint32_t CLocManager::GetTextVariable(uint32_t index) {
    if (index >= m_vTrcRecords.m_ui32NbUsedElt) return 0;
    return m_vTrcRecords.m_pBlock[index].m_unk8;
}

// 0x000375b0 CLocManager_SetTextVariable
uint8_t CLocManager::SetTextVariable(uint32_t index, uint32_t value) {
    if (index >= m_vTrcRecords.m_ui32NbUsedElt) return 0;
    if (m_vTrcRecords.m_pBlock[index].m_unk8 != value) m_vTrcRecords.m_pBlock[index].m_unk8 = value;
    return 1;
}

// 0x000375f8 CLocManager_SetTextVariableValueByName_maybe
uint8_t CLocManager::SetTextVariableValueByName(const char* name, int32_t value) {
    if (name == nullptr) return 0;
    const uint32_t hash = LocStr_HashXor4(name);
    for (uint32_t i = 0; i < m_vTrcRecords.m_ui32NbUsedElt; ++i) {
        STrcRecord& record = m_vTrcRecords.m_pBlock[i];
        if (record.m_unk4 != hash) continue;
        if (static_cast<int32_t>(record.m_unk0) == value) return 1;
        record.m_unk0 = static_cast<uint32_t>(value);
        g_pEngine->m_manager2d->PostEvent(5, nullptr);
        return 1;
    }
    return 0;
}

// 0x000376f8 CLocManager_GetTextVariableValue_maybe
int32_t CLocManager::GetTextVariableValue(uint32_t index) {
    if (index >= m_vTrcRecords.m_ui32NbUsedElt) return 0;
    return static_cast<int32_t>(m_vTrcRecords.m_pBlock[index].m_unk0);
}

// 0x00037730 CLocManager_SetTextVariableValue_maybe
uint8_t CLocManager::SetTextVariableValue(uint32_t index, int32_t value) {
    if (index >= m_vTrcRecords.m_ui32NbUsedElt) return 0;
    STrcRecord& record = m_vTrcRecords.m_pBlock[index];
    if (static_cast<int32_t>(record.m_unk0) != value) {
        record.m_unk0 = static_cast<uint32_t>(value);
        g_pEngine->m_manager2d->PostEvent(5, nullptr);
    }
    return 1;
}

// 0x000377c0 CLocManager_GetVoiceLanguageIndex_maybe
uint32_t CLocManager::GetVoiceLanguageIndex() {
    const uint16_t language = m_languageIndex;
    const uint32_t voice = static_cast<uint32_t>(m_ai32TextId[language]);
    if (voice == 0xffffffffu || static_cast<int32_t>(m_ui16NbLanguage) <= static_cast<int32_t>(voice)) return language;
    return voice;
}

// 0x000378e8 CLocManager_UnloadLocalizedData
void CLocManager::UnloadLocalizedData() {
    m_bGameLocalizedDataValid = 0;
    if (m_wszAllTexts != nullptr) {
        Mem_FreeAligned16(m_wszAllTexts);
        m_wszAllTexts = nullptr;
    }
    if (m_wszAllTRCTexts != nullptr) {
        Mem_FreeAligned16(m_wszAllTRCTexts);
        m_wszAllTRCTexts = nullptr;
    }
}

// 0x00037c20 CLocManager_Load
int32_t CLocManager::Load(IKFile* file, int32_t type) {
    if (type == 1) {
        // The TRC records.
        uint32_t count = 0;
        ReadU32LE(file, &count);
        LocVector_Allocate(&m_vTrcRecords, count);
        for (uint32_t i = 0; i < count; ++i) {
            STrcRecord* record = &m_vTrcRecords.m_pBlock[i];
            ReadU32LE(file, &record->m_unk0);
            ReadU32LE(file, &record->m_unk4);
            ReadU32LE(file, &record->m_unk8);
        }
        // The text objects.
        ReadU32LE(file, &count);
        LocVector_Allocate(&m_vpTexts, count);
        for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &m_vpTexts.m_pBlock[i]);
        // The default TRC text.
        m_pDefaultTrcText = static_cast<CKTrcText*>(ClassRegistry_CreateObjectByKey(0x684c));
        m_pDefaultTrcText->InitializeGameData();
        m_pDefaultTrcText->InitializeLevelData();
        // The TRC texts by id; a known id gets the new text.
        ReadU32LE(file, &count);
        if (count == 0) return 1;
        for (uint32_t i = 0; i < count; ++i) {
            uint32_t id = 0;
            ReadU32LE(file, &id);
            CKLocText* text = nullptr;
            IKFile_ReadRef(file, &text);
            HashTableU32::Node** bucket = &m_trcTexts.m_buckets[m_trcTexts.HashKey(id)];
            HashTableU32::Node* node = *bucket;
            while (node != nullptr && m_trcTexts.KeysEqual(id, node->m_key) == 0) node = node->m_next;
            if (node != nullptr) {
                m_trcTexts.ReleaseNode(node);
                m_trcTexts.InitNode(node, id, text);
                continue;
            }
            node = new HashTableU32::Node();
            m_trcTexts.InitNode(node, id, text);
            node->m_next = *bucket;
            *bucket = node;
            ++m_trcTexts.m_count;
        }
        return 1;
    }
    if (type == 3) {
        // The language table.
        ReadU16LE(file, &m_ui16NbLanguage);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_ai32SystemLanguage), m_ui16NbLanguage);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_ai32TextId), m_ui16NbLanguage);
        ReadU32LE(file, &m_defaultLanguageIndex);
        // The texts: one block (its first unit is left as it is), each text's string in turn.
        uint32_t total = 0;
        ReadU32LE(file, &total);
        m_wszAllTexts = static_cast<uint16_t*>(Mem_AllocAligned16((total + 1) * 2));
        const uint32_t texts = m_vpTexts.m_ui32NbUsedElt;
        uint16_t* cursor = m_wszAllTexts + 1;
        for (uint32_t i = 0; i != texts; ++i) {
            Thread_YieldDuringLoad(1);
            CKLocText* text = m_vpTexts.m_pBlock[i];
            uint32_t length = 0;
            ReadU32LE(file, &length);
            if (length == 0) {
                text->m_pText = nullptr;
                continue;
            }
            ReadWideText(file, cursor, length);
            text->m_pText = cursor;
            cursor += length;
        }
        // The TRC texts: the default string first, then each id's string (an empty one keeps the default).
        ReadU32LE(file, &total);
        const uint32_t defaultLength = Wcs_Length(kNoTrcDefined);
        uint16_t* block = static_cast<uint16_t*>(Mem_AllocAligned16((defaultLength + 1 + total) * 2));
        m_wszAllTRCTexts = block;
        WStr_CopyReturnEnd(block, kNoTrcDefined);
        m_pDefaultTrcText->m_pText = block;
        const uint32_t trcTexts = m_trcTexts.m_count;
        if (trcTexts != 0) {
            cursor = m_wszAllTRCTexts + (defaultLength + 1);
            CKLocText* target = nullptr;  // BUG(original): an unknown id keeps the previous text (r16)
            for (uint32_t i = 0; i != trcTexts; ++i) {
                Thread_YieldDuringLoad(1);
                uint32_t id = 0;
                ReadU32LE(file, &id);
                for (HashTableU32::Node* node = m_trcTexts.m_buckets[m_trcTexts.HashKey(id)]; node != nullptr;
                     node = node->m_next) {
                    if (m_trcTexts.KeysEqual(id, node->m_key) != 0) {
                        target = node->m_value;
                        break;
                    }
                }
                uint32_t length = 0;
                ReadU32LE(file, &length);
                if (length == 0) {
                    target->m_pText = block;
                    continue;
                }
                ReadWideText(file, cursor, length);
                target->m_pText = cursor;
                cursor += length;
            }
        }
        m_bGameLocalizedDataValid = 1;
    }
    return 1;
}
