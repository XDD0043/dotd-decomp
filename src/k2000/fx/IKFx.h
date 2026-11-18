// IKFx.h - the base of the effects (key 0x154c, not registered). XXL2: K/KServices/KServiceFx/Effects/
// IKFx.h, members m_pOwner and m_baFxData, plus DotD's flag at +0x04. IKFx_Load (0x1d8320), IKFx_Save
// and IKFx_ResetRuntimeFlags sit in the checklist of logic/fx/CKTimeScalingNodeFx.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class IKFxData;
class IKTime;

class IKFx : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x55)

    IKFx() {}  // no stores of its own (CKNodeFx3d_ConstructBase 0x1d8898 sets only IKNodeFx's)
    ~IKFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d8320 IKFx_Load

    // The effects' runtime slots. The bodies are IKNodeFx's defaults (vtable 0xb1ddf8); IKNode2dFx and the
    // effect classes override some of them with their own code, most of which is not ported yet (their Stop,
    // vt+0x6c, are listed in the C2.2 svc report). m_baFxData: bit 0 stopped, bit 1 reserved.
    virtual int32_t ResetRuntimeFlags() {  // vt+0x50 0x001d8310 IKFx_ResetRuntimeFlags
        m_bUpdateWhenPaused = 0;
        return 1;
    }
    // vt+0x54 0x009ab620 CKNodeFx3d_ReleaseReservation: when reserved by `owner`, the reservation (bit 1) and the
    // owner cleared.
    virtual void ReleaseReservation(const IKSerializable* owner) {
        if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
        m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfdu);
        m_pOwner = nullptr;
    }
    // vt+0x58 0x009ab580 CKNodeFx3d_StopAndRelease: when reserved by `owner`, the reservation cleared, the effect
    // stopped (vt+0x6c) and the owner cleared.
    virtual void StopAndRelease(const IKSerializable* owner) {
        if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
        m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfdu);
        Stop();
        m_pOwner = nullptr;
    }
    // vt+0x5c ShowSceneNode / vt+0x60 HideSceneNode: the effect's node shown or hidden. Both bases define them
    // (IKNodeFx 0x1d8918 / 0x1d8b18: the 3D node's hidden flag; IKNode2dFx 0x1d8570 / 0x1d8808: the 2D node added
    // to or taken off the manager's scene +0xa68); no effect class overrides them.
    // DOTD: the names stay Vf5C / Vf60 / Vf64 until every caller is renamed (ShowSceneNode / HideSceneNode / Start).
    virtual void Vf5C() = 0;
    virtual void Vf60() = 0;
    // vt+0x64 0x009ada60 CKNodeFx3d_Start [inline]: running (the stopped bit 0 cleared). IKNode2dFx's is 0x9ad9a0;
    // most effect classes override it with their own start.
    virtual void Vf64() { m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfe); }
    virtual void Vf68() {}  // vt+0x68 0x009ab500 CKNodeFx3d_Interrupt_maybe (empty)
    // vt+0x6c 0x009ada78 CKNodeFx3d_Stop: stopped.
    virtual void Stop() { m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfe) | 1); }
    virtual void Vf70() {}  // vt+0x70 0x009ab508 CKNodeFx3d_OnPause (empty)
    virtual void Vf74() {}  // vt+0x74 0x009ab510 CKNodeFx3d_OnResume (empty)
    // vt+0x78 0x009ada70 CKNodeFx3d_Update (empty): the effect's frame (UpdateCKSrvFx calls it for every running effect).
    virtual void Update(IKTime* /*frameClock*/) {}
    // vt+0x7c 0x009ab490 IKFx_StopIfLinkedTo (empty): the effect stops when it belongs to the sector.
    virtual void StopIfLinkedTo(int32_t /*sector*/) {}
    // vt+0x80 / +0x84: pure in IKNodeFx (0x9873c8); the effect classes keep their FX data here (CKParticlesEffectNodeFx
    // 0x9acd28 / 0x9acd30). The defaults stand in until the classes override them.
    virtual IKFxData* GetFxData() { return nullptr; }       // vt+0x80
    virtual void SetFxData(IKFxData* /*data*/) {}           // vt+0x84
    // vt+0x88 0x009ab498 IKFx_SetOwner, vt+0x8c 0x009ab4a8 CKNodeFx3d_SetDataAndOwner (the DOF, HDR and
    // TimeScaling effects override it with a priority test).
    virtual void SetOwner(const IKSerializable* owner) { m_pOwner = owner; }
    virtual void SetDataAndOwner(IKFxData* data, const IKSerializable* owner) {
        SetFxData(data);
        m_pOwner = owner;
    }
    // vt+0x90 0x009ab518 / vt+0x94 0x009ab520 CKNodeFx3d_Set/GetUpdateWhenPaused (+0x04).
    virtual void SetUpdateWhenPaused(uint8_t value) { m_bUpdateWhenPaused = value; }
    virtual uint8_t GetUpdateWhenPaused() { return m_bUpdateWhenPaused; }

    // +0x04 DotD; name from the Ghidra analysis (vt+0x50 IKFx_ResetRuntimeFlags clears it; the inline
    // CKNodeFx3d_Get/SetUpdateWhenPaused 0x9ab520/0x9ab518 read and write it), _maybe. Load sets 0.
    uint8_t m_bUpdateWhenPaused;
    uint8_t m_pad05[3];              // +0x05 never written
    const IKSerializable* m_pOwner;  // +0x08 XXL2 (CKNodeFx3d_SetDataAndOwner 0x9ab4a8 stores it)
    uint8_t m_baFxData;              // +0x0c XXL2 CBitArray8 (bit 1: reserved, CKNodeFx3d_ReleaseReservation 0x9ab620)
    uint8_t m_pad0d[3];
};
static_assert(IKFx::kClassKey == 0x154c, "key");

// 0x001cdde8 StopOwnedParticleEffect (CKParticlesEffectNodeFx.cpp): the effect stopped (vt+0x6c) when `owner` holds
// its reservation.
inline void StopOwnedParticleEffect(IKFx* effect, const IKSerializable* owner) {
    if ((effect->m_baFxData & 2u) != 0 && effect->m_pOwner == owner) effect->Stop();
}
DOTD_ASSERT_SIZE(IKFx, 0x10);
DOTD_ASSERT_OFFSET(IKFx, m_bUpdateWhenPaused, 0x04);
DOTD_ASSERT_OFFSET(IKFx, m_pOwner, 0x08);
DOTD_ASSERT_OFFSET(IKFx, m_baFxData, 0x0c);
