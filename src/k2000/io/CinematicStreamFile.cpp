// CinematicStreamFile.cpp - reconstructed original translation unit 0x7e978-0x7f698 (GAME_TOC1, main_toc1), 17 functions, 15 live.
// Primary owner: CinematicStreamFile (not a registered class)
// Other owners: CinematicStream (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x7e978  CinematicStreamFile_Init_2_maybe  [dead]
//   [x] 0x7e9b0  CinematicStreamFile_Close_maybe
//   [ ] 0x7ea60  CinematicStreamFile_Init_3_maybe  [dead]
//   [x] 0x7ea98  CinematicStreamFile_Init_maybe
//   [x] 0x7ead0  CinematicStreamFile_Open_maybe
//   [x] 0x7ec58  CinematicStreamFile_ContinueRead_maybe
//   [x] 0x7f088  CinematicStreamFile_RequestRead_maybe
//   [x] 0x7f208  CinematicStreamFile_RtFSCallback_maybe
//   [x] 0x7f3e0  KStub_Nop_7f3e0  (ConstructBase calls it twice; nothing to do)
//   [x] 0x7f3e8  CinematicStream_ResolveAnimatedNode_maybe
//   [x] 0x7f4d8  CinematicStream_IsActorSceneLeaf_maybe
//   [x] 0x7f530  KStub_Nop_7f530  (type 0's reset slot, ConstructBase)
//   [x] 0x7f538  KStub_Nop_7f538  (type 0's init slot, ConstructBase)
//   [x] 0x7f540  CinematicStream_SaveActorMatrix_maybe
//   [x] 0x7f680  KStub_Return36_7f680
//   [x] 0x7f688  KStub_Nop_7f688  (type 2's reset slot, ConstructBase)
//   [x] 0x7f690  KStub_Nop_7f690  (type 2's init slot, ConstructBase)
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/animation/AnimBlendSlot.h"
#include "k2000/components/CKCinematicStreamCpnt.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "platform/cell/cell_errors.h"
#include "platform/cell/fs.h"
#include "platform/fps.h"

// Platform equivalent, not a port: the RtFS calls the stream file makes (RenderWare's rtfsyst toolkit: RW 3.7.0.2 has
// only its header and library, and the remake reads files synchronously through the cellFs shim, KFileStream.h). A
// file opened for asynchronous reads (flags 0x11) reports to its callback: 2 when it is open, 5 with the bytes a read
// gave, 3 when it failed. The PS3 ran the callback later from the host file system's request thread; the game sees it
// in its next poll (CKCinematicStreamCpnt_UpdateStream). C2.8 chase-l20-1: the remake reads at once but holds the
// callback back by the PS3's latency, counted in frames (the render frame counter): the open is seen in the next frame,
// a read two frames after it was asked for (every stream start and chunk read of the recordings: lvl020-full +0 open,
// +1 header read, +3 the first chunk dispatched (a scripted NPC's stream: its animation starts three frames after the
// block); G +8932 / +8933 / +8935 and +11514 / +11515 / +11517; the chunk reads +65 / +67, +125 / +127, ... in
// calls.jsonl). What the 0x20000-byte buffer already holds is copied at once, as on the PS3 (no RtFS read).
struct RtFSFile {
    int32_t m_fd;
    uint32_t m_size;
    uint32_t m_position;
    void (*m_pfnCallback)(RtFSFile* file, uint32_t bytes, uint32_t unused, int32_t event, SCinematicStreamFile* context);
    SCinematicStreamFile* m_pContext;
};

