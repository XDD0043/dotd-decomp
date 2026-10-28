// CAnimatedNode.h - a scene node with a bone hierarchy (key 0x54b, vtable 0xb17e60, size 0x64). Original
// unit: CAnimatedNode.cpp. XXL2: K/KModules/KGL/SceneGraph/CAnimatedNode.h (m_pRootFrame,
// m_pRpHAnimHierarchy, the animation times and animations); DotD's layout differs after the hierarchy.
#pragma once
#include <cstdint>

#include "k2000/animation/AnimBlendSlot.h"
#include "k2000/core/Layout.h"
#include "k2000/scenegraph/CNode.h"

struct RwFrame;
struct RwMatrix;
struct RpHAnimHierarchy;
struct RtAnimAnimation;
class RenderQueue;
class IKTime;
struct RwCamera;

class CAnimatedNode : public CNode {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x15)
    DOTD_DECLARE_FACTORIES(CAnimatedNode)

    CAnimatedNode();  // 0x000c9480 CAnimatedNode_Construct (inlined in 0xcab28 CAnimatedNode_Create)
    ~CAnimatedNode() override {}

    // vt+0x2c 0x000ca4c0 CAnimatedNode_Load. No type check of its own (CNode's Load is called with the type).
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x000c9d48 CAnimatedNode_PostLoad: CNode's, then (type 0) the blend slot's PostLoad (0x79d70: returns 1),
    // the first animation (+0x5c, property bit 0) resolved and set on the controller, and every geometry's atomic given
    // the node's hierarchy (RpSkinAtomicSetHAnimHierarchy).
    int32_t PostLoad(int32_t type) override;
    // vt+0x54 0x000c9b88 CAnimatedNode_UpdateChildWorldMatrix_maybe: this node's LTM made current (the parent's update, or
    // the modelling matrix), then `child`'s LTM = its modelling matrix times this LTM, through the bone matrix of the
    // child's bone (+0x14) once the node has been drawn (+0x16 non-zero). The child frame's own LTM sync bit (4) cleared.
    void ChildWorldMatrixUpdate(CSGMovable* child) override;
    // vt+0x58 0x000cb0f0 PrepareAndEnqueueAnimatedNode: unless hidden (flag 4), the pose and the culling
    // (UpdatePoseAndCull); when visible, every geometry's atomic takes the node's world sphere and the geometries are
    // culled and queued (CNode's CullAndEnqueueNodeGeometry), the node stamped drawn.
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                          int32_t distanceCull) override;
    // 0x000cabc8 UpdateAnimatedNodePoseAndCull: while the clock runs, the animation time (with property bit 0 and
    // without bit 1: the controller's +0x50 += dt x speed +0x60) and a blend-slot node's crossfade (AdvanceInactiveTrack), the controller's
    // bounding sphere into `sphere` and the world one into `worldSphere`, the frustum test; the controller's state, and
    // when it has a pose to evaluate and the node is visible (or property 0x2000): Evaluate and RpHAnimHierarchyUpdateMatrices
    // through the evaluated interpolator, else Evaluate's time part only; the children hanging under bones get their LTM
    // (bone x node LTM, or the node's when not posed) and are traversed, then the other children. Returns visible.
    uint32_t UpdatePoseAndCull(RenderQueue** stages, IKTime* frameClock, float* sphere, float* worldSphere, RwCamera* camera);
    // 0x000c9a08 CAnimatedNode_SetHAnimHierarchy_maybe: the node's hierarchy (+0x2c) becomes `hierarchy` when it differs
    // or `forceUpdate`; `setOnRootFrame` also puts it on the bone root frame (RpHAnimFrameSetHierarchy). Every
    // geometry's atomic then gets it (CSkinGeometry_SetHAnimHierarchy_maybe 0x8b368). The controller (+0x30) is
    // stored last either way.
    void SetHAnimHierarchy(RpHAnimHierarchy* hierarchy, IKSerializable* controller, uint32_t forceUpdate,
                           uint32_t setOnRootFrame);

    // 0x000c99b8 CAnimatedNode_SetRootController_maybe: the node's animation controller.
    void SetRootController(IKSerializable* controller) { m_pController = controller; }

    // vt+0x78 0x000ca8a8 CAnimatedNode_RemoveChild_maybe: a child hanging under a bone leaves the attachment
    // list; any other goes through CSGBranch's.
    void RemoveChild(CSGLeaf* child) override;
    // 0x000c9218 CAnimatedNode_AttachChildToGroup_maybe (not virtual): `child` joins the attachment list right
    // behind the first entry whose bone byte equals the CHILD'S OWN current one (the byte before this call
    // sets it to `bone`), else at the head; then its parent is this node with `bone`.
    void AttachChildToGroup(uint8_t bone, CSGLeaf* child);

    // The node's animation, through one controller (property bits 9-10 = 1: +0x30) or through its blend slot's active
    // controller. 0x000c9978 CAnimatedNode_GetBlendSlot_maybe: *slot and *count = 1 for a node with a blend slot (bits = 2),
    // *count = 0 for one with a single controller; other nodes leave both alone.
    void GetBlendSlot(AnimBlendSlot** slot, int32_t* count);
    // 0x000c9638 AddAnimTime_maybe / 0x000c95a8 GetCurrentAnimTime_maybe (+0x54, the evaluated time) / 0x000c95f0
    // GetAnimTimeNow_maybe (+0x50) / 0x000c9690 SetCurrentAnimTime_maybe (+0x50) / 0x000c9720 GetActiveAnim_maybe (+0x5c:
    // the evaluated animation, as a dictionary word) / 0x000c96d8 GetCurrentAnim_maybe (+0x58) / 0x000c9768
    // GetCurrentAnimDuration_maybe / 0x000ca368 IsAnimEndReached_maybe / 0x000c98b8 PlayAnim_maybe / 0x000c8eb0
    // CrossfadeToAnim_maybe / 0x000c97d8 RestartCurrentAnim_maybe (the controller's Reset, vt+0x60: no animation) /
    // 0x000c8e80 SetBlendAnimPairAndWeight_maybe. The animations are dictionary words (CAnimationManager_GetAnimation).
    void AddAnimTime(double dt);
    float GetCurrentAnimTime() const;
    float GetAnimTimeNow() const;
    void SetCurrentAnimTime(float time);
    uint32_t GetActiveAnim() const;
    RtAnimAnimation* GetCurrentAnim() const;
    float GetCurrentAnimDuration() const;
    bool IsAnimEndReached(double dt) const;
    void PlayAnim(double start, uint32_t word, uint32_t restart);
    void PlayAnim(float start, RtAnimAnimation* animation, uint32_t restart);
    void CrossfadeToAnim(double blend, double start, uint32_t word, uint32_t mode);
    void RestartCurrentAnim();
    void SetBlendAnimPairAndWeight(uint32_t word1, uint32_t word2, float start1, float start2, float weight);
    // 0x0099b448 CAnimatedNode_PlayAnimAtTime_maybe (inline): with `play`, the animation from 0 (restarted; without one,
    // `reset` plays none and resets); then with `setTime` the time when it is inside the animation. Returns whether the
    // animation is not at its end (0 when nothing was set).
    uint32_t PlayAnimAtTime(RtAnimAnimation* animation, float time, uint32_t play, uint32_t setTime, uint32_t reset);
    // 0x000c8bd8 CAnimatedNode_GetBoneMatrix: the hierarchy's matrix `bone`.
    RwMatrix* GetBoneMatrix(uint32_t bone) const;
    // 0x000c8bf0 CAnimatedNode_GetSubtreeBoneCount: the nodes of the subtree from `start` (the push/pop flags; the whole
    // hierarchy's low byte for 0); 0 without a hierarchy.
    uint8_t GetSubtreeBoneCount(uint8_t start) const;
    // The controller that animates the node now (see above).
    class CKAnmKeyFrameController* ActiveController() const;

    RwFrame* m_pRootFrame;                    // +0x24 the bone frame list's first frame (under the node's frame)
    CSGLeaf* m_pAttachmentHead;               // +0x28 a reference: the children attached to bones, grouped by bone
                                              // (they chain through CSGLeaf::m_pNext; CAnimatedNode_AttachChildToGroup)
    RpHAnimHierarchy* m_pRpHAnimHierarchy;    // +0x2c the root frame's HAnim hierarchy, or null
    IKSerializable* m_pController;            // +0x30 the animation controller (a CKBlenderController)
    AnimBlendSlot m_blendSlot;                // +0x34 read when the properties' bits 9-10 are 2
    uint32_t m_aUnk4c[4];                     // +0x4c one 0x10 read, each word swapped
    uint32_t m_unk5c;                         // +0x5c an animation index (property bit 0), else 0xffffffff
    float m_unk60;                            // +0x60 the constructor sets 1.0f; read last
};
static_assert(CAnimatedNode::kClassKey == 0x54b, "key");
DOTD_ASSERT_SIZE(CAnimatedNode, 0x64);
DOTD_ASSERT_OFFSET(CAnimatedNode, m_pRootFrame, 0x24);
DOTD_ASSERT_OFFSET(CAnimatedNode, m_pAttachmentHead, 0x28);
DOTD_ASSERT_OFFSET(CAnimatedNode, m_pRpHAnimHierarchy, 0x2c);
DOTD_ASSERT_OFFSET(CAnimatedNode, m_pController, 0x30);
DOTD_ASSERT_OFFSET(CAnimatedNode, m_blendSlot, 0x34);
DOTD_ASSERT_OFFSET(CAnimatedNode, m_aUnk4c, 0x4c);
DOTD_ASSERT_OFFSET(CAnimatedNode, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CAnimatedNode, m_unk60, 0x60);

// 0x000c8ef8 IKFile_ReadBoneFrameList: a count; when positive, the RW frame list (chunk 0xe) whose first
// frame becomes *rootFrame and its HAnim hierarchy *hierarchy (every matrix reset to the identity), the
// root frame put under `parent` when there is one. A count of 0 or less: *hierarchy = null only.
int32_t IKFile_ReadBoneFrameList(IKFile* file, int32_t type, RwFrame** rootFrame, RpHAnimHierarchy** hierarchy,
                                 RwFrame* parent);
