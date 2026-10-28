// CKSrvShadow.h - the blob-shadow service (key 0x301, vtable 0xb1ecb8, size 0x6c). Original unit:
// CKSrvShadow.cpp (0x1fa938-0x1fe788). XXL2: K/KServices/KServiceShadow/CKSrvShadow.h: the same
// members in the same order, read the same way; DotD adds +0x0c..+0x15, the +0x30 vector and +0x68.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/IKService.h"
#include "k2000/util/TVector.h"

// The ground a shadow is cast on (XXL2 CKShadowGround). Only the in-use byte is known.
struct CKShadowGround {
    uint8_t m_unk00[0x1d];
    uint8_t m_bUsed_maybe;  // +0x1d CKSrvShadow_Stop clears it
};
DOTD_ASSERT_OFFSET(CKShadowGround, m_bUsed_maybe, 0x1d);

// XXL2 CKShadowSpot (an IKShadow): one shadow quad, 0x8c bytes on the PS3, vtable 0xb1ede0 (Ghidra:
// ShadowProjector_*). The service creates them with new[] in its Load.
class CKShadowSpot {
public:
    CKShadowSpot();  // inlined in CKSrvShadow_Load
    virtual ~CKShadowSpot() {}           // +0x00 / +0x04 0x9b1230 / 0x9b1240
    virtual void Destroy() {}            // +0x08 0x1fee10 (empty)
    // +0x0c 0x1fee38 CKShadowSpot_SetData_maybe (render/ShadowProjector.cpp): the spot's data from a shadow
    // component, the shadowed leaf and the ground. The shadow texture is bound to the spot node's
    // material, which is rendering state.
    virtual void SetData(IKSerializable* shadowCpnt, IKSerializable* leaf, void* ground);
    virtual void Update() {}             // +0x10 0x1ff2c0  STUB(C1.6) (arguments unverified)
    // +0x14 0x1fee18 CKShadowSpot_SetShadowHided_maybe: with `hided` 0 the spot loses its flag byte (+0x1b) and
    // its word at +0x2c (the CKSrvShadow_Stop call passes 1: nothing happens).
    virtual void SetShadowHided(int32_t hided) {
        if (hided != 0) return;
        m_cColor[3] = 0;
        m_afColor[3] = 0.0f;
    }

    CKShadowSpot* m_pNext;               // +0x04 IKShadow's CSBaseNode
    IKSerializable* m_pShadowCpnt;       // +0x08 CKShadowCpnt
    IKSerializable* m_pLeaf;             // +0x0c SetData's second argument (the shadowed CSGLeaf)
    void* m_pGround;                     // +0x10 SetData's third argument (the CKShadowGround)
    uint32_t m_unk14;                    // +0x14 the component's +0x1c word
    uint8_t m_cColor[4];                 // +0x18 the same word as bytes
    float m_fUnk1c;                      // +0x1c the component's +0x20 float
    float m_afColor[4];                  // +0x20 the colour bytes as floats
    CVector3 m_v30;                      // +0x30 (0, 1, 0)
    CVector3 m_v3c;                      // +0x3c (0, 1, 0)
    float m_fUnk48;                      // +0x48 the component's +0x24 float
    uint32_t m_unk4c;                    // +0x4c not set by the constructor
    float m_fUnk50;                      // +0x50 SetData: 0.2f
    uint32_t m_unk54;                    // +0x54 SetData: 0
    uint32_t m_unk58;                    // +0x58 the constructor sets 1
    uint32_t m_unk5c;                    // +0x5c the constructor sets 8
    uint32_t m_unk60;                    // +0x60 the constructor sets 0
    int32_t m_unk64;                     // +0x64 the constructor sets -1
    uint32_t m_unk68[3];                 // +0x68 not set by the constructor
    uint32_t m_unk74;                    // +0x74 the constructor sets 3
    uint32_t m_unk78[4];                 // +0x78 not set by the constructor
    uint8_t m_unk88;                     // +0x88 the constructor sets 0
    uint8_t m_pad89[3];                  // +0x89
};
DOTD_ASSERT_SIZE(CKShadowSpot, 0x8c);
DOTD_ASSERT_OFFSET(CKShadowSpot, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKShadowSpot, m_unk74, 0x74);
DOTD_ASSERT_OFFSET(CKShadowSpot, m_unk88, 0x88);

