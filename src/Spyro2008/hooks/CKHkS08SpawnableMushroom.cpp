// CKHkS08SpawnableMushroom.cpp - reconstructed original translation unit 0x4d8018-0x4da838 (GAME_TOC1, main_toc1), 36 functions, 33 live.
// Primary class: CKHkS08SpawnableMushroom  key 0x3342  category Hook  size 0x60  vtable 0xb2a168
// Other owners: CKHkS08Fire (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4d8018  CKHkS08SpawnableMushroom_Delete
//   [x] 0x4d8068  CKHkS08SpawnableMushroom_Restart  (empty: IKHook's, inherited)
//   [x] 0x4d8070  CKHkS08SpawnableMushroom_Pause  (empty: IKHook's, inherited)
//   [x] 0x4d8078  CKHkS08SpawnableMushroom_Resume  (empty: IKHook's, inherited)
//   [ ] 0x4d8080  FUN_004d8080  [dead]
//   [x] 0x4d8230  CKHkS08SpawnableMushroom_vfF0
//   [x] 0x4d8240  CKHkS08SpawnableMushroom_MessageProc
//   [x] 0x4d8298  CKHkS08SpawnableMushroom_FaceTowards_maybe
//   [x] 0x4d8440  CKHkS08SpawnableMushroom_Stop
//   [x] 0x4d8468  CKHkS08SpawnableMushroom_Start
//   [x] 0x4d8490  CKHkS08SpawnableMushroom_PostLoad
//   [ ] 0x4d84f8  CKHkS08SpawnableMushroom_Save
//   [x] 0x4d8520  CKHkS08SpawnableMushroom_RecursiveRegistration  (KBase42C2's 0x445bf0 = IKHook's: inherited)
//   [x] 0x4d8548  CKHkS08SpawnableMushroom_Destroy
//   [ ] 0x4d8590  CKHkS08SpawnableMushroom_Construct_2  [dead]
//   [x] 0x4d8600  CKHkS08SpawnableMushroom_DeleteArray
//   [x] 0x4d86b0  CKHkS08SpawnableMushroom_Destructor_2  (the destructor 0x4d92b0's body)
//   [ ] 0x4d8730  RegisterCKHkS08SpawnableMushroomClass
//   [ ] 0x4d87b8  _GLOBAL__D_4d87b8
//   [ ] 0x4d87c8  _GLOBAL__I_4d87c8
//   [x] 0x4d87d8  CKHkS08SpawnableMushroom_AttachSounds  (KGLObjectAttached, vt+0xb4: no live caller)
//   [x] 0x4d8968  CKHkS08SpawnableMushroom_vf98
//   [x] 0x4d89b0  CKHkS08SpawnableMushroom_Construct
//   [x] 0x4d8a20  CKHkS08SpawnableMushroom_Destroy_maybe
//   [x] 0x4d9088  CKHkS08SpawnableMushroom_Create
//   [x] 0x4d9110  CKHkS08SpawnableMushroom_CreateArray
//   [x] 0x4d9220  CKHkS08SpawnableMushroom_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x4d92b0  CKHkS08SpawnableMushroom_Destructor
//   [x] 0x4d9330  CKHkS08SpawnableMushroom_vf94
//   [x] 0x4d9a98  CKHkS08SpawnableMushroom_Load
//   [x] 0x4d9cd8  CKHkS08SpawnableMushroom_ApplyDamage_maybe
//   [x] 0x4da360  CKHkS08SpawnableMushroom_ProcessDamageContacts_maybe
//   [x] 0x4da698  CKHkS08SpawnableMushroom_Update
//   [x] 0x4da7a0  CKHkS08Fire_Delete  (DOTD_DECLARE_FACTORIES, CKHkS08Fire.h)
//   [x] 0x4da7f0  CKHkS08Fire_vfC8  (ApplyStatePreset, CKHkS08Fire.h)
//   [ ] 0x4da818  FUN_004da818  [dead]
//
//   [ ] 0x9c61e0  CKHkS08SpawnableMushroom_IsKindOfClass  [inline]
//   [ ] 0x9c6240  CKHkS08SpawnableMushroom_GetClassType  [inline]
//   [ ] 0x9c6248  CKHkS08SpawnableMushroom_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08SpawnableMushroom.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvBeacon.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/misc/Engine.h"
#include "k2000/math/Math.h"
#include "k2000/core/Stub.h"
#include "Spyro2008/groups/CKGrpS08SpawnableMushroom.h"
#include "Renderware/rwcore/RwCamera.h"
#include "crt/xsinf.h"
#include <cstring>

