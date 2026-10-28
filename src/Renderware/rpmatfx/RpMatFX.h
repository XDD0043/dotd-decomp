// RpMatFX.h - the RenderWare MatFX material plugin (library code 0x696f68-0x69b4e8, TocBridge_RpMatFX* in 0x98e8f0..).
// The data is part of RpMaterial (rpworld/RpGeometry.h: RpMatFXMaterialData with two effect slots), filled by
// the stream reader MatFXMaterialStreamRead_maybe 0x69a388 (rpworld/RpGeometryStream.cpp) and by
// CMaterial's own calls below.
// C2.4 step 1 replaced the C1.3 shim (one fake RpGeometry/RpMaterial per CGeometry) with the real objects.
// STUB(C2.4 step 4): the MatFX pipelines (RpMatFXAtomicEnableEffects, _rpMatFXPipelineAtomicSetup_maybe), the
// bump map texture (MatFX_CreateBumpedTexture_maybe) and the setters CMaterial_PostLoad needs.
#pragma once
#include <cstdint>

#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwTypes.h"

class IKSerializable;

// The geometry object's vt+0x84 (CGeometry_FindRpGeometry 0x00088170, CParticleGeometry_FindRpGeometry
// 0x00089d60; XXL2 CGeometry::FindRpGeometry): the atomic's RpGeometry, as CMaterial_Load asks for it.
// STUB(C2.4 step 4): the PTank atomics of CParticleGeometry have no RpGeometry in the shim (the original
// returns the one RpPTankAtomicCreate made, with one material); they get one fake geometry with one material,
// created on first use (null in, null out).
RpGeometry* RwShim_FindRpGeometry(IKSerializable* geometry);

// 0x00699740 RpMatFXMaterialSetEffects: the data allocated on first use; a change of the effect word cleans
// it (MatFXMaterialDataClean_maybe 0x697d50); then the slots' types: 1 bump (slot 0), 2 env map, 3 bump + env
// (slots 0, 1), 4 dual (blend modes 5 / 6), 5 UV transform, 6 dual UV transform (slot 0 UV, slot 1 dual).
RpMaterial* RpMatFXMaterialSetEffects(RpMaterial* material, uint32_t effects);
// 0x00697150 RpMatFXMaterialGetEffects
uint32_t RpMatFXMaterialGetEffects(const RpMaterial* material);

// RpMatFX (library, TocBridge_RpMatFXMaterial* 0x0098e9c0 / 0x0098e9d0 / 0x0098e940).
RpMaterial* RpMatFXMaterialSetEnvMapCoefficient(RpMaterial* material, float coefficient);
RpMaterial* RpMatFXMaterialSetEnvMapFBAlpha(RpMaterial* material, int32_t useFBAlpha);
// 0x006976f8 RpMatFXMaterialSetUVTransformMatrices
RpMaterial* RpMatFXMaterialSetUVTransformMatrices(RpMaterial* material, RwMatrix* baseTransform, RwMatrix* dualTransform);
const RpMaterial* RpMatFXMaterialGetUVTransformMatrices(const RpMaterial* material, RwMatrix** baseTransform,
                                                        RwMatrix** dualTransform);

// 0x006974a8 RpMatFXMaterialGetEnvMapTexture: the env map effect's texture, or null.
RwTexture* RpMatFXMaterialGetEnvMapTexture(const RpMaterial* material);
// 0x006975c8 RpMatFXMaterialGetEnvMapCoefficient: the env map effect's coefficient (0 without one).
float RpMatFXMaterialGetEnvMapCoefficient(const RpMaterial* material);
// 0x00697628 RpMatFXMaterialGetDualTexture: the dual effect's texture, or null.
RwTexture* RpMatFXMaterialGetDualTexture(const RpMaterial* material);
// 0x00697688 RpMatFXMaterialGetDualBlendModes: the dual effect's source and destination blend modes (0, 0 without one).
const RpMaterial* RpMatFXMaterialGetDualBlendModes(const RpMaterial* material, int32_t* srcBlend, int32_t* dstBlend);
