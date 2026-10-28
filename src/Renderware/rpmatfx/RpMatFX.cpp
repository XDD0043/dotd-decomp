// RpMatFX.cpp - see RpMatFX.h.
#include "Renderware/rpmatfx/RpMatFX.h"

#include <cstring>
#include <unordered_map>

#include "Renderware/rwcore/RwSList.h"
#include "Renderware/rwcore/RwTexture.h"
#include "k2000/geometry/CGeometry.h"

namespace {
// The slot of the given effect type, or null (the PS3 code tests slot 0 then slot 1 and uses the slot
// pointer even when neither matches: a null write; here the callers tolerate a material without the effect,
// STUB(C2.4 step 4): CMaterial_PostLoad sets the effects first).
RpMatFXEffect* FindEffect(const RpMaterial* material, uint32_t type) {
    RpMatFXMaterialData* data = material->matfx;
    if (data == nullptr) return nullptr;
    if (data->effects[0].type == type) return &data->effects[0];
    if (data->effects[1].type == type) return &data->effects[1];
    return nullptr;
}

// RwTextureDestroy as MatFX uses it: the reference count (the textures belong to their dictionaries).
void TextureRelease(RwTexture* texture) {
    if (texture != nullptr) --texture->refCount;
}

// 0x00697d50 MatFXMaterialDataClean_maybe: the textures of the slots released, everything zeroed.
void DataClean(RpMatFXMaterialData* data) {
    for (RpMatFXEffect& effect : data->effects) {
        switch (effect.type) {
        case rpMATFXEFFECTBUMPMAP:
            TextureRelease(effect.bump.texture4);
            TextureRelease(effect.bump.texture8);
            break;
        case rpMATFXEFFECTENVMAP:
            TextureRelease(effect.env.texture);
            break;
        case rpMATFXEFFECTDUAL:
            TextureRelease(effect.dual.texture);
            break;
        case rpMATFXEFFECTUVTRANSFORM:
            effect.uv.baseTransform = nullptr;
            effect.uv.dualTransform = nullptr;
            break;
        default:
            break;
        }
    }
    std::memset(data, 0, sizeof(RpMatFXMaterialData));
}
}  // namespace

RpGeometry* RwShim_FindRpGeometry(IKSerializable* geometry) {
    if (geometry == nullptr) return nullptr;
    RpGeometry* found = static_cast<RpGeometry*>(static_cast<CGeometry*>(geometry)->FindRpGeometry());  // vt+0x84
    if (found != nullptr) return found;
    static std::unordered_map<const IKSerializable*, RpGeometry*> geometries;
    RpGeometry*& fake = geometries[geometry];
    if (fake == nullptr) {
        RpMaterial* material = RpMaterialCreate();
        fake = RpGeometryCreate(0, 0, 0);
        _rpMaterialListAppendMaterial(&fake->matList, material);
        RpMaterialDestroy(material);  // the list holds the reference
        RpMatFXMaterialSetEffects(material, rpMATFXEFFECTENVMAP);  // the K materials set the env map values
    }
    return fake;
}

// 0x00699740 RpMatFXMaterialSetEffects
RpMaterial* RpMatFXMaterialSetEffects(RpMaterial* material, uint32_t effects) {
    RpMatFXMaterialData* data = material->matfx;
    if (data == nullptr) {
        data = static_cast<RpMatFXMaterialData*>(RwMalloc(sizeof(RpMatFXMaterialData), 0x30120));
        std::memset(data, 0, sizeof(RpMatFXMaterialData));
        material->matfx = data;
    }
    if (effects == 0 || (data->flags != 0 && effects != data->flags)) {
        DataClean(data);
        data->flags = effects;
    } else {
        data->flags = effects;
    }
    switch (effects) {
    case 1:
        data->effects[0].type = rpMATFXEFFECTBUMPMAP;
        break;
    case 2:
        data->effects[0].type = rpMATFXEFFECTENVMAP;
        break;
    case 3:
        data->effects[0].type = rpMATFXEFFECTBUMPMAP;
        data->effects[1].type = rpMATFXEFFECTENVMAP;
        break;
    case 4:
    case 6:
        if (effects == 6) {
            data->effects[1].type = rpMATFXEFFECTDUAL;
            data->effects[0].type = rpMATFXEFFECTUVTRANSFORM;
        } else {
            data->effects[0].type = rpMATFXEFFECTDUAL;
        }
        {  // the dual slot's blend modes: rwBLENDSRCALPHA 5 / rwBLENDINVSRCALPHA 6
            RpMatFXEffect* dual = FindEffect(material, rpMATFXEFFECTDUAL);
            dual->dual.srcBlendMode = 5;
            dual->dual.dstBlendMode = 6;
        }
        break;
    case 5:
        data->effects[0].type = rpMATFXEFFECTUVTRANSFORM;
        break;
    default:
        break;
    }
    return material;
}