#include "k2000/io/IKFile.h"
#include "k2000/misc/Mat4.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "k2000/components/CKQuakeCpntUpdater.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/logic/CKDamage.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include <cmath>

// 0x004d9a98 CKHkS08SpawnableMushroom_Load
int32_t CKHkS08SpawnableMushroom::Load(IKFile* file, int32_t type) {
    KBase42C2::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pUnk4C);
    IKFile_ReadRef(file, &m_pUnk54);
    IKFile_ReadRef(file, &m_pUnk50);
    IKFile_ReadRef(file, &m_pUnk5C);
    return 1;
}

// 0x004d8490 CKHkS08SpawnableMushroom_PostLoad: KBase42C2's part (0x445a68), then for the level type the two
// RwMatrix, +0x48 first.
int32_t CKHkS08SpawnableMushroom::PostLoad(int32_t type) {
    KBase42C2::PostLoad(type);
    if (type == K_LEVEL_PLATEFORMS) {
        m_pUnk48 = RwMatrixCreate_Thunk();
        m_pUnk44 = RwMatrixCreate_Thunk();
    }
    return 1;
}

// 0x004d8468 CKHkS08SpawnableMushroom_Start
void CKHkS08SpawnableMushroom::Start() {
    KBase42C2::Start();  // 0x445c70
}

namespace {
bool SignBitSet(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, sizeof bits);
    return (bits & 0x80000000u) != 0;
}
// The inlined sinf / cosf with the library call for a negative angle (as CKCameraClassicTrack3's GameSinf).
float GameSinf(float x) { return SignBitSet(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }
float GameCosf(float x) { return SignBitSet(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }
}  // namespace

// 0x004d9330 CKHkS08SpawnableMushroom_vf94
void CKHkS08SpawnableMushroom::Vf94() {
    KBase42C2::Vf94();  // 0x00445c48
    CKSrvBeacon* beacons = static_cast<CKSrvBeacon*>(g_pEngine->m_srvBeacon);
    const uint8_t* beacon = beacons->GetBeaconData(m_aUnk28);
    int16_t xyz[3] = {0, 0, 0};
    int8_t yawByte = 0;
    if (beacon != nullptr) {
        std::memcpy(xyz, beacon, sizeof xyz);
        yawByte = static_cast<int8_t>(beacon[6]);
    }
    const float yaw = static_cast<float>(static_cast<double>(yawByte)) * 3.14159274f * 0.0078125f;  // TOC +0x6bf4 / +0x6bf8
    const CVector3 forward{GameSinf(yaw), 0.0f, GameCosf(yaw)};
    float variant = 0.0f;
    const CKSrvBeacon::CKBeaconSet* set = beacons->GetBeaconSet(m_aUnk28);
    if (beacons->m_aBeaconSectors[m_aUnk28[0]].m_apBeaconKlusters != nullptr && set != nullptr) {
        const uint8_t* bits = beacons->m_aBeaconSectors[m_aUnk28[0]].m_bavPersistent.m_p8Bits;
        const uint32_t base = static_cast<uint32_t>(set->m_aui16Accessor[3]) + 1u +
                              static_cast<uint32_t>(set->m_ui8PersistentSizeBits) * m_aUnk28[3];
        uint32_t v = 0;
        for (uint32_t b = 0; b < 8; ++b) {
            if (((bits[(base + b) >> 3] >> ((base + b) & 7)) & 1u) != 0) v += 1u << b;
        }
        variant = static_cast<float>(static_cast<double>(v));
    }
    m_fHitPoints = variant;
    CSGLeaf* child = static_cast<CSGLeaf*>(m_pUnk4C);
    child->m_sgProperties &= ~4u;
    static_cast<CSGMovable*>(m_pUnk4C)->SetIdentity();  // 0x000d08f0
    CSGMovable* node = static_cast<CSGMovable*>(m_pKGLObject);
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.x = static_cast<float>(static_cast<double>(xyz[0])) * 0.1f;  // TOC +0x6bfc
    frame->modelling.pos.y = static_cast<float>(static_cast<double>(xyz[1])) * 0.1f;
    frame->modelling.pos.z = static_cast<float>(static_cast<double>(xyz[2])) * 0.1f;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(node->m_pRwFrame);  // 0x00010698
    const CVector3 up{0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC +0x6b90)
    node->SetBasisFromUpAndForward(&up, &forward);  // 0x000d0a30
    IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_pUnk54);
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->EnableVolume(volume);  // 0x00192090
    RwFrame* vf = volume->m_pRwFrame;
    vf->modelling.pos.y = static_cast<CKGrpS08SpawnableMushroom*>(m_pUnk30)->m_unk80;
    vf->modelling.pos.z = 0.0f;
    vf->modelling.pos.x = 0.0f;
    vf->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(volume->m_pRwFrame);
    m_bitArray = ((m_bitArray & ~8u) | 8u) & ~0x10u;
    std::memcpy(m_pUnk48, &static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->modelling, sizeof(RwMatrix));
}

