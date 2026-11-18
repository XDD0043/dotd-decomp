// CGeometry.h - a renderable RenderWare atomic (key 0x8a, vtable 0xb129c8, size 0x30) and the particle
// tank geometry (CParticleGeometry, key 0x4a, size 0x34). Original units: CGeometry.cpp (0x88670..),
// CParticleGeometry.cpp (0x89688..). XXL2: K/KModules/KGL/Geometry/CGeometry.h (IRendableObject,
// CSBaseNode<CGeometry*>: m_pNext, m_pRpAtomic, m_cGeometryColor, m_pMaterial) and CParticleGeometry.h
// (m_baParticleGeometry). The remaster's file-name and material-name strings are not in DotD.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/IRendableObject.h"

struct RpAtomic;
struct RwCamera;
class IKTime;
class RenderQueue;
class CNode;
struct RpAtomic;

// 0x000bb828 CGeometry_SetupMaterialShader_maybe (unit CMaterial.cpp): the atomic's pipeline for its material's shader
// mode (CGeometry_PostLoad's first call, with the material's bits 3-6).
void CGeometry_SetupMaterialShader(RpAtomic* atomic, int32_t mode);

class CGeometry : public IRendableObject {
public:
    DOTD_CLASS_KEY(kCategoryGeometry, 0x2)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x990c30
        return key == 0x8a || key == 0xa8d || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CGeometry)

    CGeometry();                                        // 0x00088670 CGeometry_Create (inlined)
    ~CGeometry() override {}                            // 0x00990df8 CGeometry_Destructor (0x990d90 deleting): the vtables only (Destroy frees the atomic)
    // vt+0x10 0x00088570 CGeometry_Destroy: IRendableObject's, the atomic destroyed, no material.
    void Destroy() override;
    // vt+0x24 0x00087fc8 CGeometry_RecursiveRegistration: the third handle's (+0x2c) RecursiveRegistration when set;
    // not IRendableObject's (the geometry itself is not registered).
    void RecursiveRegistration(int32_t type) override {
        if (m_unk2c != nullptr) m_unk2c->RecursiveRegistration(type);
    }
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000892a0 CGeometry_Load
    // vt+0x30 0x00088c90 CGeometry_PostLoad (C2.4 step 4): the material shader setup, the tangent flag of the aux layer
    // modes, the aux geometry, the shadow shader flag.
    int32_t PostLoad(int32_t type) override;
    // vt+0x5c 0x00088e28 CGeometry_Render (C2.4 step 4): the shader manager's flags from the render flags, the fog
    // state, the geometry colour into the RW material, then the atomic's render callback (once, or once per alpha
    // reference of a multi-pass material).
    void Render(IKTime* frameClock) override;
    // vt+0x60 0x00089138 CGeometry_UpdateProperties: the render stage bits (0-4) from the blend mode, the material's
    // property bits and the layer (bits 17-18).
    void UpdateProperties() override;
    // vt+0x6c 0x000889f8 CGeometry_GetMaterialRenderInfo: (z write with alpha, alpha reference, alpha test, blend mode).
    void GetRenderingProperties(uint8_t* first, uint8_t* second, uint8_t* third, uint32_t* blendMode) override;
    // vt+0x74 0x00088b28 CGeometry_ComputeSortingCoef: the forced sort key, or the squared distance from the camera to
    // the atomic's world sphere centre times 1 / far^2.
    void ComputeSortingCoef(int32_t sortingOrder) override;
    // 0x00088028 CGeometry_SetBlendMode: the blend mode (render flag bits 8-9); a change updates the stage.
    void SetBlendMode(uint32_t blendMode);

    // vt+0x58 0x000886d8 CGeometry_UpdateAndExtract with its stage arguments (the 2D renderables' slot
    // is declared without them, IRendableObject::UpdateAndExtract): the material's per-frame update, the
    // distance cull, then the stage its render flags name (bits 0-4; material types 7 / 8: stage 16).
    void EnqueueVisible(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                        int32_t distanceCull);
    // vt+0x78 0x00088398 GetGeometryWorldBoundingSphere (CParticleGeometry: 0x000896e8).
    virtual float* GetWorldBoundingSphere(CNode* node);
    // vt+0x7c 0x00088340 CGeometry_UpdateBoundingSphere_maybe: the atomic's interpolated bounding sphere
    // (_rpAtomicResyncInterpolatedSphere), the atomic's dirty-sphere flag cleared and its world bound marked dirty.
    virtual void UpdateBoundingSphere();
    // vt+0x80 0x000882a8 CGeometry_vf80 (CParticleGeometry 0x00089820): the shader flag byte (+0x28): 1 when the geometry
    // receives shadow textures (render flags 0x800000 and 0x1000000) and the shadow service allows them.
    virtual void Vf80(int32_t arg);
    // vt+0x84 0x00088170 CGeometry_FindRpGeometry: the atomic's RpGeometry (CParticleGeometry 0x00089d60: its
    // PTank atomic's quad geometry, or its emitter's PTank's).
    virtual void* FindRpGeometry();
    // vt+0x88 0x0008a520 CParticleGeometry_HasParticlesToDraw_maybe (CGeometry's: 1).
    virtual int32_t HasParticlesToDraw() { return 1; }
    // 0x00088530 CGeometry_UnlockGeometry_maybe (not virtual): RpGeometryUnlock of the atomic's geometry; 1 when it
    // returned the geometry.
    int32_t UnlockGeometry();

    CGeometry* m_pNext;             // +0x18 (XXL2 CSBaseNode<CGeometry*>::m_pNext): a handle
    RpAtomic* m_pRpAtomic;          // +0x1c streamed (chunk 0x14, RpAtomicStreamRead), cloned from another geometry, or a PTank
    uint8_t m_cGeometryColor[4];    // +0x20 CColor, read without a byte swap
    IKSerializable* m_pMaterial;    // +0x24 CMaterial (a handle)
    uint32_t m_unk28;               // +0x28 DotD; not set by the constructor or Load; its first byte is bShaderFlag
    uint8_t ShaderFlag() const { return *reinterpret_cast<const uint8_t*>(&m_unk28); }  // lbz 0x28
    void SetShaderFlag(uint8_t flag) { *reinterpret_cast<uint8_t*>(&m_unk28) = flag; }
    IKSerializable* m_unk2c;        // +0x2c DotD: a third handle
};
DOTD_ASSERT_SIZE(CGeometry, 0x30);
DOTD_ASSERT_OFFSET(CGeometry, m_pNext, 0x18);
DOTD_ASSERT_OFFSET(CGeometry, m_cGeometryColor, 0x20);
DOTD_ASSERT_OFFSET(CGeometry, m_unk2c, 0x2c);

