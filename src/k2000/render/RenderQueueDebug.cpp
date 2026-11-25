// RenderQueueDebug.cpp - DEV (platform/gfx/gpuprof.h, not in the original): the description of a render stage's item for
// the GPU test's measured frames. A file of its own: RwTexture.h and RpWorld.h (CRenderer.cpp) both define RwLinkList.
#include <cstdio>
#include <string>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwRaster.h"
#include "Renderware/rwcore/RwTexture.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/graphical/IRendableObject.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/misc/ClassRegistry.h"

// DEV (gpuprof.h): what identifies an item of a described stage: its class, its geometry's triangles and vertices, its
// CMaterial's shader mode, its first texture with the size, and the number of materials.
std::string RenderQueueItemDescription(IRendableObject* item) {
    char text[200];
    const KClassInfo* info = FindClassInfo(MakeClassKey(static_cast<uint32_t>(item->GetClassType()),
                                                        static_cast<uint32_t>(item->GetClassID())));
    int n = std::snprintf(text, sizeof(text), "%s", info != nullptr ? info->name : "?");
    if (item->IsKindOfClass(CGeometry::kClassKey) != 0) {
        CGeometry* geometry = static_cast<CGeometry*>(item);
        const RpGeometry* g = geometry->m_pRpAtomic != nullptr ? geometry->m_pRpAtomic->geometry : nullptr;
        if (g != nullptr) {
            n += std::snprintf(text + n, sizeof(text) - n, ", %d triangles, %d vertices, %d material(s)", g->numTriangles,
                               g->numVertices, g->matList.numMaterials);
            const RpMaterial* m = g->matList.numMaterials > 0 ? g->matList.materials[0] : nullptr;
            if (m != nullptr && m->texture != nullptr) {
                const RwRaster* r = m->texture->raster;
                n += std::snprintf(text + n, sizeof(text) - n, ", texture %s %dx%d", m->texture->name,
                                   r != nullptr ? r->width : 0, r != nullptr ? r->height : 0);
            }
        }
        if (geometry->m_pMaterial != nullptr && geometry->m_pMaterial->IsKindOfClass(CMaterial::kClassKey) != 0) {
            std::snprintf(text + n, sizeof(text) - n, ", shader mode %u",
                          static_cast<CMaterial*>(geometry->m_pMaterial)->GetShaderMode());
        }
    }
    return text;
}
