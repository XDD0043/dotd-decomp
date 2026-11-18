// CSparkNodeFx.h - a spark effect node (key 0x70b, vtable 0xb18ba8, size 0x5c). Original unit:
// CSparkNodeFx.cpp. No XXL2 class; the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/INodeFx.h"

class CKSparkParam;
class CParticleGeometry;
struct CMatrix34;

class CSparkNodeFx : public INodeFx {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x1c)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a55b8
        return key == 0x70b || key == 0x50b || key == 0xcb || key == 0x24b || key == 0x20b || key == 0x14b || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CSparkNodeFx)

    // One spark (PS3 0x68 bytes, PostLoad's array). The pool and the live sparks are singly linked lists through
    // +0x00 (m_pFreeSparks / m_pLiveSparks). Names ours, from InitSpark / UpdateSpark.
    struct SSpark {
        SSpark* m_pNext;        // +0x00
        float m_position[3];    // +0x04
        float m_velocity[3];    // +0x10
        float m_accel[3];       // +0x1c in the node's space when m_bLocal (UpdateSpark: through the inverse LTM)
        float m_size[2];        // +0x28
        float m_age;            // +0x30 InitSpark 0; UpdateSparks adds the frame time
        float m_lifetime;       // +0x34
        float m_sizeRate[2];    // +0x38 (end size - start size) / lifetime
        float m_unk40;          // +0x40 not written by InitSpark
        float m_unk44;          // +0x44 param +0x70 + r * +0x74, at least 0 (not read by UpdateSpark)
        uint8_t m_targetColor[4];  // +0x48 RwRGBA
        uint8_t m_color[4];        // +0x4c RwRGBA, moves toward the target
        float m_colorSpeed;     // +0x50 colour distance / lifetime / 255
        float m_colorF[4];      // +0x54 the colour as floats
        uint8_t m_bLocal;       // +0x64 param byte 0x9a bit 3
        uint8_t m_pad65[3];
    };

    CSparkNodeFx();  // 0x000e7f20 CSparkNodeFx_Construct (inlined in 0xe8388 CSparkNodeFx_Create)
    ~CSparkNodeFx() override {}  // 0x0e7ee0 / 0xe8408 (+ delete): CNode's destructor chain
    // vt+0x10 0x000e7f88 CSparkNodeFx_Destroy: CNode's, the matrix destroyed, the free and live lists unlinked (every
    // link cleared) and emptied, the spark array freed (delete[]) and cleared.
    void Destroy() override;

    // vt+0x2c 0x000e8070 CSparkNodeFx_Load
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x000e9410 CSparkNodeFx_PostLoad: the spark pool (count - listed, 0x68 bytes each), the
    // matrix (+0x54), the PTank's constant tex coords, the sparks started when +0x40 is set, every geometry's vt+0x80.
    int32_t PostLoad(int32_t type) override;
    // vt+0x1c 0x000ea040 CSparkNodeFx_MessageProc: 0x1a64 (on / off byte) starts or stops the sparks.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x58 0x000ea200 CSparkNodeFx_Enqueue: while on (+0x40), visible (flag 1) and the clock not in state 3 (in a
    // paused state only with +0x4c), the sparks advance; when the last one died and the emission is over they stop;
    // then the node's own geometry is culled and queued (vt+0x84). No child traversal, no render stamp.
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                          int32_t distanceCull) override;

    // 0x000e7b20 CSparkNodeFx_SetParams_maybe: the parameters copied into this node's own (CKSparkParam_Copy_maybe).
    void SetParams(CKSparkParam* params);
    // 0x000e7c90 CSparkNodeFx_ReleaseAllSparks_maybe
    void ReleaseAllSparks();
    // 0x000e84a0 CSparkNodeFx_InitSpark_maybe: 16 rand draws (24 with random colours, param byte 0x9a bit 0).
    void InitSpark(SSpark* spark);
    // 0x000e9250 CSparkNodeFx_InitSparks_maybe: on, a first burst, the emission timer (1 rand draw) and duration.
    void InitSparks();
    // 0x000e96b0 CSparkNodeFx_UpdateSpark_maybe: motion, size, colour; the PTank matrix and colour entries.
    void UpdateSpark(float dt, SSpark* spark, CMatrix34* matrix, uint8_t* color);
    // 0x000e9c70 CSparkNodeFx_UpdateSparks_maybe: the live sparks advance or die; the emission timer (a burst and
    // 1 rand draw when it runs out).
    void UpdateSparks(float dt);

    int32_t m_i32NbSparks;      // +0x2c _maybe: PostLoad allocates this many minus the listed ones
    int32_t m_i32NbLiveSparks;  // +0x30 PostLoad sets 0
    SSpark* m_pFreeSparks;      // +0x34 the pool (PostLoad); the constructor sets 0
    SSpark* m_pLiveSparks;      // +0x38 the constructor and PostLoad set 0
    CParticleGeometry* m_pGeometry;  // +0x3c PostLoad: the first geometry (a CParticleGeometry); constructor 0
    uint8_t m_unk40;            // +0x40 read: on (PostLoad starts the sparks when non-zero)
    uint8_t m_unk41;            // +0x41 InitSparks clears it; set: no new bursts, the sparks stop with the last one
    uint8_t m_pad42[2];
    float m_fEmitTime;          // +0x44 InitSparks: param +0x90; Enqueue counts it down
    float m_fBurstTimer;        // +0x48 the time to the next burst
    uint8_t m_unk4c;            // +0x4c read: also update while the clock is paused
    uint8_t m_pad4d[3];
    CKSparkParam* m_pSparkParam;  // +0x50 the constructor sets 0
    CMatrix34* m_pMatrix;       // +0x54 PostLoad: RwMatrixCreate (UpdateSparks: the inverse of the LTM)
    SSpark* m_pSparks;          // +0x58 PostLoad: the spark array; the constructor sets 0
};
static_assert(CSparkNodeFx::kClassKey == 0x70b, "key");
DOTD_ASSERT_SIZE(CSparkNodeFx, 0x5c);
DOTD_ASSERT_SIZE(CSparkNodeFx::SSpark, 0x68);
DOTD_ASSERT_OFFSET(CSparkNodeFx::SSpark, m_age, 0x30);
DOTD_ASSERT_OFFSET(CSparkNodeFx::SSpark, m_targetColor, 0x48);
DOTD_ASSERT_OFFSET(CSparkNodeFx::SSpark, m_colorF, 0x54);
DOTD_ASSERT_OFFSET(CSparkNodeFx::SSpark, m_bLocal, 0x64);
DOTD_ASSERT_OFFSET(CSparkNodeFx, m_i32NbSparks, 0x2c);
DOTD_ASSERT_OFFSET(CSparkNodeFx, m_pFreeSparks, 0x34);
DOTD_ASSERT_OFFSET(CSparkNodeFx, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CSparkNodeFx, m_fEmitTime, 0x44);
DOTD_ASSERT_OFFSET(CSparkNodeFx, m_unk4c, 0x4c);
DOTD_ASSERT_OFFSET(CSparkNodeFx, m_pSparkParam, 0x50);
DOTD_ASSERT_OFFSET(CSparkNodeFx, m_pSparks, 0x58);
