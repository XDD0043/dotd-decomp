#include "platform/cell/msgdialog.h"

#include <atomic>
#include <chrono>
#include <mutex>
#include <string>
#include <thread>

#include "platform/cell/cell_errors.h"
#include "platform/cell/pad.h"
#include "platform/log.h"

namespace {
std::mutex g_mutex;
bool g_open = false;
uint32_t g_type = 0;
std::string g_text;
CellMsgDialogCallback g_callback = nullptr;
void* g_userData = nullptr;
int32_t g_answer = CELL_MSGDIALOG_BUTTON_NONE;  // pending, delivered by the next poll
uint16_t g_lastButtons = 0xffff;                 // port 0's DIGITAL2 word at the last poll (all held at open)
}  // namespace

int32_t cellMsgDialogOpen2(uint32_t type, const char* msgString, CellMsgDialogCallback callback, void* userData,
                           void* /*extParam*/) {
    std::lock_guard<std::mutex> lock(g_mutex);
    if (g_open) return CellError(0x8002b301);  // CELL_MSGDIALOG_ERROR_DIALOG_NOT_OPENED: one at a time
    g_open = true;
    g_type = type;
    g_text = msgString != nullptr ? msgString : "";
    g_callback = callback;
    g_userData = userData;
    g_answer = CELL_MSGDIALOG_BUTTON_NONE;
    g_lastButtons = 0xffff;  // a button already held when the dialog opens does not answer it
    DOTD_LOG("msgdialog: open (type 0x%x): %s", type, g_text.c_str());
    return CELL_OK;
}

int32_t cellMsgDialogClose(float /*delayTime*/) {
    std::lock_guard<std::mutex> lock(g_mutex);
    if (!g_open) return CellError(0x8002b301);
    g_open = false;
    g_callback = nullptr;
    return CELL_OK;
}

namespace dotd::platform {
const char* MsgDialogText() {
    std::lock_guard<std::mutex> lock(g_mutex);
    return g_open ? g_text.c_str() : nullptr;
}

bool AnswerMsgDialog(int32_t buttonType) {
    std::lock_guard<std::mutex> lock(g_mutex);
    if (!g_open) return false;
    g_answer = buttonType;
    return true;
}

void MsgDialogPoll() {
    CellMsgDialogCallback callback = nullptr;
    void* userData = nullptr;
    int32_t answer = CELL_MSGDIALOG_BUTTON_NONE;
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        if (!g_open) return;
        if (g_answer == CELL_MSGDIALOG_BUTTON_NONE) {
            uint16_t words[24];
            uint16_t buttons = g_lastButtons;
            if (ReadPadWords(0, words)) buttons = words[CELL_PAD_BTN_OFFSET_DIGITAL2];
            const uint16_t pressed = static_cast<uint16_t>(buttons & ~g_lastButtons);
            g_lastButtons = buttons;
            const uint32_t kind = g_type & CELL_MSGDIALOG_TYPE_BUTTON_TYPE_MASK;
            if ((pressed & CELL_PAD_CTRL_CROSS) != 0 && kind != CELL_MSGDIALOG_TYPE_BUTTON_TYPE_NONE) {
                g_answer = CELL_MSGDIALOG_BUTTON_YES;
            } else if ((pressed & CELL_PAD_CTRL_CIRCLE) != 0) {
                if (kind == CELL_MSGDIALOG_TYPE_BUTTON_TYPE_YESNO) g_answer = CELL_MSGDIALOG_BUTTON_NO;
                else if ((g_type & CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON) == 0) g_answer = CELL_MSGDIALOG_BUTTON_ESCAPE;
            }
        }
        if (g_answer == CELL_MSGDIALOG_BUTTON_NONE) return;
        answer = g_answer;
        callback = g_callback;
        userData = g_userData;
        g_open = false;
        g_callback = nullptr;
        g_answer = CELL_MSGDIALOG_BUTTON_NONE;
    }
    DOTD_LOG("msgdialog: answered %d", answer);
    if (callback != nullptr) callback(answer, userData);
}

int32_t SystemMessageWait(const char* text) {
    std::atomic<int32_t> answer{CELL_MSGDIALOG_BUTTON_NONE};
    auto onAnswer = [](int32_t button, void* data) { static_cast<std::atomic<int32_t>*>(data)->store(button); };
    // One dialog at a time: wait for a game dialog to close first.
    while (cellMsgDialogOpen2(CELL_MSGDIALOG_TYPE_BUTTON_TYPE_OK, text, onAnswer, &answer, nullptr) != CELL_OK) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    while (answer.load() == CELL_MSGDIALOG_BUTTON_NONE) std::this_thread::sleep_for(std::chrono::milliseconds(1));
    return answer.load();
}
}  // namespace dotd::platform
