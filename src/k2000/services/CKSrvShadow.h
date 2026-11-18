// CKSrvShadow.h - the blob-shadow service (key 0x301, vtable 0xb1ecb8, size 0x6c). Original unit:
// CKSrvShadow.cpp (0x1fa938-0x1fe788). XXL2: K/KServices/KServiceShadow/CKSrvShadow.h: the same
// members in the same order, read the same way; DotD adds +0x0c..+0x15, the +0x30 vector and +0x68.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/IKService.h"
#include "k2000/util/TVector.h"

class IKTime;

// The ground a shadow is cast on (XXL2 CKShadowGround), embedded in the casters (IKHkEnemy +0x190, CKHkMovableCharacter
// +0xd4). CKShadowSpot_Update fills it from its ground probe.
struct CKShadowGround {
    CVector3 m_v3Position;  // +0x00 the shadow's point on the ground (the probe's start)
    CVector3 m_v3Normal;    // +0x0c the ground's normal there
    float m_fUnk18;         // +0x18 the height above the ground (the contact's m_fdH); the shadow shrinks above 0.05
    // +0x1c bit 0 probe the ground, 1 keep the normal, 2 keep +0x18, 3 probe from the leaf's position, 4 no shadow
    uint8_t m_ui8Flags;
    uint8_t m_bUsed_maybe;  // +0x1d CKSrvShadow_Stop clears it
};
DOTD_ASSERT_OFFSET(CKShadowGround, m_fUnk18, 0x18);
DOTD_ASSERT_OFFSET(CKShadowGround, m_ui8Flags, 0x1c);
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
    // +0x10 0x001ff2c0 ShadowProjector_Update (UpdateCKSrvShadow): the spot's quad for this frame into the shadow
    // PTank's arrays (`matrix`, `uv` four floats, `color` four bytes): the ground probed (ground flag 0), the quad laid
    // on the ground's normal (smoothed with +0x2b), lifted towards the camera, scaled by the component (and its height),
    // the alpha faded with the distance, the normal and the colour smoothed. 1 when the spot is not drawn (no shadow,
    // not drawn this frame, no ground, a ground the game manager refuses, too far), 0 when it wrote the arrays.
    virtual int32_t Update(IKTime* clock, CMatrix34* matrix, float* uv, uint8_t* color);
    // +0x14 0x1fee18 CKShadowSpot_SetShadowHided_maybe: with `hided` 0 the spot loses its flag byte (+0x1b) and
    // its word at +0x2c (the CKSrvShadow_Stop call passes 1: nothing happens).
    virtual void SetShadowHided(int32_t hided) {
        if (hided != 0) return;
        m_cColor[3] = 0;
        m_afColor[3] = 0.0f;
    }

    // 0x001feff0 ShadowProjector_BuildGroundAlignedMatrix_maybe (the spot is not read): `matrix`'s basis with `at` (the
    // ground normal) as its at axis and the leaf's modelling at axis as its up hint, or its modelling up when the at
    // axis is (nearly) parallel to the normal; a modelling matrix not flagged normalised has the hint normalised first.
    void BuildGroundAlignedMatrix(CMatrix34* matrix, IKSerializable* leaf, const CVector3* at);

    CKShadowSpot* m_pNext;               // +0x04 IKShadow's CSBaseNode
    IKSerializable* m_pShadowCpnt;       // +0x08 CKShadowCpnt
    IKSerializable* m_pLeaf;             // +0x0c SetData's second argument (the shadowed CSGLeaf)
    void* m_pGround;                     // +0x10 SetData's third argument (the CKShadowGround)
    uint8_t m_cTargetColor[4];           // +0x14 the colour the spot fades to: the component's (its alpha faded)
    uint8_t m_cColor[4];                 // +0x18 the colour drawn (RGBA bytes)
    float m_fUnk1c;                      // +0x1c the component's colour smoothing speed (+0x20)
    float m_afColor[4];                  // +0x20 the colour drawn as floats
    CVector3 m_v30;                      // +0x30 the ground normal the spot turns to (0, 1, 0)
    CVector3 m_v3c;                      // +0x3c the smoothed normal (0, 1, 0)
    float m_fUnk48;                      // +0x48 the component's normal smoothing speed (+0x24)
    uint8_t m_bDrawn;                    // +0x4c the spot was drawn (UpdateCKSrvShadow); not set by the constructor
    uint8_t m_pad4d[3];
    CGroundContactDatasIn m_groundIn;    // +0x50 the ground probe's settings: SetData 0.2, 0; masks 1, 8
    CGroundContactDatasInOut m_groundContact;  // +0x60 the ground probe's result
};
DOTD_ASSERT_SIZE(CKShadowSpot, 0x8c);
DOTD_ASSERT_OFFSET(CKShadowSpot, m_cTargetColor, 0x14);
DOTD_ASSERT_OFFSET(CKShadowSpot, m_bDrawn, 0x4c);
DOTD_ASSERT_OFFSET(CKShadowSpot, m_groundIn, 0x50);
DOTD_ASSERT_OFFSET(CKShadowSpot, m_groundContact, 0x60);