namespace {

constexpr const char* kRoot = "/dev_bdvd/PS3_GAME/USRDIR";  // KHostFS_BuildPath (KFileStreamHost.cpp)

bool RtFS_FileExists(const char* path) {
    const std::string full = std::string(kRoot) + "/" + path;
    CellFsStat st;
    return cellFsStat(full.c_str(), &st) == CELL_OK;
}

// A callback held back: its file, bytes and event, the render frame counter it was asked in and the frames it takes.
struct RtFSPending {
    RtFSFile* file;
    uint32_t bytes;
    int32_t event;
    uint16_t asked;
    uint16_t frames;
    uint32_t askedTick;  // --fps N (platform/fps.h): the 60 Hz frame count it was asked at
};
std::vector<RtFSPending>& Pending() {
    static std::vector<RtFSPending> pending;
    return pending;
}
constexpr uint16_t kOpenFrames = 1;
constexpr uint16_t kReadFrames = 2;

// The frames since `asked` (the counter runs 1 .. 0xfffe).
uint16_t FramesSince(uint16_t asked) {
    int32_t d = static_cast<int32_t>(g_ui16RenderFrameCounter) - static_cast<int32_t>(asked);
    if (d < 0) d += 0xfffe;
    return static_cast<uint16_t>(d);
}

RtFSFile* RtFS_FileOpen(const char* path, uint32_t /*flags*/, decltype(RtFSFile::m_pfnCallback) callback,
                        SCinematicStreamFile* context) {
    const std::string full = std::string(kRoot) + "/" + path;
    CellFsStat st;
    if (cellFsStat(full.c_str(), &st) != CELL_OK) return nullptr;
    int32_t fd = -1;
    if (cellFsOpen(full.c_str(), CELL_FS_O_RDONLY, &fd, nullptr, 0) != CELL_OK) return nullptr;
    RtFSFile* file = new RtFSFile{fd, static_cast<uint32_t>(st.size), 0, callback, context};
    Pending().push_back({file, 0, 2, g_ui16RenderFrameCounter, kOpenFrames, dotd::fps::TickCount()});  // open
    return file;
}

void RtFS_FileRead(void* buffer, uint32_t size, uint32_t count, RtFSFile* file) {
    uint64_t got = 0;
    const uint32_t want = size * count;
    if (cellFsRead(file->m_fd, buffer, want, &got) != CELL_OK) got = 0;
    file->m_position += static_cast<uint32_t>(got);
    // nothing more: the read failed (3); else the bytes it gave (5)
    Pending().push_back({file, static_cast<uint32_t>(got), got == 0 ? 3 : 5, g_ui16RenderFrameCounter, kReadFrames,
                         dotd::fps::TickCount()});
}

void RtFS_FileCancelAsync(RtFSFile* file) {
    std::vector<RtFSPending>& pending = Pending();
    for (size_t i = 0; i < pending.size();) {
        if (pending[i].file == file) pending.erase(pending.begin() + static_cast<std::ptrdiff_t>(i));
        else ++i;
    }
}

void RtFS_FileClose(RtFSFile* file) {
    RtFS_FileCancelAsync(file);
    cellFsClose(file->m_fd);
    delete file;
}

}  // namespace

void CinematicStreamFile_RtFSCallback(RtFSFile* handle, uint32_t bytes, uint32_t unused, int32_t event,
                                      SCinematicStreamFile* file);

namespace {

// The fields Init, Open, Close and the callback's event 3 clear (the buffer pointers apart).
void ClearState(SCinematicStreamFile* file) {
    file->m_pBuffer = nullptr;
    file->m_pDestination = nullptr;
    file->m_ui32Requested = 0;
    file->m_ui32Copied = 0;
    file->m_pOwner = nullptr;
    file->m_ui32Available = 0;
    file->m_pFile = nullptr;
    file->m_bBusy = 0;
    file->m_bDone = 0;
}

// The copy out of the read buffer: what is left of the request, at most what the buffer holds.
void CopyOut(SCinematicStreamFile* file, uint32_t count) {
    std::memcpy(file->m_pDestination + file->m_ui32Copied, file->m_pBuffer + file->m_ui32BufferOffset, count);
    file->m_ui32Copied += count;
    file->m_ui32Available -= count;
    file->m_ui32BufferOffset += count;
}

}  // namespace

// The held-back RtFS callbacks whose frames have passed, in the order they were asked for (a callback may ask for the
// next read, which then waits its own frames).
void CinematicStreamFile_PumpAsync() {
    std::vector<RtFSPending>& pending = Pending();
    for (size_t i = 0; i < pending.size();) {
        const RtFSPending p = pending[i];
        // --fps N: the latency is in 60 Hz frames, not displayed frames (the same time as at 60 fps).
        const uint32_t since = dotd::fps::Unlocked() ? dotd::fps::TickCount() - p.askedTick : FramesSince(p.asked);
        if (since < p.frames) {
            ++i;
            continue;
        }
        pending.erase(pending.begin() + static_cast<std::ptrdiff_t>(i));
        p.file->m_pfnCallback(p.file, p.bytes, 0, p.event, p.file->m_pContext);
        i = 0;  // the callback may have changed the list
    }
}

// 0x0007ea98 CinematicStreamFile_Init_maybe
void CinematicStreamFile_Init(SCinematicStreamFile* file) {
    ClearState(file);
    file->m_bOpened = 0;
    file->m_pBufferRaw = nullptr;
}