// 0x00697150 RpMatFXMaterialGetEffects
uint32_t RpMatFXMaterialGetEffects(const RpMaterial* material) {
    return material->matfx != nullptr ? material->matfx->flags : 0;
}

// 0x00697440 RpMatFXMaterialSetEnvMapCoefficient
RpMaterial* RpMatFXMaterialSetEnvMapCoefficient(RpMaterial* material, float coefficient) {
    if (RpMatFXEffect* effect = FindEffect(material, rpMATFXEFFECTENVMAP)) effect->env.coefficient = coefficient;
    return material;
}

// 0x006973d8 RpMatFXMaterialSetEnvMapFBAlpha
RpMaterial* RpMatFXMaterialSetEnvMapFBAlpha(RpMaterial* material, int32_t useFBAlpha) {
    if (RpMatFXEffect* effect = FindEffect(material, rpMATFXEFFECTENVMAP)) effect->env.useFrameBufferAlpha = useFBAlpha;
    return material;
}

// 0x00697760 RpMatFXMaterialGetUVTransformMatrices
const RpMaterial* RpMatFXMaterialGetUVTransformMatrices(const RpMaterial* material, RwMatrix** baseTransform,
                                                        RwMatrix** dualTransform) {
    RpMatFXEffect* effect = FindEffect(material, rpMATFXEFFECTUVTRANSFORM);
    if (baseTransform != nullptr) *baseTransform = effect != nullptr ? effect->uv.baseTransform : nullptr;
    if (dualTransform != nullptr) *dualTransform = effect != nullptr ? effect->uv.dualTransform : nullptr;
    return material;
}

// 0x006976f8 RpMatFXMaterialSetUVTransformMatrices: the UV transform effect's two matrices (slot 0, else slot 1).
// The PS3 writes through a null pointer when the material has no such effect; here it is left alone.
RpMaterial* RpMatFXMaterialSetUVTransformMatrices(RpMaterial* material, RwMatrix* baseTransform, RwMatrix* dualTransform) {
    if (RpMatFXEffect* effect = FindEffect(material, rpMATFXEFFECTUVTRANSFORM)) {
        effect->uv.baseTransform = baseTransform;
        effect->uv.dualTransform = dualTransform;
    }
    return material;
}

// 0x006974a8 RpMatFXMaterialGetEnvMapTexture
RwTexture* RpMatFXMaterialGetEnvMapTexture(const RpMaterial* material) {
    const RpMatFXEffect* effect = FindEffect(material, rpMATFXEFFECTENVMAP);
    return effect != nullptr ? effect->env.texture : nullptr;
}

// 0x006975c8 RpMatFXMaterialGetEnvMapCoefficient
float RpMatFXMaterialGetEnvMapCoefficient(const RpMaterial* material) {
    const RpMatFXEffect* effect = FindEffect(material, rpMATFXEFFECTENVMAP);
    return effect != nullptr ? effect->env.coefficient : 0.0f;
}

// 0x00697628 RpMatFXMaterialGetDualTexture
RwTexture* RpMatFXMaterialGetDualTexture(const RpMaterial* material) {
    const RpMatFXEffect* effect = FindEffect(material, rpMATFXEFFECTDUAL);
    return effect != nullptr ? effect->dual.texture : nullptr;
}

// 0x00697688 RpMatFXMaterialGetDualBlendModes
const RpMaterial* RpMatFXMaterialGetDualBlendModes(const RpMaterial* material, int32_t* srcBlend, int32_t* dstBlend) {
    const RpMatFXEffect* effect = FindEffect(material, rpMATFXEFFECTDUAL);
    if (srcBlend != nullptr) *srcBlend = effect != nullptr ? effect->dual.srcBlendMode : 0;
    if (dstBlend != nullptr) *dstBlend = effect != nullptr ? effect->dual.dstBlendMode : 0;
    return material;
}
