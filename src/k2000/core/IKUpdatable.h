// IKUpdatable.h - the updated objects (key 0x3fe; XXL2: K/KCore/Interfaces/IKUpdatable.h): modules
// (managers), services, CKLevel, hooks, groups, CKGameLoop.
//
// XXL2 has 11 slots here (Start .. PostSectorUnload); DotD inserted six more (+0x58, +0x60, +0x64,
// +0x6c, +0x74, +0x80), whose names are unknown. The slot map is from co-override agreement over the
// 27 IKUpdatable classes in both games (outputs/remake/research/xxl2-symbols.md section 3).
// XXL2 puts IKUObjectInfos between IKSerializable and IKUpdatable; it adds no PS3 fields or slots here.
// vtable 0xb12ae8. Pure slots hold __cxa_pure_virtual (OPD 0xc0d668) in the original.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"

class IKTime;

class IKUpdatable : public IKSerializable {
public:
    ~IKUpdatable() override {}                                // vt+0x00 / +0x04  0x990e58 / 0x990e18
    int32_t IsKindOfClass(uint32_t key) override {            // vt+0x08  0x990b90
        return key == 0x3fe || key == 0xc;
    }
    void Destroy() override {}                                // vt+0x10  0x990b40
    virtual void Start() = 0;                                 // vt+0x50
    virtual void Restart() {}                                 // vt+0x54  0x990bb0
    virtual int32_t Vf58() { return 1; }                      // vt+0x58  0x990bb8 (DotD)
    virtual void PreRestart() {}                              // vt+0x5c  0x990bc0
    virtual void Vf60() {}                                    // vt+0x60  0x990bc8 (DotD)
    virtual void Vf64() {}                                    // vt+0x64  0x990bd0 (DotD)
    virtual void Stop() = 0;                                  // vt+0x68
    virtual int32_t Vf6C() { return 1; }                      // vt+0x6c  0x990bd8 (DotD)
    virtual void Pause() = 0;                                 // vt+0x70
    virtual int32_t Vf74() { return 1; }                      // vt+0x74  0x990be0 (DotD)
    virtual void Resume() = 0;                                // vt+0x78
    virtual void Update(IKTime* frameClock) = 0;               // vt+0x7c  (XXL2: IKTime*)
    virtual void Vf80(IKTime* /*frameClock*/) {}              // vt+0x80  0x990be8 (DotD): the update of a life with flag 2 (CKBundle_Update)
    virtual void PreSectorLoaded(int32_t /*sector*/) {}       // vt+0x84  0x990bf0 (the sector index: CKGameLoop_PreSectorLoaded passes it on)
    virtual void SectorLoaded(int32_t /*sector*/) {}           // vt+0x88  0x990bf8 (the sector index: CKBundle_SectorLoaded passes it on)
    virtual void SectorUnload(int32_t /*sector*/) {}          // vt+0x8c  0x990c00 (the sector index: CKGameLoop passes it on)
    virtual void PostSectorUnload(int32_t /*sector*/) {}      // vt+0x90  0x990c08
};
