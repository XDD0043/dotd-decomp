// IKKinematicsChain.h - the base of the bone chains that drive part of an animated node's hierarchy (unregistered key
// 0x10d, vtable 0xb16bd0, size 0x10; XXL2: K/KModules/KGL/KinematicsChain/IKKinematicsChain.h, the same members:
// CSBaseNode<IKKinematicsChain*>, m_pAnimatedNode, m_phierarchy). The chains are CKIKChain (0x14d) and CKAnimatedChain
// (0x18d); no game file holds either. Its inline IsKindOfClass copy is 0x99c4a0 (k2000/misc/Vt_3.cpp's list).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CAnimatedNode;
class IKTime;
struct RpHAnimHierarchy;

class IKKinematicsChain : public IKSerializable {
public:
    // The constructor (inlined in the Create factories, e.g. 0x8d088): the vtable, the next link null.
    IKKinematicsChain() : m_pNext(nullptr), m_pAnimatedNode(nullptr), m_pHierarchy(nullptr) {}
    ~IKKinematicsChain() override {}  // vt+0x00 / +0x04 0x99c558 / 0x99c518: the vtables only
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x10d || key == 0xc; }  // vt+0x08 0x99c4a0
    // vt+0x50 (pure; XXL2 GetBoneNumInHierarchy): the hierarchy node index of chain bone `bone`.
    virtual uint32_t GetBoneNumInHierarchy(uint32_t bone) = 0;
    // vt+0x54 (pure; XXL2 UpdateChain): one update of the chain with the frame clock.
    virtual void UpdateChain(IKTime* clock) = 0;

    IKKinematicsChain* m_pNext;       // +0x04 XXL2 CSBaseNode<IKKinematicsChain*>::m_pNext (a reference)
    CAnimatedNode* m_pAnimatedNode;   // +0x08 XXL2 m_pAnimatedNode (a reference)
    RpHAnimHierarchy* m_pHierarchy;   // +0x0c XXL2 m_phierarchy: the node's hierarchy (+0x2c), set by the Loads
};
DOTD_ASSERT_SIZE(IKKinematicsChain, 0x10);
DOTD_ASSERT_OFFSET(IKKinematicsChain, m_pNext, 0x04);
DOTD_ASSERT_OFFSET(IKKinematicsChain, m_pAnimatedNode, 0x08);
DOTD_ASSERT_OFFSET(IKKinematicsChain, m_pHierarchy, 0x0c);
