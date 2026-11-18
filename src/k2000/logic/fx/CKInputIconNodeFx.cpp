// CKInputIconNodeFx.cpp - reconstructed original translation unit 0x1c4480-0x1c5f28 (GAME_TOC1, main_toc1), 28 functions, 26 live.
// Primary class: CKInputIconNodeFx  key 0x458c  category Logic  size 0x3c  vtable 0xb1d098
// Other owners: InputIconFx (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1c4480  CKInputIconNodeFx_Delete
//   [x] 0x1c44d0  CKInputIconNodeFx_StopIfLinkedTo
//   [x] 0x1c4588  CKInputIconNodeFx_OnPause
//   [x] 0x1c45c8  CKInputIconNodeFx_SetPosition_maybe
//   [ ] 0x1c4620  RegisterCKInputIconNodeFxClass
//   [ ] 0x1c46a8  _GLOBAL__D_1c46a8
//   [ ] 0x1c46b8  _GLOBAL__I_1c46b8
//   [x] 0x1c46c8  CKInputIconNodeFx_ApplyDisplayMode_maybe
//   [x] 0x1c4968  CKInputIconNodeFx_Stop
//   [x] 0x1c49e8  CKInputIconNodeFx_PostLoad
//   [x] 0x1c4a10  CKInputIconNodeFx_Load
//   [ ] 0x1c4a38  CKInputIconNodeFx_Save
//   [x] 0x1c4a60  CKInputIconNodeFx_RecursiveRegistration
//   [x] 0x1c4a88  CKInputIconNodeFx_Destroy  (inherited: CKNodeFx3d_Destroy)
//   [x] 0x1c4ab0  CKInputIconNodeFx_Construct  (the constructor)
//   [x] 0x1c4af0  CKInputIconNodeFx_Construct_2  (the constructor)
//   [x] 0x1c4b30  CKInputIconNodeFx_DeleteArray
//   [x] 0x1c4bd8  InputIconFx_UpdateWorldPosition_maybe
//   [ ] 0x1c4ca0  FUN_001c4ca0  [dead]
//   [x] 0x1c4d30  CKInputIconNodeFx_UpdatePlacement_maybe
//   [x] 0x1c5558  CKInputIconNodeFx_Update
//   [x] 0x1c5a88  CKInputIconNodeFx_Start
//   [x] 0x1c5c80  CKInputIconNodeFx_CreateArray
//   [x] 0x1c5d48  CKInputIconNodeFx_Create
//   [x] 0x1c5da8  CKInputIconNodeFx_SetAlpha_maybe
//   [ ] 0x1c5ea0  CKInputIconNodeFx_Destruct_2  [dead]
//   [x] 0x1c5ec0  CKInputIconNodeFx_Destruct  (C++ destructor)
//   [x] 0x1c5ee0  CKInputIconNodeFx_DeletingDestruct  (C++ deleting destructor)
//
//   [ ] 0x9ac750  CKInputIconNodeFx_IsKindOfClass  [inline]
//   [x] 0x9ac788  CKInputIconNodeFx_GetClassType  [inline]
//   [x] 0x9ac790  CKInputIconNodeFx_GetClassID  [inline]
//   [x] 0x9ac798  CKInputIconNodeFx_GetFxData  [inline]
//   [x] 0x9ac7a0  CKInputIconNodeFx_SetFxData  [inline]
#include "k2000/logic/fx/CKInputIconNodeFx.h"

#include <cmath>

#include "Renderware/rt2d/Rt2dTypes.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwTypes.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/input/KBase628C.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/fx/CKInputIconFxData.h"
#include "k2000/logic/input/CKInputBlockSequential.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/services/CKSrvInput.h"
#include "k2000/system/IKTime.h"

namespace {

// 0x00061bf8 CManager2d_GetFont_maybe (CManager2d::GetFont)
Rt2dFont* CManager2d_GetFont(const CManager2d* manager, uint32_t id) { return manager->GetFont(id); }

// 0x00c50d40 / 0x00c50d64: the shared +y axis and the null vector (zero in the EBOOT's BSS; static initialisers).
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};

