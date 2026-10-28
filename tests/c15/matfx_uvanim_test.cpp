// matfx_uvanim_test - C2.4: CMaterial::UpdateUVAnimation (MatFXUVAnim_UpdateMaterial_maybe 0xbd228), the per-frame UV
// animation of the materials of shader modes 5, 6, 12 and 14. No game data: a CMaterial is built by hand, its
// effect type / flag bits and parameter block are set and an IKTime of known time and delta is stepped; the matrix is
// compared with the values worked out from the assembly's semantics.
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "Renderware/rpmatfx/RpMatFX.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/system/IKTime.h"

namespace {
int g_failures = 0;

void Check(bool ok, const char* what) {
    if (!ok) {
        std::printf("FAIL: %s\n", what);
        ++g_failures;
    }
}
bool Near(float a, float b, float eps = 1e-4f) { return std::fabs(a - b) <= eps; }
void CheckNear(float got, float want, const char* what, float eps = 1e-4f) {
    if (!Near(got, want, eps)) {
        std::printf("FAIL: %s: got %.7f want %.7f\n", what, got, want);
        ++g_failures;
    }
}

class TestTime : public IKTime {
public:
    double KGetExactTime() override { return 0.0; }
    int32_t Initialize() override { return 1; }
    void Destroy() override {}
};

void SetTime(IKTime* time, float now, float dt, int32_t state = IKTime::RUNNING) {
    time->m_afCurrentTime[0] = now;
    time->m_afDeltaTime[0] = dt;
    time->m_eCurrentState = state;
}

uint32_t Bits(float f) {
    uint32_t b;
    std::memcpy(&b, &f, 4);
    return b;
}

void Identity(CMatrix34* m) {
    std::memset(m, 0, sizeof(*m));
    m->m_right.x = 1.0f;
    m->m_up.y = 1.0f;
    m->m_at.z = 1.0f;
    m->m_ui32Flags = 0x20003u;
}

// Mode 12 (one slot; slot 0 writes the first-pass matrix, no RpMaterial needed), effect type `type`, flag bits `flags`
// (properties bit 19 + 7 * slot + n).
struct Rig {
    CMaterial material;
    CMatrix34 matrix;
    TestTime time;
    explicit Rig(uint32_t type, uint32_t flagBits) {
        Identity(&matrix);
        std::memset(&material.m_FXParameters, 0, sizeof(material.m_FXParameters));  // the constructor leaves the slots alone
        material.m_pFirstPassTransformMatrix = &matrix;
        material.m_baProperties = 0x100u | (12u << 3) | (type << 16) | (flagBits << 19);
    }
    void Step(float now, float dt) {
        SetTime(&time, now, dt);
        material.UpdateUVAnimation(&time);
    }
    CMaterialFXEffect& Fx() { return material.m_FXParameters.m_aEffects[0]; }
};

void TestNotRunning() {
    Rig rig(0, 3);
    rig.Fx().k01.m_aui32Words[0] = Bits(1.0f);
    SetTime(&rig.time, 1.0f, 0.5f, IKTime::PAUSED);
    rig.material.UpdateUVAnimation(&rig.time);
    Check(rig.matrix.m_pos.x == 0.0f && rig.matrix.m_ui32Flags == 0x20003u, "paused clock leaves the matrix alone");
}

void TestScroll() {
    Rig rig(0, 3);  // U and V animated, both unlimited
    CMaterialFXEffect& fx = rig.Fx();
    fx.k01.m_aui32Words[0] = Bits(0.5f);
    fx.k01.m_aui32Words[1] = Bits(-0.25f);
    rig.Step(0.5f, 0.5f);
    CheckNear(rig.matrix.m_pos.x, 0.25f, "scroll u");
    CheckNear(rig.matrix.m_pos.y, -0.125f, "scroll v");
    Check(rig.matrix.m_ui32Flags == 0x3u, "scroll clears the internal identity flag");
    // Wrap into [-1, 1]: u 0.9 + 0.5 * 0.5 = 1.15 -> 0.15 ; v -0.9 - 0.25 * 0.5 = -1.025 -> -0.025
    rig.matrix.m_pos.x = 0.9f;
    rig.matrix.m_pos.y = -0.9f;
    rig.Step(1.0f, 0.5f);
    CheckNear(rig.matrix.m_pos.x, 0.15f, "scroll u wraps down", 1e-5f);
    CheckNear(rig.matrix.m_pos.y, -0.025f, "scroll v wraps up", 1e-5f);

    // Only V animated: U untouched, z cleared.
    Rig onlyV(0, 2);
    onlyV.Fx().k01.m_aui32Words[0] = Bits(5.0f);
    onlyV.Fx().k01.m_aui32Words[1] = Bits(1.0f);
    onlyV.matrix.m_pos.z = 7.0f;
    onlyV.Step(0.25f, 0.25f);
    CheckNear(onlyV.matrix.m_pos.x, 0.0f, "unanimated u stays");
    CheckNear(onlyV.matrix.m_pos.y, 0.25f, "animated v");
    CheckNear(onlyV.matrix.m_pos.z, 0.0f, "scroll clears z");
}

void TestScrollLimited() {
    Rig rig(0, 1 | 4);  // U animated (bit 19) and U limited (bit 21)
    CMaterialFXEffect& fx = rig.Fx();
    fx.k01.m_aui32Words[0] = Bits(1.0f);
    fx.k01.m_ui8Byte10 = 4;  // four stops
    fx.k01.m_ui32Word18 = Bits(1.0f);  // one second at each
    fx.k01.m_ui8StepU = 1;
    rig.Step(0.25f, 0.25f);  // moves to 0.25 = 1/4: stops, countdown 1.0
    CheckNear(rig.matrix.m_pos.x, 0.25f, "limited: reaches stop 1");
    Check(fx.k01.m_ui8WaitingU == 1, "limited: waiting");
    CheckNear(fx.k01.m_fWaitLeftU, 1.0f, "limited: wait starts");
    rig.Step(0.75f, 0.5f);
    CheckNear(fx.k01.m_fWaitLeftU, 0.5f, "limited: counts down");
    CheckNear(rig.matrix.m_pos.x, 0.25f, "limited: holds still");
    rig.Step(1.25f, 0.5f);
    CheckNear(fx.k01.m_fWaitLeftU, 0.0f, "limited: counted down");
    Check(fx.k01.m_ui8WaitingU == 1 && fx.k01.m_ui8StepU == 1, "limited: still waiting at 0");
    rig.Step(1.5f, 0.25f);  // countdown <= 0: moves on to step 2
    Check(fx.k01.m_ui8WaitingU == 0 && fx.k01.m_ui8StepU == 2, "limited: next step");
    rig.Step(1.75f, 0.25f);  // 0.25 + 0.25 = 0.5 = 2/4: stops
    CheckNear(rig.matrix.m_pos.x, 0.5f, "limited: reaches stop 2");
    Check(fx.k01.m_ui8WaitingU == 1, "limited: waiting at 2");
    fx.k01.m_ui8StepU = 4;  // past the last stop the step goes back to 1
    fx.m_fWaitLeftV = 0.0f;
    fx.k01.m_fWaitLeftU = 0.0f;
    rig.Step(2.0f, 0.1f);
    Check(fx.k01.m_ui8StepU == 1 && fx.k01.m_ui8WaitingU == 0, "limited: step wraps to 1");
    // Step != 0 and the position reaches 1.0: back to 0, waiting.
    fx.k01.m_ui8StepU = 4;
    rig.matrix.m_pos.x = 0.9f;
    rig.Step(2.5f, 0.5f);
    CheckNear(rig.matrix.m_pos.x, 0.0f, "limited: passes 1.0 -> 0");
    Check(fx.k01.m_ui8StepU == 0 && fx.k01.m_ui8WaitingU == 1, "limited: step 0 waiting");
}

void TestRotation() {
    Rig rig(1, 1);  // U: about X
    rig.matrix.m_pos = {0.25f, 0.5f, 0.75f};
    rig.Fx().k01.m_aui32Words[0] = Bits(90.0f);
    rig.Step(1.0f, 1.0f);  // 90 degrees about X
    CheckNear(rig.matrix.m_right.x, 1.0f, "rotate X keeps right.x", 1e-5f);
    CheckNear(rig.matrix.m_up.y, 0.0f, "rotate X: up.y", 1e-5f);
    CheckNear(std::fabs(rig.matrix.m_up.z), 1.0f, "rotate X: |up.z|", 1e-5f);
    CheckNear(rig.matrix.m_pos.x, 0.25f, "rotate keeps pos x");
    CheckNear(rig.matrix.m_pos.y, 0.5f, "rotate keeps pos y");
    CheckNear(rig.matrix.m_pos.z, 0.75f, "rotate keeps pos z");
    Check((rig.matrix.m_ui32Flags & 0x20000u) == 0, "rotate clears the internal identity flag");

    Rig both(1, 3);  // U about X by 90, V about Y by 90, in that order
    both.Fx().k01.m_aui32Words[0] = Bits(90.0f);
    both.Fx().k01.m_aui32Words[1] = Bits(90.0f);
    both.Step(1.0f, 1.0f);
    Rig xOnly(1, 1);
    xOnly.Fx().k01.m_aui32Words[0] = Bits(90.0f);
    xOnly.Step(1.0f, 1.0f);
    Check(std::fabs(both.matrix.m_right.x - xOnly.matrix.m_right.x) > 0.5f, "rotate V adds a rotation about Y");
}

void TestFlipBook() {
    Rig rig(2, 0);
    CMaterialFXEffect& fx = rig.Fx();
    fx.k2.m_ui16Half8 = 2;  // 2 x 2 frames
    fx.k2.m_ui16HalfA = 2;
    fx.k2.m_fFloatC = 1.0f;
    fx.k2.m_fFloat10 = 2.0f;
    rig.matrix.m_at.x = 5.0f;
    rig.Step(0.6f, 0.1f);  // 0.6 * 4 = 2.4: frame 2 = row 1, column 0
    CheckNear(rig.matrix.m_pos.x, 0.0f, "flip-book u frame 2");
    CheckNear(rig.matrix.m_pos.y, 0.5f, "flip-book v frame 2");
    CheckNear(rig.matrix.m_right.x, 2.0f, "flip-book scale x");
    CheckNear(rig.matrix.m_up.y, 2.0f, "flip-book scale y");
    CheckNear(rig.matrix.m_at.z, 0.0f, "flip-book at.z");
    CheckNear(rig.matrix.m_at.x, 0.0f, "flip-book clears at.x");
    Check(rig.matrix.m_ui32Flags == 2u, "flip-book flags");
    rig.Step(1.3f, 0.1f);  // second cycle: (1.3 - 1) * 4 = 1.2: frame 1 = row 0, column 1
    CheckNear(rig.matrix.m_pos.x, 0.5f, "flip-book u frame 1", 1e-3f);
    CheckNear(rig.matrix.m_pos.y, 0.0f, "flip-book v frame 1");

    Rig scroll(2, 3);  // plus the running U / V scroll
    CMaterialFXEffect& sfx = scroll.Fx();
    sfx.k2.m_ui16Half8 = 2;
    sfx.k2.m_ui16HalfA = 2;
    sfx.k2.m_fFloatC = 1.0f;
    sfx.k2.m_fFloat10 = 1.0f;
    sfx.k2.m_aui32Words[0] = Bits(0.5f);
    sfx.k2.m_aui32Words[1] = Bits(-0.5f);
    scroll.Step(0.1f, 0.1f);  // frame 0; accumulators 0.05 / -0.05
    CheckNear(scroll.matrix.m_pos.x, 0.05f, "flip-book u scroll");
    CheckNear(scroll.matrix.m_pos.y, -0.05f, "flip-book v scroll");
    CheckNear(sfx.k2.m_fAccumU, 0.05f, "flip-book accumulator u");
    scroll.Step(0.2f, 0.1f);
    CheckNear(sfx.k2.m_fAccumU, 0.10f, "flip-book accumulator u grows");
    sfx.k2.m_fAccumU = 1.95f;  // the accumulator is not wrapped, the position is
    scroll.Step(0.3f, 0.1f);
    CheckNear(sfx.k2.m_fAccumU, 2.0f, "flip-book accumulator unwrapped", 1e-5f);
    // time 0.3: frame 1 (column 0.5), so u = 0.5 + 2.0 = 2.5 -> 0.5 after the wrap
    CheckNear(scroll.matrix.m_pos.x, 0.5f, "flip-book u wrapped (2.5 -> 0.5)", 1e-5f);

    Rig empty(2, 0);  // a zero grid: nothing happens
    empty.Fx().k2.m_ui16Half8 = 0;
    empty.Fx().k2.m_ui16HalfA = 3;
    empty.Step(0.5f, 0.1f);
    Check(empty.matrix.m_ui32Flags == 0x20003u && empty.matrix.m_right.x == 1.0f, "flip-book with a zero grid");
}

void TestShear() {
    Rig rig(3, 0);
    rig.Fx().k3.m_afFloats[0] = 0.2f;  // amplitude
    rig.Fx().k3.m_afFloats[1] = 1.0f;  // frequency
    rig.matrix.m_up.z = 9.0f;
    rig.Step(0.5235988f, 0.1f);  // sin(pi/6) = 0.5
    CheckNear(rig.matrix.m_up.x, 0.1f, "shear up.x", 1e-3f);
    CheckNear(rig.matrix.m_up.y, 1.0f, "shear up.y");
    CheckNear(rig.matrix.m_up.z, 0.0f, "shear up.z");
    Check(rig.matrix.m_ui32Flags == 0u, "shear clears the type bits and the internal identity flag");
    rig.Step(-0.5235988f, 0.1f);  // negative time: the library sine, odd
    CheckNear(rig.matrix.m_up.x, -0.1f, "shear with a negative angle", 1e-3f);
}

void TestCircle() {
    Rig rig(4, 0);
    rig.Fx().k4.m_afFloats[0] = 0.3f;  // sine amplitude
    rig.Fx().k4.m_afFloats[1] = 1.0f;  // sine frequency
    rig.Fx().k4.m_fFloat18 = 0.1f;     // cosine amplitude
    rig.Fx().k4.m_fFloat20 = 2.0f;     // cosine frequency
    rig.matrix.m_pos.z = 4.0f;
    rig.Step(0.0f, 0.1f);
    CheckNear(rig.matrix.m_pos.x, 0.0f, "circle t=0 x");
    CheckNear(rig.matrix.m_pos.y, 0.1f, "circle t=0 y");
    CheckNear(rig.matrix.m_pos.z, 0.0f, "circle z");
    Check((rig.matrix.m_ui32Flags & 0x20000u) == 0, "circle clears the internal identity flag");
    rig.Step(1.5707964f, 0.1f);  // sin(pi/2) = 1 ; cos(pi) = -1
    CheckNear(rig.matrix.m_pos.x, 0.3f, "circle t=pi/2 x", 1e-3f);
    CheckNear(rig.matrix.m_pos.y, -0.1f, "circle t=pi/2 y", 1e-3f);
    rig.Step(-1.5707964f, 0.1f);
    CheckNear(rig.matrix.m_pos.x, -0.3f, "circle t=-pi/2 x", 1e-3f);
    CheckNear(rig.matrix.m_pos.y, -0.1f, "circle t=-pi/2 y", 1e-3f);
}

void TestTwoSlots() {
    // Mode 6: slot 0 animates the base UV matrix, slot 1 the dual one (the MatFX effect's two matrices).
    RpMaterial rp;
    std::memset(&rp, 0, sizeof(rp));
    RpMatFXMaterialSetEffects(&rp, 6);
    CMatrix34 base;
    CMatrix34 dual;
    Identity(&base);
    Identity(&dual);
    RpMatFXMaterialSetUVTransformMatrices(&rp, reinterpret_cast<RwMatrix*>(&base), reinterpret_cast<RwMatrix*>(&dual));
    CMaterial material;
    std::memset(&material.m_FXParameters, 0, sizeof(material.m_FXParameters));
    material.m_pRpMaterial = &rp;
    // slot 0: scroll U (bit 19); slot 1 (type bits at 23): scroll V (bit 27 = 20 + 7)
    material.m_baProperties = 0x100u | (6u << 3) | (0u << 16) | (1u << 19) | (0u << 23) | (1u << 27);
    material.m_FXParameters.m_aEffects[0].k01.m_aui32Words[0] = Bits(1.0f);
    material.m_FXParameters.m_aEffects[1].k01.m_aui32Words[1] = Bits(2.0f);
    TestTime time;
    SetTime(&time, 0.25f, 0.25f);
    material.UpdateUVAnimation(&time);
    CheckNear(base.m_pos.x, 0.25f, "mode 6 base u");
    CheckNear(base.m_pos.y, 0.0f, "mode 6 base v untouched");
    CheckNear(dual.m_pos.y, 0.5f, "mode 6 dual v");
    CheckNear(dual.m_pos.x, 0.0f, "mode 6 dual u untouched");
    // Effect type above 4 on a slot: skipped.
    material.m_baProperties = 0x100u | (6u << 3) | (5u << 16) | (1u << 19);
    SetTime(&time, 0.5f, 0.25f);
    material.UpdateUVAnimation(&time);
    CheckNear(base.m_pos.x, 0.25f, "effect type 5 does nothing");
    RpMatFXMaterialSetEffects(&rp, 0);
}
}  // namespace

int main() {
    TestNotRunning();
    TestScroll();
    TestScrollLimited();
    TestRotation();
    TestFlipBook();
    TestShear();
    TestCircle();
    TestTwoSlots();
    if (g_failures == 0) std::printf("matfx_uvanim_test: all passed\n");
    return g_failures == 0 ? 0 : 1;
}
