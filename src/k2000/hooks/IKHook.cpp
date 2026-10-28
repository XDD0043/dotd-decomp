// IKHook.cpp - the parts of IKHook (key 0x2, vtable 0xb132f0) that are not inline in the header.
#include "k2000/hooks/IKHook.h"

#include "k2000/scenegraph/CAnimatedNode.h"

// 0x00019a90 IKHook_vfBC: CAnimatedNode_GetBlendSlot_maybe 0xc9978 on the hook's scene node (+0x1c).
void IKHook::GetBlendSlot(AnimBlendSlot** slot, int32_t* count) {
    static_cast<CAnimatedNode*>(m_pKGLObject)->GetBlendSlot(slot, count);
}