// 0x00010690 Math_Sqrtf (fsqrts).
inline float Sqrtf(float x) { return std::sqrt(x); }

CKInputIconFxData* DataOf(const CKInputIconNodeFx* fx) { return static_cast<CKInputIconFxData*>(fx->m_pFxData); }
CGeometry* FirstGeometry(const CKInputIconNodeFx* fx) { return static_cast<CGeometry*>(fx->m_pNode->m_lGeometryList); }

// The icon's size by its distance from the camera (inlined twice in UpdatePlacement): the near size up to the near
// distance, the far size from the far one, linear between. NaN distances keep the near size.
void ScaleByDistance(const CKInputIconFxData* data, float distance, float* sx, float* sy) {
    const float far = data->m_unk28;
    const float near = data->m_unk24;
    if (distance > far || distance == far) {  // fcmpu + cror (gt, eq)
        *sy = data->m_unk20;
        *sx = data->m_unk1c;
        return;
    }
    if (!(distance > near)) return;  // ble
    const float t = (distance - near) / (far - near);
    *sy = ppc::fmadds(t, data->m_unk20 - data->m_unk18, data->m_unk18);
    *sx = ppc::fmadds(t, data->m_unk1c - data->m_unk14, data->m_unk14);
}

// The action block's part (inlined three times in UpdatePlacement): a waiting block (+0x0e) shows the far size; the
// block's vt+0x88 enlarges it by the input service's factor (+0x34).
void ScaleByActionBlock(const CKInputIconNodeFx* fx, const CKInputIconFxData* data, float* sx, float* sy) {
    KBase628C* block = fx->m_pActionBlock;
    if (block == nullptr) return;
    if (block->m_unk0e != 0) {
        *sy = data->m_unk20;
        *sx = data->m_unk1c;
    }
    if (block->Vf88() == 0) return;  // vt+0x88
    const float factor = static_cast<CKSrvInput*>(g_pEngine->m_srvInput)->m_unk34;
    *sy = *sy * factor;
    *sx = *sx * factor;
}

}  // namespace

// 0x001c4a10 CKInputIconNodeFx_Load
int32_t CKInputIconNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    return 1;
}

// 0x009ac798 CKInputIconNodeFx_GetFxData / 0x009ac7a0 CKInputIconNodeFx_SetFxData
IKFxData* CKInputIconNodeFx::GetFxData() { return reinterpret_cast<IKFxData*>(m_pFxData); }
void CKInputIconNodeFx::SetFxData(IKFxData* data) { m_pFxData = reinterpret_cast<IKSerializable*>(data); }

// 0x001c45c8 CKInputIconNodeFx_SetPosition_maybe
void CKInputIconNodeFx::SetPosition(const CVector3* position) {
    const float x = position->x;
    const float z = position->z;
    const float y = position->y;
    m_vPosition.x = x;
    m_vPosition.y = y;
    m_vPosition.z = z;
    const CKInputIconFxData* data = DataOf(this);
    if (data == nullptr) return;
    m_vPosition.x = data->m_unk34.x + x;
    m_vPosition.y = data->m_unk34.y + y;
    m_vPosition.z = data->m_unk34.z + z;
}

// 0x001c4bd8 InputIconFx_UpdateWorldPosition_maybe
void CKInputIconNodeFx::UpdateWorldPosition(const CMatrix34* matrix) {
    const CKInputIconFxData* data = DataOf(this);
    const CVector3* offset = data != nullptr ? &data->m_unk34 : &kNullVector;
    const float ox = offset->x;
    const float oz = offset->z;
    const float oy = offset->y;
    float x = matrix->m_pos.x;
    float z = matrix->m_pos.z;
    float y = matrix->m_pos.y;
    m_vPosition.x = x;
    m_vPosition.z = z;
    m_vPosition.y = y;
    x = ppc::fmadds(ox, matrix->m_right.x, x);
    y = ppc::fmadds(ox, matrix->m_right.y, y);
    z = ppc::fmadds(ox, matrix->m_right.z, z);
    m_vPosition.x = x;
    m_vPosition.z = z;
    m_vPosition.y = y;
    x = ppc::fmadds(oy, matrix->m_up.x, x);
    z = ppc::fmadds(oy, matrix->m_up.z, z);
    y = ppc::fmadds(oy, matrix->m_up.y, y);
    m_vPosition.x = x;
    m_vPosition.z = z;
    m_vPosition.y = y;
    m_vPosition.x = ppc::fmadds(oz, matrix->m_at.x, x);
    m_vPosition.z = ppc::fmadds(oz, matrix->m_at.z, z);
    m_vPosition.y = ppc::fmadds(oz, matrix->m_at.y, y);
}