// 0x0007e9b0 CinematicStreamFile_Close_maybe
void CinematicStreamFile_Close(SCinematicStreamFile* file, CKCinematicStreamCpnt* owner) {
    file->m_pOwner = owner;
    if (file->m_pFile != nullptr) {
        RtFS_FileCancelAsync(file->m_pFile);
        RtFS_FileClose(file->m_pFile);
        file->m_pFile = nullptr;
    }
    if (file->m_pBufferRaw != nullptr) {
        ::operator delete[](file->m_pBufferRaw);  // OperatorDelete_Bridge
        file->m_pBuffer = nullptr;
        file->m_pBufferRaw = nullptr;
    }
    file->m_pBuffer = nullptr;
    file->m_bOpened = 0;
    ClearState(file);
    file->m_pBufferRaw = nullptr;
}

// 0x0007ead0 CinematicStreamFile_Open_maybe
uint8_t CinematicStreamFile_Open(SCinematicStreamFile* file, const char* path, CKCinematicStreamCpnt* owner) {
    file->m_pOwner = owner;
    if (file->m_pFile != nullptr) {
        RtFS_FileCancelAsync(file->m_pFile);
        RtFS_FileClose(file->m_pFile);
        file->m_pFile = nullptr;
    }
    if (file->m_pBufferRaw != nullptr) {
        ::operator delete[](file->m_pBufferRaw);
        file->m_pBuffer = nullptr;
        file->m_pBufferRaw = nullptr;
    }
    file->m_bOpened = 0;
    ClearState(file);
    file->m_pBufferRaw = nullptr;
    if (RtFS_FileExists(path)) {
        file->m_pOwner = owner;
        file->m_pFile = RtFS_FileOpen(path, 0x11, CinematicStreamFile_RtFSCallback, file);
        if (file->m_pFile != nullptr) {
            file->m_pBufferRaw = static_cast<uint8_t*>(::operator new[](0x20040));  // OperatorNewArray
            file->m_pBuffer = reinterpret_cast<uint8_t*>((reinterpret_cast<uintptr_t>(file->m_pBufferRaw) + 0x3f) &
                                                         ~static_cast<uintptr_t>(0x3f));
        }
    }
    return file->m_pFile != nullptr ? 1 : 0;
}

// 0x0007ec58 CinematicStreamFile_ContinueRead_maybe (the original unrolls the copy loop four times and calls itself
// for the rest). `count` 0: from the buffer's next byte; else the first `count` bytes of the buffer.
uint8_t CinematicStreamFile_ContinueRead(SCinematicStreamFile* file, uint32_t count) {
    if (count == 0) {
        count = file->m_ui32Available;
        if (count != 0) {
            if (file->m_ui32Copied + count > file->m_ui32Requested) count = file->m_ui32Requested - file->m_ui32Copied;
            if (count != 0) CopyOut(file, count);
        }
    } else {
        if (file->m_ui32Copied + count > file->m_ui32Requested) count = file->m_ui32Requested - file->m_ui32Copied;
        if (count != 0) {
            std::memcpy(file->m_pDestination + file->m_ui32Copied, file->m_pBuffer, count);
            file->m_ui32Copied += count;
            file->m_ui32Available -= count;
            file->m_ui32BufferOffset += count;
        }
    }
    for (;;) {
        if (file->m_ui32Copied == file->m_ui32Requested) {
            file->m_bBusy = 0;
            file->m_bDone = 1;
            return 1;
        }
        if (file->m_ui32Available == 0) {
            RtFS_FileRead(file->m_pBuffer, 0x20000, 1, file->m_pFile);
            return 1;
        }
        uint32_t chunk = file->m_ui32Available;
        if (file->m_ui32Copied + chunk > file->m_ui32Requested) chunk = file->m_ui32Requested - file->m_ui32Copied;
        CopyOut(file, chunk);
    }
}

