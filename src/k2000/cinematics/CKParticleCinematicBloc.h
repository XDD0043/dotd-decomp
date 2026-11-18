// CKParticleCinematicBloc.h - a cinematic bloc that switches particle nodes on and off (key 0x308, vtable 0xb1b610, size
// 0x48). Original unit: CKParticleCinematicBloc.cpp (0x1803c0-0x1814d0). XXL2: CKParticleCinematicBloc with
// m_apParticleArray, m_ui32ParticleNb, m_fTimeForActivation, m_fStartTime in the same order (no level file holds the
// class: nothing exercises it). The bloc's flag bits (m_DataFlags): 0x80 the nodes are shown too (0x200 | 0x400),
// 0x100 timed (stopped m_fTimeForActivation seconds after the first update), 0x200 the nodes keep emitting after the bloc
// (XXL2 GetNeverDesactive; the Start completes the bloc at once).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;
class IKTime;

class CKParticleCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0xc)
    DOTD_DECLARE_FACTORIES(CKParticleCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    // 0x00180828 CKParticleCinematicBloc_Create: IKCinematicBloc_Construct, then the vtable (the members are the Load's).
    CKParticleCinematicBloc() {}
    ~CKParticleCinematicBloc() override {}

    // vt+0x10 0x00180b10 CKParticleCinematicBloc_Destroy: the node array freed (the pointer is not cleared).
    void Destroy() override;
    // vt+0x24 0x00180880 CKParticleCinematicBloc_RecursiveRegistration: registered (unless 4..7), the base's, then every
    // node without a parent (CSGLeaf +0x0c) with the same type.
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00180448 CKParticleCinematicBloc_Load
    // vt+0x30 0x001809a0 CKParticleCinematicBloc_PostLoad: the base's; in a level load every node's scene property 0x1000.
    int32_t PostLoad(int32_t type) override;

    void Start() override;                 // vt+0x5c 0x00180f00 CKParticleCinematicBloc_Start
    void Complete() override;              // vt+0x64 0x001812e0 CKParticleCinematicBloc_Complete
    void Update(IKTime* time) override;    // vt+0x68 0x00180a38 CKParticleCinematicBloc_Update
    void Stop() override;                  // vt+0x6c 0x00180c00 CKParticleCinematicBloc_Stop
    void Abort() override;                 // vt+0x70 0x00180e60 CKParticleCinematicBloc_Abort

    // The nodes' emission switched off (scene properties 0x400 and 0x80000, the emitter's emit flag 0x8), inlined in Stop
    // and Abort; nothing with flag 0x200 (never deactivated).
    void StopNodes();

    IKSerializable** m_apParticleArray;  // +0x38 CParticlesNodeFx references (new[]; null for none)
    uint32_t m_ui32ParticleNb;           // +0x3c
    float m_fTimeForActivation;          // +0x40
    float m_fStartTime;                  // +0x44 -1 until the first update after a start (the scalable time then)
};
DOTD_ASSERT_SIZE(CKParticleCinematicBloc, 0x48);
DOTD_ASSERT_OFFSET(CKParticleCinematicBloc, m_apParticleArray, 0x38);
DOTD_ASSERT_OFFSET(CKParticleCinematicBloc, m_ui32ParticleNb, 0x3c);
DOTD_ASSERT_OFFSET(CKParticleCinematicBloc, m_fTimeForActivation, 0x40);
DOTD_ASSERT_OFFSET(CKParticleCinematicBloc, m_fStartTime, 0x44);