// 0x001c46c8 CKInputIconNodeFx_ApplyDisplayMode_maybe. On the screen (data +0x30 or +0x33) every geometry gets render
// flag 17 and the screen stage (0x11, or 0x14 with data +0x31, 0x12 with data +0x32) and the node goes under the
// screen scene root (engine +0x10); in the world the stage 0x10 and the dynamic scene root (engine +0x14), or `parent`.
// Bit 5 is set either way; a changed flag 17 reruns the geometry's UpdateProperties (vt+0x60).
void CKInputIconNodeFx::ApplyDisplayMode(IKSerializable* parent) {
    CNode* node = m_pNode;
    uint32_t onScreen = 0;
    uint32_t stage32 = 0;
    uint32_t stage31 = 0;
    CSGBranch* oldParent = node->m_pParent;
    const CKInputIconFxData* data = DataOf(this);
    if (data != nullptr) {
        if (data->m_unk30 != 0 || data->m_unk33 != 0) {
            parent = nullptr;
            onScreen = 1;
        }
        stage32 = data->m_unk32 != 0 ? 1u : 0u;
        stage31 = data->m_unk31 != 0 ? 1u : 0u;
    }
    for (CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList); geometry != nullptr;
         geometry = geometry->m_pNext) {
        uint32_t flags = geometry->m_BitProperties;
        if (((flags >> 17) & 1u) != onScreen) {
            geometry->m_BitProperties = (flags & 0xfffdffffu) | (onScreen << 17);
            geometry->UpdateProperties();  // vt+0x60
            flags = geometry->m_BitProperties;
        }
        if (onScreen == 0) {
            geometry->m_BitProperties = (flags & 0xffffffe0u) | 0x10u;
        } else if (stage32 != 0) {
            geometry->m_BitProperties = (flags & 0xffffffe0u) | 0x12u;
        } else if (stage31 != 0) {
            geometry->m_BitProperties = (flags & 0xffffffe0u) | 0x14u;
        } else {
            geometry->m_BitProperties = (flags & 0xffffffe0u) | 0x11u;
        }
        geometry->m_BitProperties = (geometry->m_BitProperties & 0xffffffdfu) | 0x20u;
    }
    m_pNode->SetFlag10Bit5ResetField20To1(onScreen);  // 0x000cc808
    if (parent != nullptr && parent == oldParent) return;
    if (oldParent != nullptr) oldParent->RemoveChild(m_pNode);  // vt+0x78
    if (parent == nullptr) parent = onScreen != 0 ? g_pEngine->m_secondarySceneRoot : g_pEngine->m_dynamicSceneRoot;
    static_cast<CSGBranch*>(parent)->AddChild(m_pNode);  // vt+0x70
}

