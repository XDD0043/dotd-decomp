// CKGroupBlocCinematicBloc.h - a group of cinematic elements (key 0x1c8, vtable 0xb1b3b0, size 0x48). Original unit: CKGroupBlocCinematicBloc.cpp.
// XXL2: the same members in the same order.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;

class CKGroupBlocCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x7)
    DOTD_DECLARE_FACTORIES(CKGroupBlocCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    // 0x0017c430 CKGroupBlocCinematicBloc_Create: IKCinematicBloc_Construct, then the vtable.
    CKGroupBlocCinematicBloc() {}
    ~CKGroupBlocCinematicBloc() override {}
    // vt+0x10 0x0017c818 CKGroupBlocCinematicBloc_Destroy: the element array deleted when there is one (kept).
    void Destroy() override {
        if (m_pEltPointer != nullptr) delete[] m_pEltPointer;  // TocBridge_OperatorDeleteArray
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0017cc38 CKGroupBlocCinematicBloc_Load
    // vt+0x24 0x0017c288 CKGroupBlocCinematicBloc_RecursiveRegistration: registered (unless 4..7), the base's, then every
    // element of the group's.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x58 0x0017c028 CKGroupBlocCinematicBloc_PreActivate: the group's first element (+0x40) pre-activated (vt+0x58).
    void PreActivate() override { static_cast<IKCinematicElement*>(m_pBegin)->PreActivate(); }

    // vt+0x5c 0x0017c908 CKGroupBlocCinematicBloc_Start: the blocs' start (StartCommon), the end element not completed,
    // the begin element activated, every element of the group flagged as having outputs (bit 4).
    void Start() override;
    // vt+0x64 0x0017ce68 CKGroupBlocCinematicBloc_Complete: CompleteBloc, every running element aborted (vt+0x70), all
    // flagged bit 4, the end element off the scene's running list.
    void Complete() override;
    // vt+0x68 0x0017c1b8 CKGroupBlocCinematicBloc_Update: completed once the end element has completed (bit 2) and has no
    // start / interrupt elements (+0x08 / +0x0a both 0xffff).
    void Update(IKTime* time) override;
    // vt+0x6c 0x0017c598 CKGroupBlocCinematicBloc_Stop: CompleteBloc, every running element stopped (bit 4 cleared, vt+0x6c),
    // then Complete (vt+0x64).
    void Stop() override;
    // vt+0x1c 0x0017c108 CKGroupBlocCinematicBloc_MessageProc: 0x501 stops the group (vt+0x6c, running or not) and
    // answers 0; anything else goes to the elements' MessageProc (its answer, 0 or 1).
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x70 0x0017c488 CKGroupBlocCinematicBloc_Abort: bit 0 of the element flags cleared; each element that runs
    // (bit 0) is aborted (vt+0x70), every one gets bit 4.
    void Abort() override;

    IKSerializable** m_pEltPointer;  // +0x38 IKCinematicElement references (new[]); not set when the count is 0
    uint32_t m_ui32EltNumber;        // +0x3c
    IKSerializable* m_pBegin;        // +0x40 IKCinematicElement
    IKSerializable* m_pEnd;          // +0x44 IKCinematicElement
};
DOTD_ASSERT_SIZE(CKGroupBlocCinematicBloc, 0x48);
DOTD_ASSERT_OFFSET(CKGroupBlocCinematicBloc, m_pEltPointer, +0x38);
DOTD_ASSERT_OFFSET(CKGroupBlocCinematicBloc, m_ui32EltNumber, +0x3c);
DOTD_ASSERT_OFFSET(CKGroupBlocCinematicBloc, m_pBegin, +0x40);
DOTD_ASSERT_OFFSET(CKGroupBlocCinematicBloc, m_pEnd, +0x44);
