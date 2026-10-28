// CKExplosionFxData.h - an explosion effect: shockwave values, sound, pad vibration, camera quake, and a
// list of parts created by type (key 0x1a8c, vtable 0xb1c988, size 0x3c). Original unit:
// CKExplosionFxData.cpp (0x1b3510-0x1b5d98); Create and CreateArray are in CKMeshPopFxData.cpp,
// DeleteArray in CKFlashFxData.cpp. XXL2: KServiceFx/Effects/CKExplosionFxData.h; its m_pSoundDico and
// m_pVibrationPadData are read one after the other like +0x1c/+0x24 here. XXL2 reads seven values before
// them and DotD four, so the four floats keep our names (XXL2's first four are m_fWaveFinalRadiusPrec,
// m_fWaveGrowth, m_fAngleProj, m_fWaveRadius, _maybe the same).
//
// The parts (XXL-Editor's efdParts) are small polymorphic objects with no names in either game. Their
// common base has vtable 0xb1c9f0 (destructors and an empty +0x08); CreatePart (0x1b3510) makes them by
// type: 0 and 1 have their own classes, 2..8 share one that holds an object reference (XXL-Editor, for
// Asterix at the Olympic Games: 2 shockwave, 3 spark, 4 flash FX data), and 9 and above get null.
#pragma once
#include <cstdint>

#include "k2000/components/CKQuakeCameraLauncher.h"
#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/managers/CKVibrationData.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/util/TVector.h"

class CKExplosionFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x6a)
    DOTD_DECLARE_FACTORIES(CKExplosionFxData)

    // vtable 0xb1c9f0 (names ours). +0x08 is read last by Load for every part.
    struct Part {
        virtual ~Part() {}   // +0x00 / +0x04 0x9aba98 / 0x9aba68
        virtual void Vf08() {}  // +0x08 0x9aba18
        uint32_t m_type;     // +0x04
        float m_unk08;       // +0x08 (type 0 stores 0.0f, the others integer 0)
    };
    // Type 0, vtable 0xb1ca08, 0x70 bytes.
    struct PartType0 : Part {
        PartType0();         // inlined in CreatePart
        uint32_t m_unk0c;    // +0x0c
        uint32_t m_unk10;    // +0x10
        CVector3 m_unk14;    // +0x14 (1, 1, 1)
        CVector3 m_unk20;    // +0x20
        CVector3 m_unk2c;    // +0x2c
        CVector3 m_unk38;    // +0x38
        float m_unk44;       // +0x44 5.0
        float m_unk48;       // +0x48 1.0
        float m_unk4c;       // +0x4c 1.0
        float m_unk50;       // +0x50 1.0
        float m_unk54;       // +0x54
        float m_unk58;       // +0x58
        float m_unk5c;       // +0x5c 1.0
        float m_unk60;       // +0x60 1.0
        float m_unk64;       // +0x64
        float m_unk68;       // +0x68
        uint32_t m_unk6c;    // +0x6c 0x1ff; not read
    };
    // Type 1, vtable 0xb1ca20, 0x40 bytes.
    struct PartType1 : Part {
        PartType1();         // inlined in CreatePart
        IKSerializable* m_pObject;  // +0x0c
        uint32_t m_unk10;    // +0x10
        float m_unk14;       // +0x14 5.0
        float m_unk18;       // +0x18 1.0
        CVector3 m_unk1c;    // +0x1c the constant at 0xc50d40, (0, 1, 0)
        CVector3 m_unk28;    // +0x28 the constant at 0xc50d64, (0, 0, 0)
        CVector3 m_unk34;    // +0x34 the constant at 0xc50d64
    };
    // Types 2..8, vtable 0xb1c970 (its +0x08 is 0x1b3508, also empty), 0x10 bytes.
    struct PartObject : Part {
        explicit PartObject(uint32_t type);  // inlined in CreatePart
        IKSerializable* m_pObject;  // +0x0c an FX data (XXL-Editor)
    };

    CKExplosionFxData();  // 0x001ae948 CKExplosionFxData_Create (the constructor is inlined there)

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001b4328 CKExplosionFxData_Load
    // vt+0x30 PostLoad 0x1b36f0 (stays the default in C1.3): counts the sound dictionary's loaded sounds
    // into +0x20.
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x1a4c; }  // vt+0x54 0x1b3500

    // 0x001b3510 CKExplosionFxData_CreateElementByType_maybe
    Part* CreatePart(uint32_t type);

    float m_unk08;                          // +0x08
    float m_unk0c;                          // +0x0c
    float m_unk10;                          // +0x10
    float m_unk14;                          // +0x14
    uint8_t m_unk18;                        // +0x18
    uint8_t m_pad19[3];
    IKSerializable* m_pSoundDico;           // +0x1c CKSoundDictionaryID
    uint32_t m_unk20;                       // +0x20 PostLoad: the number of loaded sounds
    CKVibrationData* m_pVibrationPadData;   // +0x24
    CKQuakeCameraLauncher* m_pQuakeLauncher;  // +0x28 (Ghidra draft: CKQuakeCameraLauncher*)
    TVector<Part*, 10> m_parts;             // +0x2c the constructor: null, 10, 0
    uint8_t m_unk38[4];                     // +0x38 read without a swap: the file's bytes
};
DOTD_ASSERT_SIZE(CKExplosionFxData::Part, 0xc);
DOTD_ASSERT_SIZE(CKExplosionFxData::PartType0, 0x70);
DOTD_ASSERT_SIZE(CKExplosionFxData::PartType1, 0x40);
DOTD_ASSERT_SIZE(CKExplosionFxData::PartObject, 0x10);
DOTD_ASSERT_OFFSET(CKExplosionFxData::PartType0, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKExplosionFxData::PartType0, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKExplosionFxData::PartType0, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKExplosionFxData::PartType0, m_unk6c, 0x6c);
DOTD_ASSERT_OFFSET(CKExplosionFxData::PartType1, m_pObject, 0x0c);
DOTD_ASSERT_OFFSET(CKExplosionFxData::PartType1, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKExplosionFxData::PartType1, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKExplosionFxData::PartObject, m_pObject, 0x0c);
DOTD_ASSERT_SIZE(CKExplosionFxData, 0x3c);
DOTD_ASSERT_OFFSET(CKExplosionFxData, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKExplosionFxData, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKExplosionFxData, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKExplosionFxData, m_pSoundDico, 0x1c);
DOTD_ASSERT_OFFSET(CKExplosionFxData, m_pVibrationPadData, 0x24);
DOTD_ASSERT_OFFSET(CKExplosionFxData, m_pQuakeLauncher, 0x28);
DOTD_ASSERT_OFFSET(CKExplosionFxData, m_parts, 0x2c);
DOTD_ASSERT_OFFSET(CKExplosionFxData, m_unk38, 0x38);