// 0x001c4d30 CKInputIconNodeFx_UpdatePlacement_maybe. Three placements:
// - data +0x30 (on the screen at m_vPosition): scaled (x by the camera context's height / width) and put there;
// - data +0x33 (on the screen at the projected m_vPosition): scaled by the camera distance, the projected point in
//   0..1 (y flipped) with z 0;
// - otherwise (or without data) in the world: facing the camera (its -z axis), local to its parent unless that is the
//   dynamic scene root, at m_vPosition pulled toward the camera by data +0x2c, scaled by the distance (pre-concatenated).
void CKInputIconNodeFx::UpdatePlacement() {
    CKInputIconFxData* data = DataOf(this);
    if (data != nullptr && data->m_unk30 != 0) {
        float sx = data->m_unk14;
        float sy = data->m_unk18;
        const float aspect = static_cast<CameraContext*>(g_pEngine->m_cameraContext)->m_fHeightOverWidth;
        ScaleByActionBlock(this, data, &sx, &sy);
        m_pNode->SetScaleXYZ(aspect * sx, sy, 1.0f);  // 0x000d0e60
        RwFrame* frame = m_pNode->m_pRwFrame;
        frame->modelling.pos.z = m_vPosition.z;
        frame->modelling.pos.x = m_vPosition.x;
        frame->modelling.pos.y = m_vPosition.y;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(m_pNode->m_pRwFrame);
        return;
    }
    if (data != nullptr && data->m_unk33 != 0) {
        float sx = data->m_unk14;
        float sy = data->m_unk18;
        const float aspect = static_cast<CameraContext*>(g_pEngine->m_cameraContext)->m_fHeightOverWidth;
        if (sx != data->m_unk1c || sy != data->m_unk20) {
            const CVector3& camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_v3RealPos;
            const float dy = camera.y - m_vPosition.y;
            const float dx = camera.x - m_vPosition.x;
            const float dz = camera.z - m_vPosition.z;
            const float distance = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
            ScaleByDistance(data, distance, &sx, &sy);
        }
        ScaleByActionBlock(this, data, &sx, &sy);
        m_pNode->SetScaleXYZ(aspect * sx, sy, 1.0f);
        const CameraContext* context = g_pEngine->m_graphic->m_renderer->m_cameraContext;
        // BUG(original): without the rasters ProjectWorldPointToScreen writes nothing and the stack is read as it is.
        float screen[2] = {0.0f, 0.0f};
        ProjectWorldPointToScreen(context, reinterpret_cast<const RwV3d*>(&m_vPosition), screen, 1);  // 0x000a30c0
        float width = 0.0f;
        float height = 0.0f;
        const RwRaster* raster = context->m_pFinalColorRaster;
        if (raster != nullptr) {
            height = static_cast<float>(raster->height);
            width = static_cast<float>(raster->width);
        }
        const float y = screen[1] / height;
        RwFrame* frame = m_pNode->m_pRwFrame;
        frame->modelling.pos.z = 0.0f;  // stw 0
        frame->modelling.pos.x = screen[0] / width;
        frame->modelling.pos.y = 1.0f - y;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(m_pNode->m_pRwFrame);
        return;
    }
    CKSrvCamera* cameraService = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    const CVector3& camera = cameraService->m_v3RealPos;
    const CVector3 at = {-cameraService->m_v3RealAxisZ.x, -cameraService->m_v3RealAxisZ.y, -cameraService->m_v3RealAxisZ.z};
    m_pNode->SetOrientationFromAtUp(&at, &kAxisY);  // 0x000d0918
    CSGBranch* parent = m_pNode->m_pParent;
    if (static_cast<IKSerializable*>(parent) != g_pEngine->m_dynamicSceneRoot) {
        parent->ForceWorldMatrixUpdate();  // vt+0x50
        CMatrix34 local;
        Mat4_Invert(&local, reinterpret_cast<const CMatrix34*>(&parent->m_pRwFrame->ltm));
        Mat4_TransformPreConcat(&local, reinterpret_cast<const CMatrix34*>(&m_pNode->m_pRwFrame->modelling));
        m_pNode->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&local));  // 0x000d0be8
    }
    RwFrame* frame = m_pNode->m_pRwFrame;
    frame->modelling.pos.z = m_vPosition.z;
    frame->modelling.pos.x = m_vPosition.x;
    frame->modelling.pos.y = m_vPosition.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(m_pNode->m_pRwFrame);
    m_pNode->ForceWorldMatrixUpdate();  // vt+0x50
    const float pz = m_vPosition.z;
    const float px = m_vPosition.x;
    const float py = m_vPosition.y;
    const RwV3d* world = &m_pNode->m_pRwFrame->ltm.pos;
    float dy = camera.y - world->y;
    float dx = camera.x - world->x;
    float dz = camera.z - world->z;
    const float length = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        dz = dz * inverse;
        dx = dx * inverse;
        dy = dy * inverse;
    }
    // BUG(original): data +0x2c is read without the data test (the world placement is also the one without data).
    const float pull = data->m_unk2c;
    frame = m_pNode->m_pRwFrame;
    frame->modelling.pos.z = ppc::fmadds(pull, dz, pz);
    frame->modelling.pos.x = ppc::fmadds(pull, dx, px);
    frame->modelling.pos.y = ppc::fmadds(pull, dy, py);
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(m_pNode->m_pRwFrame);
    m_pNode->ForceWorldMatrixUpdate();
    data = DataOf(this);
    float sx = data->m_unk14;
    float sy = data->m_unk18;
    if (sx != data->m_unk1c || sy != data->m_unk20) {
        const RwV3d* moved = &m_pNode->m_pRwFrame->ltm.pos;
        const float ey = camera.y - moved->y;
        const float ex = camera.x - moved->x;
        const float ez = camera.z - moved->z;
        const float distance = Sqrtf(ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, ey * ey)));
        ScaleByDistance(data, distance, &sx, &sy);
    }
    ScaleByActionBlock(this, data, &sx, &sy);
    m_pNode->ScaleXYZ(sx, sy, 1.0f);  // 0x000d0d28
}