// 0x004d8968 CKHkS08SpawnableMushroom_vf98
void CKHkS08SpawnableMushroom::Vf98() {
    KBase42C2::Vf98();  // 0x00445c18
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->DisableVolume(static_cast<IKBoundingVolume*>(m_pUnk54));  // 0x001920e8
}

// 0x004d87d8 CKHkS08SpawnableMushroom_AttachSounds (the node argument is not read: the hook's node +0x1c serves)
void CKHkS08SpawnableMushroom::KGLObjectAttached(IKSerializable* /*node*/) {
    CSGBranch* node = static_cast<CSGBranch*>(m_pKGLObject);
    CSGLeaf* child = static_cast<CSGLeaf*>(m_pUnk4C);
    if (child->m_pParent != nullptr) child->m_pParent->RemoveChild(child);  // vt+0x78
    node->AddChild(child);                                                  // vt+0x70
    CSGLeaf* volume = static_cast<CSGLeaf*>(m_pUnk54);
    if (volume != nullptr) {
        if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);
        node->AddChild(volume);
    }
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pUnk50);
    if (sounds->GetSound(0) != nullptr) sounds->GetSound(0)->SetAttachObject(m_pKGLObject);  // 0x00112bc0, 0x00111350
    if (sounds->GetSound(1) != nullptr) sounds->GetSound(1)->SetAttachObject(m_pKGLObject);
}

// 0x004da698 CKHkS08SpawnableMushroom_Update. (KStub_Nop_445990, KBase42C2's update, comes first: empty.)
void CKHkS08SpawnableMushroom::Update(IKTime* clock) {
    static_cast<CSGLeaf*>(m_pUnk4C)->m_sgProperties &= ~4u;
    ProcessDamageContacts();                 // 0x004da360
    ContactHistory_Update(&m_unk58, clock);  // 0x005833c0
    CKQuakeCpntUpdater* quake = static_cast<CKQuakeCpntUpdater*>(m_pUnk5C);
    if (quake->m_bRunning != 0) {
        float out[15];
        quake->EvaluateScaled(clock->m_afDeltaTime[0], 1.0f, out);  // 0x0024f5c8, TOC +0x6b8c
        CMatrix34 shake;
        ShakeSample_BuildMatrix(quake, out, &shake, static_cast<const CMatrix34*>(m_pUnk44));  // 0x0024ee90
        Mat4_TransformPostConcat(&shake, static_cast<const CMatrix34*>(m_pUnk48));              // 0x0023f760
        static_cast<CSGMovable*>(m_pKGLObject)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&shake));  // 0x000d0be8
    }
}

namespace {
const float kNoTouchTime = -1000.0f;  // TOC +0x6c08 (both times of ContactHistory_Touch)

// The beacon's persistent bits of this mushroom (CKSrvBeacon sector +0x28) and its first bit: the set's first bit (+0x1a)
// plus the set's bits per beacon (+0x11) times the beacon index (+0x2e). Null without klusters. BUG(original): a slot whose
// set index is -1 reads a null set.
uint8_t* PersistentBits(const uint16_t* slot, uint32_t* first) {
    CKSrvBeacon* beacons = static_cast<CKSrvBeacon*>(g_pEngine->m_srvBeacon);
    CKSrvBeacon::CKBeaconSector& sector = beacons->m_aBeaconSectors[slot[0]];
    if (sector.m_apBeaconKlusters == nullptr) return nullptr;
    const CKSrvBeacon::CKBeaconSet* set = beacons->GetBeaconSet(slot);
    *first = static_cast<uint32_t>(set->m_aui16Accessor[3]) +
             static_cast<uint32_t>(set->m_ui8PersistentSizeBits) * slot[3];
    return sector.m_bavPersistent.m_p8Bits;
}

// One bit cleared, then the value's low bit or-ed in (the original's two byte stores).
void WriteBit(uint8_t* bits, uint32_t index, uint32_t value) {
    const uint32_t shift = index & 7u;
    bits[index >> 3] = static_cast<uint8_t>(bits[index >> 3] & ~(1u << shift));
    bits[index >> 3] = static_cast<uint8_t>(bits[index >> 3] | ((value & 1u) << shift));
}
}  // namespace