class CKSrvShadow : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0xc)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b10f8
        return key == 0x301 || key == 0x1 || key == 0x3fe || key == 0xc;
    }
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
    ~CKSrvShadow() override;  // 0x001fe668 CKSrvShadow_Destructor

    void Destroy() override;  // vt+0x10 0x001fd068 CKSrvShadow_Destroy

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
    // vt+0x88 0x001fb660 CKSrvShadow_SectorLoaded: with the sector textures (+0x15) the loaded sector's present entry
    // takes its node's material texture again (null without a geometry).
    void SectorLoaded(int32_t sector) override;
    // vt+0x50 0x001faf00 CKSrvShadow_Start: the spot node's frame back to the identity; with the sector textures (+0x15)
    // every present entry's node hidden (its scene-graph property bit 2).
    void Start() override;
    void Stop() override;                               // vt+0x68 0x1fcc58 CKSrvShadow_Stop
    void Pause() override {}                            // vt+0x70 0x1faa50 CKSrvShadow_Pause (empty)
    void Resume() override {}                           // vt+0x78 0x1faa58 CKSrvShadow_Resume (empty)
    // vt+0x7c 0x001fdd68 UpdateCKSrvShadow: while the clock runs: the shadow PTank's matrix, tex-coord and colour arrays
    // locked; near high-priority waiting casters take the spots of low-priority ones (demoted); near waiting casters
    // (high, then low) registered on free spots; every drawn spot updated (Update vt+0x10) into the next array slots, at
    // most m_ui32NbShadowSpot (the rest queued as waiting again), the ones that stop drawing demoted, the ones that ask
    // unregistered; the PTank's particle count set and unlocked; the spot node hidden without any.
    void Update(IKTime* clock) override;
    // 0x001facc8 ShadowAtlas_GetUVMin_maybe / 0x001face0 ShadowAtlas_GetUVMax_maybe: shadow `index`'s corners in the
    // shadow texture (its two texture coordinates).
    const CTexCoord* GetUVMin(uint8_t index) const { return &m_aTextureCoord[index * 2u]; }
    const CTexCoord* GetUVMax(uint8_t index) const { return &m_aTextureCoord[index * 2u + 1u]; }
    // 0x001fbb38 CKSrvShadow_DemoteCasterToPending: the drawn spot of `leaf` in the list of the component's priority
    // (0 high, 1 low) hidden, unlinked and given back, its caster queued at the head of that priority's waiting list (when a
    // waiting slot is free; without one the spot is given back while still linked, as the original does).
    void DemoteCasterToPending(IKSerializable* leaf, IKSerializable* shadowCpnt);
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
