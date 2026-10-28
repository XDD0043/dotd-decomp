// CKHkActorBase.h - the unregistered base of most Spyro2008 and k2000 hooks (key 0xd82, vtable 0xb24cb0,
// size 0x20). Original unit: CKHkActorBase.cpp (0x3f6dc0-0x3f7430). No XXL2 class of this key. It adds no
// field to IKHook: its constructor 0x3f6dc0 sets the IKLife/IKHook parts only.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/IKHook.h"

class CKHkActorBase : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x36)

    CKHkActorBase() {}  // 0x003f6dc0 CKHkActorBase_d82_maybe_Construct (the IKLife/IKHook defaults)
    ~CKHkActorBase() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003f6e98 CKHkActorBase_d82_maybe_Load
    // vt+0x30 0x003f6e70 CKHkActorBase_d82_maybe_PostLoad: IKLife_PostLoad, then 1.
    int32_t PostLoad(int32_t type) override {
        PostLoadLife(type);
        return 1;
    }
    void SetDefaultState(int32_t /*flag*/) override {}  // vt+0x38 0x3f72a0 KStub_Nop_3f72a0 (empty)
    // vt+0x50 0x3f6e48 CKHkActorBase_d82_maybe_ResetRuntime (empty): the hooks' Start overrides call it first.
    void Start() override {}
    // vt+0xc8 0x9c0bd0 (empty here): the hooks with a state preset (CKHkDoor, CKHkPressionStone,
    // CKHkContextualMeca, ...) set their flag bits from the preset `state` (0 or 1).
    virtual void ApplyStatePreset(int32_t /*state*/) {}
    // vt+0xcc 0x9c0bd8 (empty here): CKHkHeroActivator and others switch themselves on or off.
    virtual void SetEnabled(int32_t /*enabled*/) {}
};
DOTD_ASSERT_SIZE(CKHkActorBase, 0x20);