// 0x001c5da8 CKInputIconNodeFx_SetAlpha_maybe (C2.8 sequence). The translucent bit is "the alpha byte is not 0xff",
// taken after 0xff became 0xfe (so always set), unless the opaque material case below.
void CKInputIconNodeFx::SetAlpha(uint8_t alpha) {
    int32_t value = alpha;
    if (value == 0xff) value = -2;
    CGeometry* geometry = FirstGeometry(this);
    uint32_t translucent = (~static_cast<uint32_t>(value) & 0xffu) != 0 ? 1u : 0u;
    if ((geometry->m_BitProperties & 0x1000u) != 0) {
        const int32_t mode = static_cast<int32_t>((static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu);
        if (mode > 0 && mode <= 6) {
            translucent = 0;
            value = -1;
        }
    }
    geometry->m_cGeometryColor[3] = static_cast<uint8_t>(value);
    const uint32_t flags = geometry->m_BitProperties;
    if (((flags >> 11) & 1u) == translucent) return;
    geometry->m_BitProperties = (flags & 0xfffff7ffu) | (translucent << 11);
    geometry->UpdateProperties();  // vt+0x60
}

// 0x001c5a88 CKInputIconNodeFx_Start. The geometry's alpha: opaque (0xff, render flag 11 clear) for a material of modes
// 1..6 with render flag 12, else 0xfe with flag 11 set (UpdateProperties when it changes); the material's bits 0 and 1
// set. The run-time state reset, the position the data's offset, then placed and hidden (Update shows it); bit 2 of the
// effect flags cleared.
void CKInputIconNodeFx::Vf64() {
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfe);
    CGeometry* geometry = FirstGeometry(this);
    uint32_t translucent = 1;
    uint8_t alpha = 0xfe;
    if ((geometry->m_BitProperties & 0x1000u) != 0) {
        const uint32_t mode = (static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu;
        if (mode > 0 && mode <= 6) {
            translucent = 0;
            alpha = 0xff;
        }
    }
    geometry->m_cGeometryColor[3] = alpha;
    const uint32_t flags = geometry->m_BitProperties;
    if (((flags >> 11) & 1u) != translucent) {
        geometry->m_BitProperties = (flags & 0xfffff7ffu) | (translucent << 11);
        geometry->UpdateProperties();  // vt+0x60
    }
    CMaterial* material = static_cast<CMaterial*>(geometry->m_pMaterial);
    material->m_baProperties = (material->m_baProperties & 0xfffffffeu) | 1u;
    material->m_baProperties = (material->m_baProperties & 0xfffffffdu) | 2u;
    m_pActionBlock = nullptr;
    m_i32Config = -1;
    m_fBlinkTimer = 0.0f;
    m_i32BlinkPhase = 0;
    m_pInputBlocks = nullptr;
    m_i32BlockId = -1;
    m_vPosition.x = 0.0f;
    m_vPosition.y = 0.0f;
    m_vPosition.z = 0.0f;
    const CKInputIconFxData* data = DataOf(this);
    if (data != nullptr) {
        m_vPosition.x = data->m_unk34.x + 0.0f;
        m_vPosition.y = data->m_unk34.y + 0.0f;
        m_vPosition.z = data->m_unk34.z + 0.0f;
    }
    ApplyDisplayMode(nullptr);
    UpdatePlacement();
    Vf60();  // vt+0x60 HideSceneNode
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfb);
}

