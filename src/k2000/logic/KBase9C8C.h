// KBase9C8C.h - an unregistered abstract base (key 0x9c8c, Ghidra: CKBhvBlockBase_maybe; no XXL2
// counterpart). Original unit: KBase9C8C.cpp (0x5c5788-0x5c5838). Derived straight from IKSerializable;
// base of the behaviour blocks (CKBhvBlockProjectiles 0xa7cc; _maybe also CKBhvBlockAnimation and
// CKBhvBlockSpeech). Its vtable 0xb2fd80 (TOC1 -0x5ff8) adds the block interface at +0x50..+0x7c that
// CKHkScriptedNPC drives on its blocks (+0x34), the user (the NPC's +0x2c, a KBase9CCC) passed along.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Stub.h"

class IKTime;

class KBase9C8C : public IKSerializable {
public:
    KBase9C8C() {}  // 0x005c5788 CKBhvBlockBase_maybe_Construct: stores the vtable only
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005c57b0 BhvBlockBase_Load_maybe

    // vt+0x50 0x9cd380 KBaseC_vf50_2 (empty): the runtime reset (CKHkScriptedNPC_OnActivate).
    virtual void ResetRuntime() {}
    // vt+0x54 0x9cd388 KBaseC_vf54_2 (empty): CKHkScriptedNPC_OnDeactivate.
    virtual void Vf54() {}
    // vt+0x58 0x9cd390 KBaseC_vf58_2 (empty): CKHkScriptedNPC_ReinitRuntime.
    virtual void Vf58() {}
    // vt+0x5c 0x9cd398 KBaseC_vf5C_2: whether the block can start for `user` (1).
    virtual uint8_t CanEnter(IKSerializable* /*user*/) { return 1; }
    // vt+0x60 0x9cd320 KBaseC_vf60_2: whether the current block can be left (1).
    virtual uint8_t CanLeave(IKSerializable* /*user*/) { return 1; }
    // vt+0x64 / +0x68 / +0x6c: the block entered for `user`, left, updated; pure in the base (__cxa_pure_virtual).
    // CKBhvBlockAnimation, CKBhvBlockProjectiles and CKBhvBlockSpeech have them.
    virtual void Enter(IKSerializable* /*user*/) {
        DOTD_STUB_ONCE("KBase9C8C vt+0x64: a behaviour block without its own Enter (pure in the original)");
    }
    virtual void Leave(IKSerializable* /*user*/) {
        DOTD_STUB_ONCE("KBase9C8C vt+0x68: a behaviour block without its own Leave (pure in the original)");
    }
    virtual void Update(IKTime* /*clock*/) {
        DOTD_STUB_ONCE("KBase9C8C vt+0x6c: a behaviour block without its own Update (pure in the original)");
    }
    // vt+0x70 0x9cd3a0 KBaseC_vf70_4 (empty): the block prepared as the next one (CKHkScriptedNPC_vfF8).
    virtual void Prepare() {}
    // vt+0x74 0x9cd3a8 KBaseC_vf74_5 (empty): the preparation undone (CKHkScriptedNPC_vfFC).
    virtual void Unprepare() {}
    // vt+0x78 0x9cd3b0 KBaseC_vf78_4 (empty): the next block's update while the current one runs.
    virtual void PreUpdate(IKTime* /*clock*/) {}
    // vt+0x7c 0x9cd3b8 KBaseC_vf7C_3: 0.
    virtual uint8_t Vf7C() { return 0; }
};
