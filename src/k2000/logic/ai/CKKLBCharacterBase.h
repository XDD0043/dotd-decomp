// CKKLBCharacterBase.h - the unregistered base of the linked-beacon characters (key 0x9f0c, Ghidra KBase9F0C;
// name _maybe: "KLB" = K linked beacon, from its one registered class CKKLBCharacterSparx 0x9f8c). Not in
// CKKLBCharacterSparx's IsKindOf chain (that is IKSerializable only). Its Load 0x451510 sits in the
// CKLinkedBeaconSeq.cpp unit (0x450df0-0x451658), where it is ported.
// No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class IKFile;
class IKTime;
struct CPFCharacter;

class CKKLBCharacterBase : public IKSerializable {
public:
    CKKLBCharacterBase() {}  // the derived Create stores the vtable only
    ~CKKLBCharacterBase() override {}

    // vt+0x2c 0x00451510 CKKLBCharacterSparx_LoadBase_maybe (CKLinkedBeaconSeq.cpp): one reference.
    int32_t Load(IKFile* file, int32_t type) override;

    // The character interface the linked beacon (CKHkLinkedBeacon, its +0xc8) drives, slots +0x50..+0xa8 (not
    // IKUpdatable's meanings). Every slot is CKKLBCharacterSparx's (the only derived class); its file says what each does.
    virtual void Vf50() = 0;                    // vt+0x50 0x4504f8: bind to the hero group's Sparx
    virtual void Vf54() = 0;                    // vt+0x54 0x450690: release the Sparx's target
    virtual int32_t Vf58() = 0;                 // vt+0x58 0x450528: bound to a Sparx
    virtual CVector3 Vf5C() = 0;                // vt+0x5c 0x450950: the Sparx's world position
    virtual int32_t Vf60() = 0;                 // vt+0x60 0x450548: 1
    virtual void Vf64(const float* direction) = 0;  // vt+0x64 0x450668: the goal direction
    virtual void Vf68(const CVector3* position, float speed, int32_t unused) = 0;  // vt+0x68 0x450a28
    virtual void Vf6C(const CVector3* position, const CVector3* direction, int32_t fast) = 0;  // vt+0x6c 0x450988
    virtual void Vf70(const CVector3* position, const CVector3* direction) = 0;  // vt+0x70 0x450640: place
    virtual uint8_t MoveTowardTarget(IKTime* clock) = 0;  // vt+0x74 0x450610
    virtual uint8_t Vf78(IKTime* clock) = 0;    // vt+0x78 0x450a78: the same as vt+0x74
    virtual uint8_t Vf7C(double dt) = 0;        // vt+0x7c 0x4505e0: the node's animation at its end
    virtual void Vf80(uint32_t animation) = 0;  // vt+0x80 0x450888: play a dictionary animation
    virtual void Vf84(double dt) = 0;           // vt+0x84 0x450858: advance the node's animation
    virtual void Vf88(uint32_t still) = 0;      // vt+0x88 0x450550: +0x54 bit 2 = !still
    virtual void Vf8C(uint8_t still) = 0;       // vt+0x8c 0x450ab8: start the move updater
    virtual uint8_t SetTarget() = 0;            // vt+0x90 0x450580
    virtual CPFCharacter* Vf94() = 0;           // vt+0x94 0x4508c0: hero 0's path-finding character
    virtual void Vf98(int32_t reset) = 0;       // vt+0x98 0x4505b0: the goal reset to the node
    virtual IKSerializable* Vf9C() = 0;         // vt+0x9c 0x450aa8: the Sparx's target
    virtual const CMatrix34* VfA0() = 0;        // vt+0xa0 0x450938: the Sparx node's world matrix
    virtual IKSerializable* VfA4() = 0;         // vt+0xa4 0x450908: the hero group's Sparx's node
    virtual int32_t VfA8() = 0;                 // vt+0xa8 0x9c3ce0: 0

    IKSerializable* m_pBeacon;  // +0x04 CKHkLinkedBeacon* in every live sample (struct draft)_maybe
};
DOTD_ASSERT_SIZE(CKKLBCharacterBase, 0x8);
DOTD_ASSERT_OFFSET(CKKLBCharacterBase, m_pBeacon, 0x04);
