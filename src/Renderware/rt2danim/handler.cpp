// handler.cpp - RW 3.7 tool/2danim/handler.c (0x6f7f48-0x6f87a0): the maestro's message handler and the
// default one, ported from the PS3 library code. See Rt2dAnim.h.
//
// Anim node flags the handler uses: bit 0 stopped, bit 1 "the frame changed" (its frame messages are
// posted by the next _rt2dMaestroAnimNodeAddDeltaTimeCallBack), bit 2 visible in the last walk.
#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rt2danim/Rt2dAnimPrivate.h"

// 0x006f7f48 Rt2dMaestroGetMessageHandler_maybe
Rt2dMessageHandlerCallBack Rt2dMaestroGetMessageHandler(Rt2dMaestro* maestro) { return maestro->messageHandler; }

// 0x006f7f50 Rt2dMaestroSetMessageHandler_maybe
Rt2dMaestro* Rt2dMaestroSetMessageHandler(Rt2dMaestro* maestro, Rt2dMessageHandlerCallBack handler) {
    maestro->messageHandler = handler;
    return maestro;
}

namespace {
// The goto the frame messages share: GotoKeyFrameListByIndex, then mark the frame changed.
void GotoFrame(Rt2dAnimNode* node, RwInt32 frameIndex) {
    Rt2dAnimGotoKeyFrameListByIndex(&node->anim, &node->props, frameIndex);
    node->flag |= 2;
}
}  // namespace