// 0x0007f088 CinematicStreamFile_RequestRead_maybe
uint8_t CinematicStreamFile_RequestRead(SCinematicStreamFile* file, void* destination, uint32_t size,
                                        CKCinematicStreamCpnt* owner) {
    const uint32_t available = file->m_ui32Available;
    file->m_pDestination = static_cast<uint8_t*>(destination);
    file->m_pOwner = owner;
    file->m_bBusy = 1;
    file->m_ui32Requested = size;
    file->m_ui32Copied = 0;
    file->m_bDone = 0;
    if (available == 0) {
        if (file->m_ui32Requested == 0) {
            file->m_bBusy = 0;
            file->m_bDone = 1;
            return 1;
        }
    } else {
        const uint32_t count = size < available ? size : available;
        if (count == 0) {
            if (file->m_ui32Requested == 0) {
                file->m_bBusy = 0;
                file->m_bDone = 1;
                return 1;
            }
        } else {
            CopyOut(file, count);
            if (file->m_ui32Copied == file->m_ui32Requested) {
                file->m_bBusy = 0;
                file->m_bDone = 1;
                return 1;
            }
        }
    }
    if (file->m_ui32Available == 0) {
        RtFS_FileRead(file->m_pBuffer, 0x20000, 1, file->m_pFile);
        return 1;
    }
    CinematicStreamFile_ContinueRead(file, 0);
    return 1;
}

// 0x0007f208 CinematicStreamFile_RtFSCallback_maybe: event 3 (failed) clears the file, 2 (opened) keeps the RtFS file,
// 5 (read) hands the bytes to the request.
void CinematicStreamFile_RtFSCallback(RtFSFile* handle, uint32_t bytes, uint32_t /*unused*/, int32_t event,
                                      SCinematicStreamFile* file) {
    if (file == nullptr) return;
    if (event == 3) {
        // BUG(original): the buffer pointers are dropped without the buffer being freed.
        ClearState(file);
        file->m_bOpened = 0;
        file->m_pBufferRaw = nullptr;
        return;
    }
    if (event == 5) {
        file->m_ui32Available = bytes;
        file->m_ui32BufferOffset = 0;
        if (bytes != 0) {
            uint32_t count = bytes;
            if (file->m_ui32Copied + count > file->m_ui32Requested) count = file->m_ui32Requested - file->m_ui32Copied;
            if (count != 0) CopyOut(file, count);
        }
        if (file->m_ui32Copied == file->m_ui32Requested) {
            file->m_bBusy = 0;
            file->m_bDone = 1;
        } else if (file->m_ui32Available != 0) {
            CinematicStreamFile_ContinueRead(file, 0);
        } else {
            RtFS_FileRead(file->m_pBuffer, 0x20000, 1, file->m_pFile);
        }
        return;
    }
    if (event == 2) {
        file->m_pFile = handle;
        file->m_bOpened = 1;
    }
}

// 0x0007f3e8 CinematicStream_ResolveAnimatedNode_maybe: a hook (key 2) stands for its node (+0x1c); an animated node
// (0x54b) or null.
IKSerializable* CinematicStream_ResolveAnimatedNode(IKSerializable* object) {
    if (object == nullptr) return nullptr;
    if (object->IsKindOfClass(2) != 0) {
        object = static_cast<IKHook*>(object)->m_pKGLObject;
        if (object == nullptr) return nullptr;
    }
    return object->IsKindOfClass(0x54b) != 0 ? object : nullptr;
}

// 0x0007f4d8 CinematicStream_IsActorSceneLeaf_maybe (type 0's PostLoad slot): the node's IsKindOfClass(0x20b), the
// answer not used.
void CinematicStream_IsActorSceneLeaf(SCinematicStreamTrackType* type) {
    IKSerializable* node = type->m_pChannel->m_pUnk04;
    if (node != nullptr) node->IsKindOfClass(0x20b);
}

// 0x0007f540 CinematicStream_SaveActorMatrix_maybe (type 0's slot +0x10): an animated node's modelling matrix kept in
// the channel's first matrix. 1.
uint8_t CinematicStream_SaveActorMatrix(SCinematicStreamTrackType* type, uint32_t /*withMedia*/) {
    CKCinematicStreamCpnt::SChannel* channel = type->m_pChannel;
    IKSerializable* node = channel->m_pUnk04;
    if (node != nullptr && node->IsKindOfClass(0x54b) != 0) {
        std::memcpy(channel->m_pMatrix10, &static_cast<CSGMovable*>(node)->m_pRwFrame->modelling, sizeof(CMatrix34));
    }
    return 1;
}

// 0x0007f680 KStub_Return36_7f680: 36 = the PS3 size of AnimFloatBlock9 (native: sizeof, as STYLE.md asks).
uint32_t CinematicStream_GetFloatBlock9Size() { return static_cast<uint32_t>(sizeof(AnimFloatBlock9)); }
