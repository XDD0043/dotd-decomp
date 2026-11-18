// RpMatFX.cpp - see RpMatFX.h.
#include "Renderware/rpmatfx/RpMatFX.h"

#include <cstring>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rwcore/RwRaster.h"
#include "Renderware/rwcore/RwSList.h"
#include "Renderware/rwcore/RwTexture.h"

namespace {
// The slot of the given effect type, or null. BUG(original): the PS3 setters test slot 0 then slot 1 and write
// through a null slot pointer when neither matches (a fault on the PS3); no game path gets there (CMaterial_PostLoad
// sets the effects before any setter), and the port's callers skip a material without the effect.
RpMatFXEffect* FindEffect(const RpMaterial* material, uint32_t type) {
    RpMatFXMaterialData* data = material->matfx;
    if (data == nullptr) return nullptr;
    if (data->effects[0].type == type) return &data->effects[0];
    if (data->effects[1].type == type) return &data->effects[1];
    return nullptr;
}

// RwTextureDestroy 0x7548c0 as MatFX calls it (when the slot has a texture).
void TextureRelease(RwTexture* texture) {
    if (texture != nullptr) RwTextureDestroy(texture);
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

// ---- C2.8 port-rest R07: CMaterial's bump / env / dual accessors' library side (from the assembly) -----------------

// 0x006977e0 RpMatFXMaterialSetDualBlendModes (the two KStub_Return1_69a9f8 render-state checks after it do nothing)
RpMaterial* RpMatFXMaterialSetDualBlendModes(RpMaterial* material, int32_t srcBlend, int32_t dstBlend) {
    if (RpMatFXEffect* effect = FindEffect(material, rpMATFXEFFECTDUAL)) {
        effect->dual.srcBlendMode = srcBlend;
        effect->dual.dstBlendMode = dstBlend;
    }
    return material;
}

// 0x00697898 RpMatFXMaterialSetDualTexture (BUG(original): the new texture's count is raised without a null check)
RpMaterial* RpMatFXMaterialSetDualTexture(RpMaterial* material, RwTexture* texture) {
    RpMatFXEffect* effect = FindEffect(material, rpMATFXEFFECTDUAL);
    ++texture->refCount;
    if (effect == nullptr) return material;
    if (effect->dual.texture != nullptr) {
        RwTextureDestroy(effect->dual.texture);
        effect->dual.texture = nullptr;
    }
    effect->dual.texture = texture;
    return material;
}

// 0x00697310 RpMatFXMaterialGetBumpMapCoefficient (fneg of the slot's +0x0c)
float RpMatFXMaterialGetBumpMapCoefficient(const RpMaterial* material) {
    const RpMatFXEffect* effect = FindEffect(material, rpMATFXEFFECTBUMPMAP);
    return effect != nullptr ? -effect->bump.coefficient : 0.0f;
}

// 0x006971e8 RpMatFXMaterialSetBumpMapCoefficient
RpMaterial* RpMatFXMaterialSetBumpMapCoefficient(RpMaterial* material, float coefficient) {
    if (RpMatFXEffect* effect = FindEffect(material, rpMATFXEFFECTBUMPMAP)) effect->bump.coefficient = -coefficient;
    return material;
}

// 0x006972b0 RpMatFXMaterialGetBumpMapFrame
void* RpMatFXMaterialGetBumpMapFrame(const RpMaterial* material) {
    const RpMatFXEffect* effect = FindEffect(material, rpMATFXEFFECTBUMPMAP);
    return effect != nullptr ? effect->bump.frame : nullptr;
}

// 0x00697180 RpMatFXMaterialSetBumpMapFrame
RpMaterial* RpMatFXMaterialSetBumpMapFrame(RpMaterial* material, void* frame) {
    if (RpMatFXEffect* effect = FindEffect(material, rpMATFXEFFECTBUMPMAP)) effect->bump.frame = frame;
    return material;
}

// 0x006985b8 RpMatFXMaterialGetBumpMapTexture
RwTexture* RpMatFXMaterialGetBumpMapTexture(const RpMaterial* material) {
    const RpMatFXEffect* effect = FindEffect(material, rpMATFXEFFECTBUMPMAP);
    return effect != nullptr ? effect->bump.texture8 : nullptr;
}

// 0x00697a48 RpMatFXMaterialSetBumpMapTexture. The bumped texture's name interleaves the base texture's name with the
// bump map's (one character of each while they last, at most 30), the bump map's twice without a base texture.
RpMaterial* RpMatFXMaterialSetBumpMapTexture(RpMaterial* material, RwTexture* texture) {
    RpMatFXEffect* effect = FindEffect(material, rpMATFXEFFECTBUMPMAP);
    if (effect == nullptr) return material;  // the PS3 writes through a null slot pointer
    if (effect->bump.texture8 != nullptr) {
        RwTextureDestroy(effect->bump.texture8);
        effect->bump.texture8 = nullptr;
    }
    if (effect->bump.texture4 != nullptr) {
        RwTextureDestroy(effect->bump.texture4);
        effect->bump.texture4 = nullptr;
        effect->bump.invWidth = 0.0f;
    }
    if (texture == nullptr) {  // 0x00697ce0: 1 / the base texture's raster width
        effect->bump.invWidth = 1.0f / static_cast<float>(material->texture->raster->width);
        return material;
    }
    effect->bump.texture8 = texture;
    ++texture->refCount;
    RwTexture* base = material->texture;
    if (texture->raster->width == 0) return material;
    if (base != nullptr && base->raster->width == 0) return material;
    const char* a = base != nullptr ? base->name : texture->name;
    const char* b = texture->name;
    char name[32] = {};
    int32_t count = 0;
    char* out = name;
    for (;;) {  // 0x00697bc4
        if (*a != 0) {
            *out++ = *a++;
            ++count;
            if (*b == 0) {
                if (count > 29) break;
                continue;
            }
        } else if (*b == 0) {
            break;
        }
        *out++ = *b++;  // 0x00697ba4
        ++count;
        if (count > 29) break;
    }
    *out = 0;
    RwTexDictionary* dict = RwTexDictionaryGetCurrent();
    effect->bump.texture4 = nullptr;
    RwTexture* bumped = dict != nullptr ? RwTexDictionaryFindNamedTexture(dict, name) : nullptr;
    effect->bump.texture4 = bumped;
    if (bumped != nullptr) {
        ++bumped->refCount;
    } else {
        // 0x0069b4c0 MatFX_CreateBumpedTextureWrapper_maybe (-> 0x698770): STUB(C2.4 step 4), the RwImage resample /
        // alpha / raster pipeline that builds the bumped texture is not ported; as a failed build (null).
        bumped = nullptr;
        effect->bump.texture4 = bumped;
        if (bumped == nullptr) return nullptr;
        if (dict != nullptr) RwTexDictionaryAddTexture(dict, bumped);
    }
    effect->bump.invWidth = 1.0f / static_cast<float>(effect->bump.texture4->raster->width);
    return material;
}

// 0x00698618 RpMatFXMaterialSetupBumpMap
RpMaterial* RpMatFXMaterialSetupBumpMap(RpMaterial* material, RwTexture* texture, void* frame, float coefficient) {
    if (RpMatFXMaterialSetBumpMapTexture(material, texture) == nullptr) return nullptr;
    RpMatFXMaterialSetBumpMapFrame(material, frame);
    if (material == nullptr) return nullptr;
    return RpMatFXMaterialSetBumpMapCoefficient(material, coefficient);
}

// 0x00697568 RpMatFXMaterialGetEnvMapFBAlpha
int32_t RpMatFXMaterialGetEnvMapFBAlpha(const RpMaterial* material) {
    const RpMatFXEffect* effect = FindEffect(material, rpMATFXEFFECTENVMAP);
    return effect != nullptr ? effect->env.useFrameBufferAlpha : 0;
}

// 0x00697508 RpMatFXMaterialGetEnvMapFrame
void* RpMatFXMaterialGetEnvMapFrame(const RpMaterial* material) {
    const RpMatFXEffect* effect = FindEffect(material, rpMATFXEFFECTENVMAP);
    return effect != nullptr ? effect->env.frame : nullptr;
}

// 0x00697370 RpMatFXMaterialSetEnvMapFrame
RpMaterial* RpMatFXMaterialSetEnvMapFrame(RpMaterial* material, void* frame) {
    if (RpMatFXEffect* effect = FindEffect(material, rpMATFXEFFECTENVMAP)) effect->env.frame = frame;
    return material;
}

// 0x00697980 RpMatFXMaterialSetEnvMapTexture
RpMaterial* RpMatFXMaterialSetEnvMapTexture(RpMaterial* material, RwTexture* texture) {
    RpMatFXEffect* effect = FindEffect(material, rpMATFXEFFECTENVMAP);
    ++texture->refCount;  // BUG(original): no null check
    if (effect == nullptr) return material;
    if (effect->env.texture != nullptr) {
        RwTextureDestroy(effect->env.texture);
        effect->env.texture = nullptr;
    }
    effect->env.texture = texture;
    return material;
}

// 0x00698fe0 RpMatFXMaterialSetupEnvMap
RpMaterial* RpMatFXMaterialSetupEnvMap(RpMaterial* material, RwTexture* texture, void* frame, int32_t useFBAlpha,
                                       float coefficient) {
    RpMatFXMaterialSetEnvMapTexture(material, texture);
    if (material == nullptr) return nullptr;
    RpMatFXMaterialSetEnvMapFrame(material, frame);
    RpMatFXMaterialSetEnvMapFBAlpha(material, useFBAlpha);
    return RpMatFXMaterialSetEnvMapCoefficient(material, coefficient);
}

namespace {
// The MatFX atomic pipeline object (RxPipeline objects are not modelled: RpAtomicPSGL_Render draws every atomic).
uint8_t s_matfxAtomicPipeline = 0;
}  // namespace

void* const g_rpMatFXAtomicPipeline = &s_matfxAtomicPipeline;  // 0x00cec484

// 0x0069a9c8 _rpMatFXPipelineAtomicSetup_maybe
RpAtomic* _rpMatFXPipelineAtomicSetup(RpAtomic* atomic) {
    atomic->pipeline = g_rpMatFXAtomicPipeline;
    return atomic;
}

// 0x00698038 RpMatFXAtomicEnableEffects
RpAtomic* RpMatFXAtomicEnableEffects(RpAtomic* atomic) {
    if (atomic->matfxEffects == 0) {
        if (_rpMatFXPipelineAtomicSetup(atomic) == nullptr) return nullptr;
        atomic->matfxEffects = 1;
    }
    return atomic;
}

// RpMatFXAtomicQueryEffects (the plugin data word).
uint32_t RpMatFXAtomicQueryEffects(const RpAtomic* atomic) { return atomic->matfxEffects; }