class CKSrvShadow : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0xc)
    DOTD_DECLARE_FACTORIES(CKSrvShadow)

    // XXL2 CKShadowDataSpot (a CSBaseNode): 0x14 bytes on the PS3.
    // new[] (an array cookie, as the original's OperatorNewArray(n * 0x14 + 4)); the CSBaseNode
    // constructor clears m_pNext.
    struct CKShadowDataSpot {
        CKShadowDataSpot() : m_pNext(nullptr) {}
        ~CKShadowDataSpot() {}

        CKShadowDataSpot* m_pNext;       // +0x00 the free list m_lShadowUnused
        CKShadowSpot* m_pShadow;         // +0x04 its spot (XXL2 IKShadow*)
        IKSerializable* m_pShadowCpnt;   // +0x08 CKShadowCpnt
        void* m_pShadowedLeaf;           // +0x0c CSGLeaf
        CKShadowGround* m_pShadowGround; // +0x10 CKShadowGround
    };
    // XXL2 CKShadowDataWaiting (a CSBaseNode): 0x10 bytes on the PS3.
    // new[] (an array cookie, as the original's OperatorNewArray(n * 0x10 + 4)); the CSBaseNode
    // constructor clears m_pNext.
    struct CKShadowDataWaiting {
        CKShadowDataWaiting() : m_pNext(nullptr) {}
        ~CKShadowDataWaiting() {}

        CKShadowDataWaiting* m_pNext;    // +0x00 the free list m_lShadowWaitingUnused
        IKSerializable* m_pShadowCpnt;   // +0x04 CKShadowCpnt
        void* m_pShadowedLeaf;           // +0x08 CSGLeaf
        CKShadowGround* m_pShadowGround; // +0x0c CKShadowGround
    };
    // XXL2 CTexCoord.
    struct CTexCoord {
        float m_fU;  // +0x00
        float m_fV;  // +0x04
    };
    // DotD's +0x30 vector element, 0x2c bytes on the PS3; names ours.
    struct Entry {
        void* m_unk00;              // +0x00 Load clears it; PostLoad sets a material texture
        CVector3 m_unk04;           // +0x04 read in one 12-byte read
        uint32_t m_unk10;           // +0x10 read third
        uint32_t m_unk14;           // +0x14 read fourth
        uint32_t m_unk18;           // +0x18 read first
        uint32_t m_unk1c;           // +0x1c read second
        uint32_t m_unk20;           // +0x20 read fifth
        uint8_t m_unk24;            // +0x24 read: the entry is present
        uint8_t m_pad25[3];         // +0x25
        IKSerializable* m_unk28;    // +0x28 a reference
    };

    CKSrvShadow();  // inlined in 0x001fbe98 CKSrvShadow_Create
    ~CKSrvShadow() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001fc060 CKSrvShadow_Load
    // 0x001faa60 CKSrvShadow_MarkCasterGeometryRecursive_maybe: every geometry of a node (class key 0xcb) whose
    // material type (properties bits 3-6) is not 7, 8 or 9 gets its render flags' low six bits set to 0x2b; with
    // `recurse`, the same for the children of a scene-graph branch (key 0x24b), recursively.
    void MarkCasterGeometry(IKSerializable* node, int32_t recurse);
    // 0x001fb6f8 CKSrvShadow_RegisterCaster: a caster whose ground is not marked used yet (or any, with `force`)
    // gets a shadow spot from the free list (`spot` reuses one), else a waiting slot; both go to the high or low
    // priority list of the caster's component. The ground's used byte is set.
    void RegisterCaster(IKSerializable* shadowCpnt, IKSerializable* node, CKShadowGround* ground, int32_t force,
                        CKShadowDataSpot* spot, uint8_t recurse);
    // 0x001fd6f0 CKSrvShadow_UnregisterCaster: the ground's spot (or waiting slot) goes back to the free lists, and a waiting
    // caster that is near takes the spot over (CKSrvShadow.cpp).
    void UnregisterCaster(CKShadowGround* ground, IKSerializable* shadowCpnt);
    // ---- the per-sector shadow textures (C2.4 step 7). Entry `sector` (when present, m_unk24) gives the baked shadow of that
    // sector: a texture (the material texture of the entry's node: m_unk28 -> its first geometry's material), the shadow's
    // extent / height range (+0x10, +0x14, +0x20), its scale (+0x18, +0x1c) and origin (+0x04). Out of range or absent
    // entries answer zero. The shaders sample the texture of the current sector on unit 5 (externShadowEnable).
    uint32_t EntryHasTexture(uint32_t index) const;      // 0x001faa00 CKSrvShadow_EntryHasTexture_maybe
    float GetEntryFloat10(uint32_t index) const;         // 0x001fb060
    float GetEntryFloat14(uint32_t index) const;         // 0x001fb028
    float GetEntryFloat18(uint32_t index) const;         // 0x001faff0
    float GetEntryFloat1C(uint32_t index) const;         // 0x001fafb8
    const float* GetEntryOrigin(uint32_t index) const;   // 0x001fb098 (the null vector 0x00c50d64 without a texture)
    // 0x001fb3b8 CKSrvShadow_GetEntryTexture_maybe: the entry's texture, taken from its node when not known yet.
    void* GetEntryTexture(uint32_t index);
    // 0x001fb468 CKSrvShadow_RefreshEntryTextures_maybe: every present entry's texture taken from its node again.
    void RefreshEntryTextures();
    // 0x001fb9e0 CKSrvShadow_UpdateActiveSectorShadowTexture_maybe (RenderGameFrame, when the level's sector changed): the current sector's texture
    // (clamp / clamp addressing) bound on texture unit 5, or unit 5 cleared; m_unk10 remembers the sector.
    void UpdateActiveSectorWorld();
    // 0x001fb988 CKSrvShadow_IsShadowModeEnabled_maybe: bit `mode` (0-2) of the word at +0x68.
    uint32_t IsShadowModeEnabled(int32_t mode) const;
    // vt+0x30 0x001fb2d0 CKSrvShadow_PostLoad: the entries' textures (when the shadow service is active, +0x15), no spots in use,
    // the bound sector 99, the current sector 0.
    int32_t PostLoad(int32_t type) override;
    void RefreshEntryTexturesOfPresent();  // PostLoad's loop (inlined there)
    void Start() override {}                            // vt+0x50 0x1faf00  STUB(C1.6)
    void Stop() override;                               // vt+0x68 0x1fcc58 CKSrvShadow_Stop
    void Pause() override {}                            // vt+0x70 0x1faa50  STUB(C1.6)
    void Resume() override {}                           // vt+0x78 0x1faa58  STUB(C1.6)
    void Update(IKTime*) override {}                    // vt+0x7c 0x1fdd68 UpdateCKSrvShadow  STUB(C1.6)
    // vt+0x94 0x1faed8 CKSrvShadow_InitializeService: Engine_SetShadowService(this), returns 1.
    int32_t InitializeService() override;
    // vt+0x98 0x1faeb0 CKSrvShadow_DestroyService: Engine_SetShadowService(null).
    void DestroyService() override;

    uint32_t m_unk0c;                            // +0x0c read
    uint32_t m_unk10;                            // +0x10 read; PostLoad sets 99
    uint8_t m_unk14;                             // +0x14 read
    uint8_t m_unk15;                             // +0x15 read: the +0x30 vector follows
    uint8_t m_pad16[2];                          // +0x16 never written (heap residue on the live dump)
    uint32_t m_ui32NbShadowSpot;                 // +0x18
    uint32_t m_ui32NbShadowSpotWaiting;          // +0x1c
    IKSerializable* m_pShadowSpotNode;           // +0x20 CNode
    IKSerializable* m_pShadowParticuleGeometry;  // +0x24 CParticleGeometry (XXL2 spelling)
    void* m_pShadowTexture;                      // +0x28 CTexture (IKFile_ReadTextureRef, one reference kept)
    CTexCoord* m_aTextureCoord;                  // +0x2c two per shadow in the texture (OperatorNewArray)
    TVector<Entry, 1> m_unk30;                   // +0x30
    CKShadowSpot* m_aShadowSpot;                 // +0x3c new CKShadowSpot[m_ui32NbShadowSpot]
    CKShadowDataSpot* m_aShadowDataSpot;         // +0x40 one per spot
    CKShadowDataSpot* m_lShadowUnused;           // +0x44 every data spot, last first
    CKShadowDataSpot* m_lDrawingShadowHighPriority;  // +0x48
    CKShadowDataSpot* m_lDrawingShadowLowPriority;   // +0x4c
    CKShadowDataWaiting* m_aShadowWaiting;       // +0x50 one per waiting slot
    CKShadowDataWaiting* m_lShadowWaitingUnused; // +0x54 every waiting slot, last first
    CKShadowDataWaiting* m_lShadowWaitingHighPriority;  // +0x58
    CKShadowDataWaiting* m_lShadowWaitingLowPriority;   // +0x5c
    uint8_t m_ui8ShadowSpotUsed;                 // +0x60 PostLoad sets 0
    uint8_t m_ui8NbShadowsInTextureShadow;       // +0x61
    uint8_t m_ui8TextureShadowWidth;             // +0x62
    uint8_t m_ui8TextureShadowHeight;            // +0x63
    float m_fOffsetShadow;                       // +0x64
    int32_t m_unk68;                             // +0x68 read (LVL000: -1)
};
DOTD_ASSERT_SIZE(CKSrvShadow::CKShadowDataSpot, 0x14);
DOTD_ASSERT_SIZE(CKSrvShadow::CKShadowDataWaiting, 0x10);
DOTD_ASSERT_SIZE(CKSrvShadow::Entry, 0x2c);
DOTD_ASSERT_SIZE(CKSrvShadow, 0x6c);
DOTD_ASSERT_OFFSET(CKSrvShadow, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(CKSrvShadow, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKSrvShadow, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKSrvShadow, m_unk15, 0x15);
DOTD_ASSERT_OFFSET(CKSrvShadow, m_ui32NbShadowSpot, 0x18);
DOTD_ASSERT_OFFSET(CKSrvShadow, m_pShadowSpotNode, 0x20);
DOTD_ASSERT_OFFSET(CKSrvShadow, m_pShadowTexture, 0x28);
DOTD_ASSERT_OFFSET(CKSrvShadow, m_aTextureCoord, 0x2c);
DOTD_ASSERT_OFFSET(CKSrvShadow, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKSrvShadow, m_aShadowSpot, 0x3c);
DOTD_ASSERT_OFFSET(CKSrvShadow, m_lShadowUnused, 0x44);
DOTD_ASSERT_OFFSET(CKSrvShadow, m_aShadowWaiting, 0x50);
DOTD_ASSERT_OFFSET(CKSrvShadow, m_lShadowWaitingUnused, 0x54);
DOTD_ASSERT_OFFSET(CKSrvShadow, m_ui8ShadowSpotUsed, 0x60);
DOTD_ASSERT_OFFSET(CKSrvShadow, m_fOffsetShadow, 0x64);
DOTD_ASSERT_OFFSET(CKSrvShadow, m_unk68, 0x68);

// 0x00cea928 (XXL2 g_pSrvShadow): the constructor stores the service here.
extern CKSrvShadow* g_pSrvShadow;