class CParticleGeometry : public CGeometry {
public:
    DOTD_CLASS_KEY(kCategoryGeometry, 0x1)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x99c310
        return key == 0x4a || key == 0x8a || key == 0xa8d || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CParticleGeometry)

    CParticleGeometry() : m_baParticleGeometry(0) {}    // 0x00089fc0 CParticleGeometry_Create (inlined)
    void RecursiveRegistration(int32_t /*type*/) override {}  // vt+0x24 0x000896d8: returns 1, registers nothing
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0008a590 CParticleGeometry_Load
    // vt+0x30 0x0008a050 CParticleGeometry_PostLoad: CGeometry's, then the blend flag again and vt+0x80 with 1.
    int32_t PostLoad(int32_t type) override;
    void Render(IKTime* frameClock) override;                             // vt+0x5c 0x00089908 CParticleGeometry_Render
    // vt+0x60 0x0008a0e8 CParticleGeometry_UpdateProperties: the render stage from the blend mode (13 additive, else
    // 14, unless bit 5), then the PTank's blend modes for the mode: a PTank atomic also gets its vertex alpha (any mode
    // but 0) and bit 21; an RpPrtStd atomic's emitter PTank property gets them too (bit 21 cleared).
    void UpdateProperties() override;
    // vt+0x6c 0x0008a028 CParticleGeometry_GetRenderingProperties: z write 1, alpha 0xff, 0, the blend mode.
    void GetRenderingProperties(uint8_t* first, uint8_t* second, uint8_t* third, uint32_t* blendMode) override;
    float* GetWorldBoundingSphere(CNode* node) override;  // vt+0x78 0x000896e8
    void Vf80(int32_t mode) override;                     // vt+0x80 0x00089820 CParticleGeometry_vf80
    int32_t HasParticlesToDraw() override;                // vt+0x88 0x0008a520
    // vt+0x8c 0x000898c8 CParticleGeometry_UnlockPTank_maybe: RpPTankAtomicUnlock of the atomic; 1 when it returned an atomic
    // (declared non-virtual: every caller so far holds a CParticleGeometry).
    int32_t UnlockPTank();
    // 0x0008a290 CParticleGeometry_UpdateAtomicBoundingSphere_maybe: the atomic's sphere around the particles.
    void UpdateAtomicBoundingSphere();
    // vt+0x84 0x00089d60 CParticleGeometry_FindRpGeometry: the PTank atomic's geometry, or for an RpPrtStd atomic the
    // geometry of its emitter's PTank property (made first when there is none).
    void* FindRpGeometry() override;

    // +0x30 (XXL2 CBitArray m_baParticleGeometry): which PTank arrays and constants the file holds
    // (rpPTANKDFLAG* bits 0x1..0x8000).
    uint32_t m_baParticleGeometry;
};
DOTD_ASSERT_SIZE(CParticleGeometry, 0x34);
DOTD_ASSERT_OFFSET(CParticleGeometry, m_baParticleGeometry, 0x30);

// 0x00088190 ParticleDraw_SetShaderParticleFlags_maybe (CParticleGeometry::Render's first call): the shader manager's
// flag word +0x8c (ShaderSceneInputs::managerFlags) for the geometry, as CGeometry::Render sets it: bit 1 = render flag
// 25 (point lights), bit 2 = render flag 0x100000 (far texture), bit 0 = the shader flag byte +0x28.
void ParticleDraw_SetShaderParticleFlags(const CGeometry* geometry);

// 0x00cf9c90: the engine's render lock (render queues, scene roots, geometry loads).
void RenderLock_Lock();
void RenderLock_Unlock();