// 0x004da360 CKHkS08SpawnableMushroom_ProcessDamageContacts_maybe. The hit points and the amount are tested with ble (a NaN
// goes on).
void CKHkS08SpawnableMushroom::ProcessDamageContacts() {
    ICollision* collision = static_cast<ICollision*>(static_cast<IKBoundingVolume*>(m_pUnk54)->m_CollisionResList);
    if (collision == nullptr || m_fHitPoints <= 0.0f) return;  // TOC +0x6b74
    for (;;) {
        IKBoundingVolume* other = static_cast<IKBoundingVolume*>(collision->GetBoundingVolume1());  // vt+0x00
        if (other->m_pOwner == this) {
            other = static_cast<IKBoundingVolume*>(collision->GetBoundingVolume2());  // vt+0x04
        } else {
            collision->GetBoundingVolume2();  // called, its answer unused
        }
        if (other->m_ui8OwnerType == 3 && (other->m_ui16PropertiesFlags & 0xcu) != 0) {
            const uint8_t touched = ContactHistory_Touch(kNoTouchTime, kNoTouchTime, &m_unk58, other, nullptr);  // 0x005830f8
            CKDamage* damage = static_cast<CKDamage*>(other->m_unk1c);
            if (damage != nullptr) {
                bool apply = false;
                float amount = 0.0f;
                const float dt = g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[0];  // +0x48 -> +0x04 -> +0x1c
                if (damage->IsKindOfClass(0x998c) != 0) {  // vt+0x08 CKS08HeroDamage
                    if (touched != 0) {
                        apply = true;
                        amount = damage->m_unk0c != 0 ? dt * damage->m_unk04 : damage->m_unk04;
                    }
                } else if (damage->IsKindOfClass(0x99cc) != 0 || damage->IsKindOfClass(0x970c) != 0) {
                    if (damage->m_unk0c != 0) {
                        apply = true;
                        amount = dt * damage->m_unk04;
                    } else if (touched != 0) {
                        apply = true;
                        amount = damage->m_unk04;
                    }
                }
                if (apply && !(amount <= 0.0f)) {
                    const CVector3 point = *collision->GetWorldContactPoint();  // vt+0x20
                    ApplyDamage(amount, &point, touched);                      // 0x004d9cd8
                }
            }
        }
        collision = collision->m_pNext;
        if (collision == nullptr || m_fHitPoints <= 0.0f) return;
    }
}

// 0x004d9cd8 CKHkS08SpawnableMushroom_ApplyDamage_maybe (r4 is not read).
void CKHkS08SpawnableMushroom::ApplyDamage(float amount, const CVector3* point, uint8_t touched) {
    CKGrpS08SpawnableMushroom* group = static_cast<CKGrpS08SpawnableMushroom*>(m_pUnk30);
    if (touched != 0) {
        CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pUnk50);
        if (sounds->GetSound(0) != nullptr) sounds->GetSound(0)->Play(0.0f);  // 0x00112bc0, 0x00111230 (TOC +0x6b74)
        const CVector3 at = *point;
        FaceTowards(&at);  // 0x004d8298
        IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(group->m_pUnk6c), this);  // inlined
        if (fx != nullptr) {
            CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
            explosion->SetTranslation(point, this);  // 0x001b66e8
            explosion->Trigger(this, 0);             // 0x001b82a8
            explosion->ReleaseReservation(this);     // vt+0x54
        }
    }
    m_fHitPoints = m_fHitPoints - amount;
    if (m_fHitPoints <= 0.0f) {  // cror lt|eq: a NaN keeps the mushroom
        m_fHitPoints = 0.0f;
        DestroyMushroom();  // 0x004d8a20
        return;
    }
    const uint32_t value = static_cast<uint32_t>(ppc::fctiwz(m_fHitPoints)) & 0xffu;  // fctiwz, the word's last byte
    uint32_t first = 0;
    uint8_t* bits = PersistentBits(m_aUnk28, &first);
    if (bits == nullptr) return;
    for (uint32_t b = 0; b < 8; ++b) WriteBit(bits, first + 1 + b, value >> b);
}

