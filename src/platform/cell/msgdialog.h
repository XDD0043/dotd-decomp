// msgdialog.h - cellMsgDialog as the game uses it: the system's YES/NO and OK dialogs (the save-data
// messages). The PS3 draws them over the game and answers through the callback on the thread that calls
// cellSysutilCheckCallback. Here the dialog is logged; port 0's Cross / Circle presses answer it (Cross is
// YES / OK, Circle NO, as the US system's enter-button assignment), or a test answers it directly.
#pragma once
#include <cstdint>

enum : uint32_t {
    CELL_MSGDIALOG_TYPE_BUTTON_TYPE_NONE = 0x00,
    CELL_MSGDIALOG_TYPE_BUTTON_TYPE_YESNO = 0x10,
    CELL_MSGDIALOG_TYPE_BUTTON_TYPE_OK = 0x20,
    CELL_MSGDIALOG_TYPE_BUTTON_TYPE_MASK = 0x70,
    CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON = 0x80,
};

enum : int32_t {
    CELL_MSGDIALOG_BUTTON_NONE = -1,
    CELL_MSGDIALOG_BUTTON_INVALID = 0,
    CELL_MSGDIALOG_BUTTON_OK = 1,
    CELL_MSGDIALOG_BUTTON_YES = 1,
    CELL_MSGDIALOG_BUTTON_NO = 2,
    CELL_MSGDIALOG_BUTTON_ESCAPE = 3,
};

typedef void (*CellMsgDialogCallback)(int32_t buttonType, void* userData);

int32_t cellMsgDialogOpen2(uint32_t type, const char* msgString, CellMsgDialogCallback callback, void* userData,
                           void* extParam);
int32_t cellMsgDialogClose(float delayTime);

namespace dotd::platform {
// The open dialog's text, or null.
const char* MsgDialogText();
// Answers the open dialog (delivered at the next cellSysutilCheckCallback). False when none is open.
bool AnswerMsgDialog(int32_t buttonType);
// cellSysutilCheckCallback: reads port 0's buttons for an answer, then delivers a pending one.
void MsgDialogPoll();
// A message of the system's own UI (cellSaveData's "There is no saved data.", ...): an OK dialog the
// calling worker thread waits on until it is answered, as the PS3's modal system UI blocks the caller.
// Never call it from the thread that runs cellSysutilCheckCallback. Returns the button.
int32_t SystemMessageWait(const char* text);
}  // namespace dotd::platform