// 0x006f7f60 Rt2dMessageHandlerDefaultCallBack (jump table at 0x6f7fe8). Returns the message, or null
// for an unknown type, NULL (0) and SPECIALTELLTARGET (12, resolved when posted).
//   1 PLAY / 2 STOP: clear / set the node's stopped flag.
//   3 NEXTFRAME / 4 PREVFRAME / 5 GOTOFRAME / 6 GOTOLABEL: go to the frame and mark it changed.
//   7 GETURL / 9 FOREIGN: nothing (the game's own handler takes GETURL, CKFlashUI_MaestroMessageHandler).
//   8 DOACTION: post message list intParam1.
//   10 MOUSEMOVETO: the mouse position in the maestro's units. 11 MOUSEBUTTONSTATE: the button state
//   machine of every button of every animation's current cel. 13 BUTTONBYLABEL: the action of the button
//   labelled intParam1 in animation index's current cel for the transition mask intParam2.
Rt2dMessage* Rt2dMessageHandlerDefaultCallBack(Rt2dMaestro* maestro, Rt2dMessage* message) {
    switch (message->messageType) {
        case rt2dMESSAGETYPEPLAY: {
            Rt2dAnimNode* node = _rt2dMaestroGetAnimNodeByIndex(maestro, message->index);
            node->flag &= ~1;
            return message;
        }
        case rt2dMESSAGETYPESTOP: {
            Rt2dAnimNode* node = _rt2dMaestroGetAnimNodeByIndex(maestro, message->index);
            node->flag |= 1;
            return message;
        }
        case rt2dMESSAGETYPENEXTFRAME: {
            Rt2dAnimNode* node = _rt2dMaestroGetAnimNodeByIndex(maestro, message->index);
            const RwInt32 next = Rt2dAnimGetNextFrameIndex(&node->anim);
            if (next >= Rt2dAnimGetNumKeyFrameLists(&node->anim)) return message;
            GotoFrame(node, next);
            return message;
        }
        case rt2dMESSAGETYPEPREVFRAME: {
            Rt2dAnimNode* node = _rt2dMaestroGetAnimNodeByIndex(maestro, message->index);
            const RwInt32 prev = Rt2dAnimGetPrevFrameIndex(&node->anim) - 1;
            if (prev < 0) return message;
            GotoFrame(node, prev);
            return message;
        }
        case rt2dMESSAGETYPEGOTOFRAME: {
            Rt2dAnimNode* node = _rt2dMaestroGetAnimNodeByIndex(maestro, message->index);
            GotoFrame(node, message->intParam1);
            return message;
        }
        case rt2dMESSAGETYPEGOTOLABEL: {
            Rt2dAnimNode* node = _rt2dMaestroGetAnimNodeByIndex(maestro, message->index);
            Rt2dStringLabel* label = Rt2dMaestroGetStringLabelByIndex(maestro, message->intParam1);
            GotoFrame(node, Rt2dStringLabelData(label));
            return message;
        }
        case rt2dMESSAGETYPEGETURL:
        case rt2dMESSAGETYPEFOREIGN:
            return message;
        case rt2dMESSAGETYPEDOACTION:
            _rt2dMaestroMessageListPostByIndex(maestro, message->intParam1);
            return message;
        case rt2dMESSAGETYPEMOUSEMOVETO: {
            // fcfid + frsp, then fmuls, fmuls / fmuls, fsubs.
            const RwReal x = static_cast<RwReal>(message->intParam1);
            maestro->prevMouse.position.x = x * maestro->invWinW * maestro->winAspectRatio;
            const RwReal y = static_cast<RwReal>(message->intParam2);
            maestro->prevMouse.position.y = 1.0f - y * maestro->invWinH;
            return message;
        }
        case rt2dMESSAGETYPEMOUSEBUTTONSTATE: {
            const RwInt32 button = message->intParam1;
            const RwInt32 prevButton = maestro->prevMouse.button;
            const RwInt32 count = _rwSListGetNumEntries(maestro->animations);
            Rt2dAnimNode* node = RwSListArray<Rt2dAnimNode>(maestro->animations);
            const RwInt32 savedIndex = maestro->currAnimIndex;
            for (RwInt32 i = 0; i < count; ++i, ++node) {
                maestro->currAnimIndex = i;
                Rt2dObject* scene = Rt2dMaestroGetAnimSceneByIndex(maestro, i);
                Rt2dCel* cel = _rt2dCelListGetCelByIndex(node->celList, Rt2dAnimGetPrevFrameIndex(&node->anim));
                const RwInt32 numButtons = _rwSListGetNumEntries(cel->buttonIndices);
                RwInt32* buttonIndex = RwSListArray<RwInt32>(cel->buttonIndices);
                for (RwInt32 k = 0; k < numButtons; ++k, ++buttonIndex) {
                    Rt2dButton* b = _rt2dMaestroGetButtonByIndex(maestro, *buttonIndex);
                    if ((b->stateFlag & 1u) == 0) continue;
                    Rt2dObject* object = Rt2dSceneGetChildByIndex(scene, b->objectIndex);
                    // stateTransTable[over][prevButton][over][button], "over" being buttonState bit 0
                    // (the PS3 build has no pick test: both "over" indices are the same bit). The
                    // button values are not range-checked (flat index, as the PS3 computes it).
                    const RwInt32 over = static_cast<RwInt32>(b->buttonState & 1u);
                    const Rt2dStateTransData* trans = &maestro->stateTransTable[0][0][0][0] +
                                                      (((over * 2 + prevButton) * 2 + over) * 2 + button);
                    RwInt32 transState = trans->transState;
                    RwInt32 child = 1;
                    if ((b->stateFlag & 2u) != 0) {
                        Rt2dObjectSetVisible(Rt2dSceneGetChildByIndex(object, 1), trans->buttonUpImg);
                        child = 2;
                    }
                    if ((b->stateFlag & 4u) != 0) {
                        Rt2dObjectSetVisible(Rt2dSceneGetChildByIndex(object, child), trans->buttonDownImg);
                        ++child;
                    }
                    if ((b->stateFlag & 8u) != 0) {
                        Rt2dObjectSetVisible(Rt2dSceneGetChildByIndex(object, child), trans->buttonOverImg);
                    }
                    RwUInt32 stateFlag = b->stateFlag;
                    if ((stateFlag & static_cast<RwUInt32>(transState)) != 0) {
                        // The action slot: -1 plus the number of transitions the button has (stateFlag
                        // bits from 4 up) among the first ones up to the transition's bit (srawi).
                        RwInt32 slot = -1;
                        if (transState != 0) {
                            RwInt32 bits = static_cast<RwInt32>(stateFlag >> 4);
                            for (;;) {
                                transState >>= 1;
                                slot += bits & 1;
                                if (transState == 0) break;
                                bits >>= 1;
                            }
                        }
                        // BUG(original): slot -1 (no transition bit at or below) reads buttonState.
                        const RwInt32 action = *reinterpret_cast<const RwInt32*>(
                            reinterpret_cast<const RwUInt8*>(b) + 0x10 + slot * 4);
                        if (action >= 0) _rt2dMaestroMessageListPostByIndex(maestro, action);
                    }
                    if (button != 0) {
                        b->buttonState |= 2u;
                    } else {
                        b->buttonState &= ~2u;
                    }
                }
            }
            maestro->prevMouse.button = button;
            maestro->currAnimIndex = savedIndex;
            return message;
        }
        case rt2dMESSAGETYPEBUTTONBYLABEL: {
            Rt2dAnimNode* node = _rt2dMaestroGetAnimNodeByIndex(maestro, message->index);
            const RwInt32 label = message->intParam1;
            if (label < 0) return nullptr;
            const RwInt32 celIndex = Rt2dAnimGetPrevFrameIndex(&node->anim);
            Rt2dCel* cel = _rt2dCelListGetCelByIndex(node->celList, celIndex);
            const RwInt32 numButtons = _rwSListGetNumEntries(cel->buttonIndices);
            for (RwInt32 k = 0; k < numButtons; ++k) {
                RwInt32 buttonLabel = 0;
                _rt2dCelListGetButtonLabelIndex(maestro, node->celList, celIndex, k, &buttonLabel);
                if (label != buttonLabel) continue;
                const RwInt32* buttonIndex = RwSListEntry<RwInt32>(cel->buttonIndices, k);
                RwUInt32 mask = static_cast<RwUInt32>(message->intParam2);
                Rt2dButton* b = _rt2dMaestroGetButtonByIndex(maestro, *buttonIndex);
                const RwUInt32 stateFlag = b->stateFlag;
                if ((mask & stateFlag) == 0) return message;
                RwInt32 slot = -1;
                if (mask != 0) {
                    RwUInt32 bits = stateFlag >> 4;  // srwi here (logical shifts)
                    for (;;) {
                        mask >>= 1;
                        slot += static_cast<RwInt32>(bits & 1u);
                        if (mask == 0) break;
                        bits >>= 1;
                    }
                }
                const RwInt32 action =
                    *reinterpret_cast<const RwInt32*>(reinterpret_cast<const RwUInt8*>(b) + 0x10 + slot * 4);
                if (action < 0) return message;
                const RwInt32 savedIndex = maestro->currAnimIndex;
                maestro->currAnimIndex = message->index;
                _rt2dMaestroMessageListPostByIndex(maestro, action);
                maestro->currAnimIndex = savedIndex;
                return message;
            }
            return message;
        }
        default:  // NULL, SPECIALTELLTARGET and anything above 13
            return nullptr;
    }
}