// 0x004d8298 CKHkS08SpawnableMushroom_FaceTowards_maybe
void CKHkS08SpawnableMushroom::FaceTowards(const CVector3* point) {
    const RwMatrix* ltm = &static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->ltm;
    CVector3 dir = {point->x - ltm->pos.x, 0.0f, point->z - ltm->pos.z};
    if (dir.x == 0.0f && dir.z == 0.0f) {
        dir = {1.0f, 0.0f, 0.0f};  // TOC +0x6b88: 0x00c50d34, the X axis
    } else {
        const float length = std::sqrt(ppc::fmadds(dir.z, dir.z, ppc::fmadds(dir.x, dir.x, 0.0f)));  // 0x00010690
        if (length != 0.0f) {
            const float inv = 1.0f / length;  // TOC +0x6b8c
            dir = {dir.x * inv, dir.y * inv, dir.z * inv};
        }
    }
    CMatrix34* face = static_cast<CMatrix34*>(m_pUnk44);
    face->m_pos = {0.0f, 0.0f, 0.0f};
    face->m_up.x = 0.0f;
    face->m_right.z = 0.0f;
    face->m_right.y = 0.0f;
    face->m_at.y = 0.0f;
    face->m_at.x = 0.0f;
    face->m_up.z = 0.0f;
    face->m_ui32Flags = 0x20003u;
    face->m_right.x = 1.0f;
    face->m_at.z = 1.0f;
    face->m_up.y = 1.0f;
    const CVector3 up = {0.0f, 1.0f, 0.0f};  // TOC +0x6b90: 0x00c50d40
    Mat4_SetBasisFromAtUp(face, &dir, &up);  // 0x0023fd30
    CMatrix34 inverse;
    Mat4_Invert(&inverse, reinterpret_cast<const CMatrix34*>(&static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->modelling));  // 0x0023f878
    Mat4_TransformPostConcat(face, &inverse);  // 0x0023f760
    static_cast<CKQuakeCpntUpdater*>(m_pUnk5C)->Start();  // 0x0024f770
}

// 0x004d8a20 CKHkS08SpawnableMushroom_Destroy_maybe
void CKHkS08SpawnableMushroom::DestroyMushroom() {
    CKGrpS08SpawnableMushroom* group = static_cast<CKGrpS08SpawnableMushroom*>(m_pUnk30);
    uint32_t first = 0;
    uint8_t* bits = PersistentBits(m_aUnk28, &first);
    if (bits != nullptr) {
        for (uint32_t b = 0; b < 8; ++b) WriteBit(bits, first + 1 + b, 0);  // the hit points
    }
    bits = PersistentBits(m_aUnk28, &first);
    if (bits != nullptr) WriteBit(bits, first, 1);  // picked
    const RwMatrix& modelling = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->modelling;
    CVector3 at = {modelling.pos.x, modelling.pos.y + group->m_unk80, modelling.pos.z};
    const CVector3 up = {0.0f, 1.0f, 0.0f};  // 0x00c50d40
    static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->SpawnGemReward(group->m_unk78, &at, &up);  // 0x004f8618
    static_cast<CSGLeaf*>(m_pUnk4C)->m_sgProperties = (static_cast<CSGLeaf*>(m_pUnk4C)->m_sgProperties & ~4u) | 4u;
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pUnk50);
    if (sounds->GetSound(1) != nullptr) sounds->GetSound(1)->Play(0.0f);  // 0x00112bc0, 0x00111230
    IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(group->m_pUnk70), this);  // inlined
    if (fx != nullptr) {
        CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
        explosion->SetTranslation(&at, this);  // 0x001b66e8
        explosion->Trigger(this, 0);           // 0x001b82a8
        explosion->ReleaseReservation(this);   // vt+0x54
    }
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->RemoveVolume(static_cast<IKBoundingVolume*>(m_pUnk54));  // 0x00192bc0
    static_cast<CKQuakeCpntUpdater*>(m_pUnk5C)->Stop();  // 0x0024f738
    group->ReleaseMember(this);  // 0x00443bf0
}

// 0x004d8548 CKHkS08SpawnableMushroom_Destroy (the pointers are kept, as in the original)
void CKHkS08SpawnableMushroom::Destroy() {
    RwMatrixDestroy_Thunk(static_cast<CMatrix34*>(m_pUnk48));
    RwMatrixDestroy_Thunk(static_cast<CMatrix34*>(m_pUnk44));
}

// 0x004d92b0 CKHkS08SpawnableMushroom_Destructor
CKHkS08SpawnableMushroom::~CKHkS08SpawnableMushroom() {
    for (ContactHistoryNode* node = m_unk58; node != nullptr;) {
        ContactHistoryNode* next = node->m_pNext;  // +0x14
        ContactHistory_FreeNode(node);
        node = next;
    }
    m_unk58 = nullptr;
}
