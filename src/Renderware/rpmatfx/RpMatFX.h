// RpMatFX.h - the RenderWare MatFX material plugin (library code 0x696f68-0x69b4e8, TocBridge_RpMatFX* in 0x98e8f0..).
// The data is part of RpMaterial (rpworld/RpGeometry.h: RpMatFXMaterialData with two effect slots), filled by
// the stream reader MatFXMaterialStreamRead_maybe 0x69a388 (rpworld/RpGeometryStream.cpp) and by
// CMaterial's own calls below.
// C2.4 step 1 replaced the C1.3 shim (one fake RpGeometry/RpMaterial per CGeometry) with the real objects.
// The atomic side: RpMatFXAtomicEnableEffects / _rpMatFXPipelineAtomicSetup_maybe (below; the pipeline is a tag, the
// RxPipeline objects are not modelled). STUB(C2.4 step 4): the bump map texture (MatFX_CreateBumpedTexture_maybe) and
// the setters CMaterial_PostLoad needs.
#pragma once
#include <cstdint>

#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwTypes.h"

class IKSerializable;

struct RpAtomic;
// 0x0069a9c8 _rpMatFXPipelineAtomicSetup_maybe: the atomic's pipeline (+0x6c) becomes the MatFX atomic pipeline (the
// plugin global 0x00cec484); the atomic.
RpAtomic* _rpMatFXPipelineAtomicSetup(RpAtomic* atomic);
// 0x00698038 RpMatFXAtomicEnableEffects: unless the atomic's MatFX flag (its plugin data) is set already, the MatFX
// pipeline set up and the flag set; null when the setup fails, else the atomic.
RpAtomic* RpMatFXAtomicEnableEffects(RpAtomic* atomic);
// RpMatFXAtomicQueryEffects: the atomic's MatFX flag.
uint32_t RpMatFXAtomicQueryEffects(const RpAtomic* atomic);
// The MatFX atomic pipeline (0x00cec484, _rpMatFXPipelinesCreate's): the tag `atomic->pipeline` holds.
extern void* const g_rpMatFXAtomicPipeline;

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

// C2.8 port-rest R07: the getters / setters CMaterial's bump / env / dual accessors call (from the assembly; each
// finds its effect's slot as the others do: slot 0, else slot 1; a material without it is left alone / answers 0).
// 0x006977e0 RpMatFXMaterialSetDualBlendModes (then two KStub_Return1_69a9f8 render-state checks, no effect)
RpMaterial* RpMatFXMaterialSetDualBlendModes(RpMaterial* material, int32_t srcBlend, int32_t dstBlend);
// 0x00697898 RpMatFXMaterialSetDualTexture: the new texture's reference count up first, the old one destroyed.
RpMaterial* RpMatFXMaterialSetDualTexture(RpMaterial* material, RwTexture* texture);
// 0x00697310 / 0x006971e8 RpMatFXMaterialGet / SetBumpMapCoefficient: the slot keeps the coefficient negated.
float RpMatFXMaterialGetBumpMapCoefficient(const RpMaterial* material);
RpMaterial* RpMatFXMaterialSetBumpMapCoefficient(RpMaterial* material, float coefficient);
// 0x006972b0 / 0x00697180 RpMatFXMaterialGet / SetBumpMapFrame
void* RpMatFXMaterialGetBumpMapFrame(const RpMaterial* material);
RpMaterial* RpMatFXMaterialSetBumpMapFrame(RpMaterial* material, void* frame);
// 0x006985b8 RpMatFXMaterialGetBumpMapTexture: the slot's +0x08 texture (the bump map as streamed).
RwTexture* RpMatFXMaterialGetBumpMapTexture(const RpMaterial* material);
// 0x00697a48 RpMatFXMaterialSetBumpMapTexture: both textures released, the new one kept (+0x08) and the bumped one
// (+0x04) looked up by the interleaved names in the current dictionary or built (STUB(C2.4 step 4): the builder).
RpMaterial* RpMatFXMaterialSetBumpMapTexture(RpMaterial* material, RwTexture* texture);
// 0x00698618 RpMatFXMaterialSetupBumpMap: SetBumpMapTexture, then the frame and the coefficient.
RpMaterial* RpMatFXMaterialSetupBumpMap(RpMaterial* material, RwTexture* texture, void* frame, float coefficient);
// 0x00697568 RpMatFXMaterialGetEnvMapFBAlpha
int32_t RpMatFXMaterialGetEnvMapFBAlpha(const RpMaterial* material);
// 0x00697508 / 0x00697370 RpMatFXMaterialGet / SetEnvMapFrame
void* RpMatFXMaterialGetEnvMapFrame(const RpMaterial* material);
RpMaterial* RpMatFXMaterialSetEnvMapFrame(RpMaterial* material, void* frame);
// 0x00697980 RpMatFXMaterialSetEnvMapTexture: the new texture's reference count up first (BUG(original): no null
// check), the old one destroyed.
RpMaterial* RpMatFXMaterialSetEnvMapTexture(RpMaterial* material, RwTexture* texture);
// 0x00698fe0 RpMatFXMaterialSetupEnvMap: the texture as SetEnvMapTexture, then the frame, FB alpha and coefficient.
RpMaterial* RpMatFXMaterialSetupEnvMap(RpMaterial* material, RwTexture* texture, void* frame, int32_t useFBAlpha,
                                       float coefficient);
