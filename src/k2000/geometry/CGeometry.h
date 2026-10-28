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

class CGeometry : public IRendableObject {
public:
    DOTD_CLASS_KEY(kCategoryGeometry, 0x2)
    DOTD_DECLARE_FACTORIES(CGeometry)

    CGeometry();                                        // 0x00088670 CGeometry_Create (inlined)
    ~CGeometry() override {}                            // STUB(C1.6): destroys the atomic
    // vt+0x10 0x00088570 CGeometry_Destroy: IRendableObject's, the atomic destroyed, no material.
    void Destroy() override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000892a0 CGeometry_Load
    // vt+0x30 0x00088c90 CGeometry_PostLoad (C2.4 step 4): the material shader setup, the tangent flag of the aux layer
    // modes, the aux geometry, the shadow shader flag.
    int32_t PostLoad(int32_t type) override;
    // vt+0x5c 0x00088e28 CGeometry_Render (C2.4 step 4): the shader manager's flags from the render flags, the fog
    // state, the geometry colour into the RW material, then the atomic's render callback (once, or once per alpha
    // reference of a multi-pass material).
    void Render() override;
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
    // distance cull, then the stage its render flags name (bits 0-4; material types 7 / 8: STUB(C2)).
    void EnqueueVisible(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                        int32_t distanceCull);
    // vt+0x78 0x00088398 GetGeometryWorldBoundingSphere (CParticleGeometry: 0x000896e8).
    virtual float* GetWorldBoundingSphere(CNode* node);
    virtual void UpdateBoundingSphere() {}   // vt+0x7c 0x00088340 CGeometry_UpdateBoundingSphere_maybe  STUB(C2)
    // vt+0x80 0x000882a8 CGeometry_vf80 (CParticleGeometry 0x00089820): the shader flag byte (+0x28): 1 when the geometry
    // receives shadow textures (render flags 0x800000 and 0x1000000) and the shadow service allows them.
    virtual void Vf80(int32_t arg);
    // vt+0x84 0x00088170 CGeometry_FindRpGeometry: the atomic's RpGeometry (CParticleGeometry 0x00089d60: its
    // PTank atomic's; the shim's PTank atomics have none, so null, see RwShim_FindRpGeometry).
    virtual void* FindRpGeometry();
    // vt+0x88 0x0008a520 CParticleGeometry_HasParticlesToDraw_maybe (CGeometry's: 1).
    virtual int32_t HasParticlesToDraw() { return 1; }

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
    DOTD_DECLARE_FACTORIES(CParticleGeometry)

    CParticleGeometry() : m_baParticleGeometry(0) {}    // 0x00089fc0 CParticleGeometry_Create (inlined)
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0008a590 CParticleGeometry_Load
    // vt+0x30 0x0008a050 CParticleGeometry_PostLoad: CGeometry's, then the blend flag again and vt+0x80 with 1.
    int32_t PostLoad(int32_t type) override;
    void Render() override;                             // vt+0x5c 0x00089908 CParticleGeometry_Render
    float* GetWorldBoundingSphere(CNode* node) override;  // vt+0x78 0x000896e8
    int32_t HasParticlesToDraw() override;                // vt+0x88 0x0008a520
    // vt+0x84 0x00089d60 CParticleGeometry_FindRpGeometry: the PTank atomic's geometry, or for an RpPrtStd atomic the
    // geometry of its emitter's PTank property. STUB(C2.4 step 4): the shim's PTank atomics and the emitters'
    // PTanks have no RpGeometry; null (RwShim_FindRpGeometry then makes one).
    void* FindRpGeometry() override { return nullptr; }

    // +0x30 (XXL2 CBitArray m_baParticleGeometry): which PTank arrays and constants the file holds
    // (rpPTANKDFLAG* bits 0x1..0x8000).
    uint32_t m_baParticleGeometry;
};
DOTD_ASSERT_SIZE(CParticleGeometry, 0x34);
DOTD_ASSERT_OFFSET(CParticleGeometry, m_baParticleGeometry, 0x30);

// 0x00cf9c90: the engine's render lock (render queues, scene roots, geometry loads).
void RenderLock_Lock();
void RenderLock_Unlock();
