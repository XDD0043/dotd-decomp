// foundation_test - C1.5 foundation: the front end boots and steps frames; RwSList behaves like the PS3's.
#include <cstdio>

#include "Renderware/rwcore/RwSList.h"
#include "boot_helper.h"

int main() {
    // _rwSListGetNewEntry growth: +1 below 4 allocated entries, then +alloced/4.
    RwSList* list = _rwSListCreate(sizeof(int32_t), 0);
    int expectedAlloc[] = {1, 2, 3, 4, 5, 6, 7, 8, 10, 10, 12, 12, 15, 15, 15, 18};
    for (int i = 0; i < 16; ++i) {
        *static_cast<int32_t*>(_rwSListGetNewEntry(list, 0)) = i;
        C15_CHECK(list->numElementsAlloced == expectedAlloc[i]);
    }
    C15_CHECK(_rwSListGetNumEntries(list) == 16);
    C15_CHECK(*RwSListEntry<int32_t>(list, 9) == 9);
    _rwSListDestroy(list);

    if (!c15::BootToFrontEnd()) {
        std::printf("foundation: no game data configured; skipped\n");
        return 77;
    }
    for (int i = 0; i < 10; ++i) c15::RunFrame();
    C15_CHECK(c15::FrameCount() == 10);
    c15::Shutdown();
    if (c15::g_failures == 0) std::printf("foundation: all tests passed\n");
    return c15::g_failures == 0 ? 0 : 1;
}