// 0x001c4968 CKInputIconNodeFx_Stop: stopped, back in the world, hidden, no data.
void CKInputIconNodeFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfe) | 1);
    ApplyDisplayMode(nullptr);
    Vf60();  // vt+0x60
    m_pFxData = nullptr;
}

// 0x001c4588 CKInputIconNodeFx_OnPause
void CKInputIconNodeFx::Vf70() { Vf60(); }

// 0x001c44d0 CKInputIconNodeFx_StopIfLinkedTo: a running effect whose node's parent is in `sector` stops (vt+0x6c).
void CKInputIconNodeFx::StopIfLinkedTo(int32_t sector) {
    if ((m_baFxData & 1) != 0 || sector == 0) return;
    if (static_cast<int32_t>(m_pNode->m_pParent->GetSectorIndex()) != sector) return;  // vt+0x6c
    Stop();
}

// 0x001c5558 CKInputIconNodeFx_Update. The blink timer advances by the clock's third delta. The material shows the
// data's texture (full UV), or the font glyph of the button: an input block sequence's action block (blinking between
// two glyphs every 0.25 s while it waits, the next glyph once done) or the data's input sequence (its action through the
// game manager's vt+0x174). No font or no input sequence: hidden. Then placed, and shown unless bit 2 is set.
void CKInputIconNodeFx::Update(IKTime* frameClock) {
    CKInput* input = g_pEngine->m_input;
    uint16_t glyph = 0x3f;
    m_fBlinkTimer = m_fBlinkTimer + frameClock->m_afDeltaTime[2];
    CKInputIconFxData* data = DataOf(this);
    RwTexture* texture = static_cast<RwTexture*>(data->m_pTexture);
    if (texture != nullptr) {
        CMaterial* material = static_cast<CMaterial*>(FirstGeometry(this)->m_pMaterial);
        material->SetTexture(texture);  // 0x000bc238
        CMatrix34* uv = material->GetUVTransformMatrix();  // 0x000bb9f8
        uv->m_at.z = 1.0f;
        uv->m_pos.z = 0.0f;
        uv->m_ui32Flags = 2;
        uv->m_right.x = 1.0f;
        uv->m_right.y = 0.0f;
        uv->m_right.z = 0.0f;
        uv->m_up.x = 0.0f;
        uv->m_up.y = 1.0f;
        uv->m_up.z = 0.0f;
        uv->m_at.x = 0.0f;
        uv->m_at.y = 0.0f;
        uv->m_pos.x = 0.0f;
        uv->m_pos.y = 0.0f;
    } else {
        Rt2dFont* font = CManager2d_GetFont(g_pEngine->m_manager2d, static_cast<uint32_t>(data->m_unk08));
        if (font == nullptr) {
            Vf60();  // vt+0x60
            return;
        }
        m_pActionBlock = nullptr;  // (data +0x40, null here)
        if (m_pInputBlocks != nullptr) {
            if (m_i32BlockId == -1) {
                m_pActionBlock = static_cast<KBase628C*>(m_pInputBlocks->GetActiveActionBlock(&glyph));  // 0x002054b0
            } else {
                m_pActionBlock = m_pInputBlocks->FindActionBlockById(m_i32BlockId, &glyph);  // 0x002052e0
            }
            if (glyph != 0x3f) {
                if (m_pActionBlock->Vf7C() != 0) {  // vt+0x7c
                    int32_t phase;
                    if (!(m_fBlinkTimer > 0.25f)) {
                        phase = m_i32BlinkPhase;
                    } else {
                        phase = 1 - m_i32BlinkPhase;
                        m_fBlinkTimer = 0.0f;  // stw 0
                        m_i32BlinkPhase = phase;
                    }
                    glyph = static_cast<uint16_t>(phase + glyph);
                } else if (m_pActionBlock->VfBC() != 0 || m_pActionBlock->Vf84() != 0) {  // vt+0xbc, vt+0x84
                    glyph = static_cast<uint16_t>(glyph + 1);
                }
            }
        } else {
            const InputSequenceEntry* entry = input->FindButtonIconGlyph(data->m_unk0c);  // 0x00105960
            if (entry == nullptr) {
                Vf60();
                return;
            }
            const int32_t config = m_i32Config != -1 ? m_i32Config : static_cast<int32_t>(data->m_unk10);
            const uint32_t action = g_pEngine->m_gameManager->GetIconAction(config, entry->m_unk00, entry->m_unk04,
                                                                            entry->m_unk08);  // vt+0x174
            glyph = input->GetActionButtonGlyph(entry->m_unk00, entry->m_unk04, action, entry->m_unk0c, 0);  // 0x00109ee8
        }
        // The glyph decoded as the font reads a string: two bytes with flag bit 1, else its first (high) byte.
        uint32_t c = (font->flag & 2u) != 0 ? glyph : static_cast<uint32_t>(glyph >> 8);
        const rt2dCharRect* rects = nullptr;
        if (font->charMap->numElementsFilled != 0) rects = reinterpret_cast<const rt2dCharRect*>(font->charMap->listElements);
        int32_t index = -1;
        if (static_cast<int32_t>(c) <= 0x7f) {
            index = font->aCharIndex[c];
        } else {
            const int32_t i = static_cast<int32_t>(c) - font->uCharOffset;
            if (i >= 0 && i < font->uCharIndexCount) index = font->uCharIndex[i];
        }
        CMaterial* material = static_cast<CMaterial*>(FirstGeometry(this)->m_pMaterial);
        // BUG(original): with an empty character map the rectangle is index x 0x20 from address 0 (only index 0 gives
        // null); the font's maps are never empty here.
        const rt2dCharRect* rect = (index >= 0 && rects != nullptr) ? rects + index : nullptr;
        if (rect == nullptr) {
            material->SetTexture(nullptr);
        } else {
            material->SetTexture(rect->tex);
            CMatrix34* uv = material->GetUVTransformMatrix();
            const float u0 = rect->uv[0].x;
            const float v0 = rect->uv[0].y;
            const float v1 = rect->uv[1].y;
            const float u1 = rect->uv[1].x;
            uv->m_ui32Flags = 2;
            uv->m_at.z = 1.0f;
            uv->m_right.y = 0.0f;
            uv->m_right.z = 0.0f;
            uv->m_up.x = 0.0f;
            uv->m_up.z = 0.0f;
            uv->m_at.x = 0.0f;
            uv->m_up.y = v1 - v0;
            uv->m_right.x = u1 - u0;
            uv->m_at.y = 0.0f;
            uv->m_pos.y = rect->uv[0].y;
            uv->m_pos.x = rect->uv[0].x;
            uv->m_pos.z = 0.0f;
        }
    }
    UpdatePlacement();
    if ((m_baFxData & 4) != 0) return;
    Vf5C();  // vt+0x5c ShowSceneNode
}

// 0x001c4a60 CKInputIconNodeFx_RecursiveRegistration: IKNodeFx's (0x1d88c0 CKNodeFx3d_LevelReset): the
// node's registration (its vt+0x24) when there is one.
void CKInputIconNodeFx::RecursiveRegistration(int32_t type) {
    IKNodeFx::RecursiveRegistration(type);
}
