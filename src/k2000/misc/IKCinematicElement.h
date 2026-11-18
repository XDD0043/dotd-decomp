// IKCinematicElement.h - the elements of a cinematic scene (key 0x808, abstract; XXL2:
// K/KServices/KServiceCinematic/CinematicElement/IKCinematicElement.h). PS3 size 0x20.
//
// Two families derive from it: the blocs (IKCinematicBloc: play an animation, a sound, move the camera,
// ...) and the logical doors (IKLogicalDoor: CKStartDoor, CKEndDoor, CKLogicalAnd, CKLogicalOr), which
// join the blocs into a graph. The members are XXL2's in the same order (XXL2 has a debug block first
// and 64-bit pointers); each family loads them with its own BasicLoadCinematicElement.
// The runtime slots (vt+0x50..+0x7c) are declared below (C2.3).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKCinematicScene;
class IKTime;

// IsKindOfClass of an element class: its own key, its family's (0x84c IKCinematicBloc / 0x88c IKLogicalDoor), 0x808
// (IKCinematicElement) and the root key 0xc (the inline 0x9a9190 CKStartDoor_IsKindOfClass and its siblings).
#define DOTD_BLOC_IS_KIND_OF()                                                                                      int32_t IsKindOfClass(uint32_t key) override {                                                                      return key == kClassKey || key == 0x84c || key == 0x808 || key == 0xc;                                      }
#define DOTD_DOOR_IS_KIND_OF()                                                                                      int32_t IsKindOfClass(uint32_t key) override {                                                                      return key == kClassKey || key == 0x88c || key == 0x808 || key == 0xc;                                      }

class IKCinematicElement : public IKSerializable {
public:
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x808 || key == 0xc; }  // IKCinematicElement (0x9aa5d8)
    int32_t GetClassType() override { return 8; }     // vt+0x14 0x9aa5c8 (LwMutex.cpp's COMDAT range)
    int32_t GetClassID() override { return 0x20; }    // vt+0x18 0x9aa5d0
    IKCinematicElement();  // 0x0018f438 IKCinematicElement_Construct
    ~IKCinematicElement() override {}

    // The elements' runtime slots, in vtable order (DotD's; XXL2's PreStart/StartElement/EndElement/UpdateElement/
    // InterruptElement/Stop/Pause/Resume are the same machine with different slots: +0x58 PreActivate and +0x74
    // OnSceneStopped are DotD's). Bodies here are the shared stubs of the original vtables
    // (0x9a8d98 / 0x9a8da0 / 0x9a8da8 / 0x9a8e58 / 0x9a8df0 / 0x9a8df8 / 0x9a8e00 are empty). The state byte is
    // m_DataFlags: bit 0 running, bit 1 updating, bit 2 completed, bit 3 stop requested, bit 4 has outputs.
    // vt+0x50 0x9a8d98 PreStart (XXL2 PreStart): the scene's ResetNodesRuntime calls it on every element.
    // CKStreamAnimCinematicBloc 0x18bde8 CKStreamAnimCinematicBloc_ResetRuntime overrides it.
    virtual void PreStart() {}
    // vt+0x54 0x9a8da0: the scene's ReinitBlocksRuntime (the service Stop) calls it. CKStreamAnimCinematicBloc
    // 0x18bdc0 (InitChannels) overrides it.
    virtual void Vf54() {}
    // vt+0x58 0x9a8da8: called on an output element right before it is activated (CKStartDoor_Start) and on the
    // scene's first element at scene start. CKAdvancedCamera/BlackBand/CharacterControl/DisplayPicture/GroupBloc/
    // ManageCamera/PlaySound/PlayVideo/Sekensor/StartEvent blocs override it.
    virtual void PreActivate() {}
    // vt+0x5c Start (XXL2 StartElement): the element begins. The doors' Starts activate or complete them.
    virtual void Start() {}
    // vt+0x60 0x9a8db0 IKCinematicElement_Activate: Start for everything but CKLogicalAnd (ActivateInput(source)).
    virtual void Activate(IKCinematicElement* /*source*/) { Start(); }
    // vt+0x64 Complete (XXL2 EndElement): the element is done; its outputs are activated.
    virtual void Complete() {}
    // vt+0x68 Update (XXL2 UpdateElement): the scene calls it every frame on a running element with bit 1 set.
    virtual void Update(IKTime* /*time*/) {}
    // vt+0x6c 0x9a8e58 Stop (XXL2 Stop); the doors have the empty one.
    virtual void Stop() {}
    // vt+0x70 Abort (XXL2 InterruptElement): the scene's end aborts the running elements.
    virtual void Abort() {}
    // vt+0x74 0x9a8df0 (empty); CKStreamAnimCinematicBloc 0x18bb80 OnSceneStopped overrides it.
    virtual void OnSceneStopped() {}
    // vt+0x78 0x9a8df8 / vt+0x7c 0x9a8e00 (empty): CKCinematicScene_PauseActiveNodes / ResumeActiveNodes (XXL2
    // Pause / Resume) call them on every running element with bit 1 set.
    virtual void Pause() {}
    virtual void Resume() {}

    // 0x0018faf8 IKCinematicElement_MessageProc (vt+0x1c of every element but CKFlaggedPath / CKFlashUI / CKGroupBloc,
    // whose own MessageProcs call it first): 0x500 starts a stopped element of a playing scene (PreActivate, then
    // CKSrvCinematic::ActivateNode from no source), 0x501 stops a running one (vt+0x6c); both answer 0, anything else 1.
    int32_t MessageProc(uint16_t message, void* data) override { return ElementMessageProc(message, data); }
    int32_t ElementMessageProc(uint16_t message, void* data);

    IKCinematicElement* m_pNext;                // +0x04 XXL2 CSBaseNode<IKCinematicElement*> (the scene's lists); 0
    uint16_t m_ui16StartElementsFirstIndex;     // +0x08
    uint16_t m_ui16InterruptElementsFirstIndex; // +0x0a
    uint16_t m_ui16ElementsNumber;              // +0x0c
    uint16_t m_pad0e;
    IKSerializable* m_pElementData;             // +0x10 CKCinematicSceneData (the doors clear it)
    uint32_t m_DataFlags;                       // +0x14 CBitArray; the Loads clear bit 0 (doors) or bits 0 and 2 (blocs)
    IKCinematicElement* m_pParentGroup;         // +0x18
    CKCinematicScene* m_pRelatedScene;          // +0x1c 0 in the constructor
};
DOTD_ASSERT_SIZE(IKCinematicElement, 0x20);
DOTD_ASSERT_OFFSET(IKCinematicElement, m_pNext, 0x04);
DOTD_ASSERT_OFFSET(IKCinematicElement, m_ui16StartElementsFirstIndex, 0x08);
DOTD_ASSERT_OFFSET(IKCinematicElement, m_ui16InterruptElementsFirstIndex, 0x0a);
DOTD_ASSERT_OFFSET(IKCinematicElement, m_ui16ElementsNumber, 0x0c);
DOTD_ASSERT_OFFSET(IKCinematicElement, m_pElementData, 0x10);
DOTD_ASSERT_OFFSET(IKCinematicElement, m_DataFlags, 0x14);
DOTD_ASSERT_OFFSET(IKCinematicElement, m_pParentGroup, 0x18);
DOTD_ASSERT_OFFSET(IKCinematicElement, m_pRelatedScene, 0x1c);
