#include "event/mac/Event.hpp"
#include "event/Event.hpp"
#include <AppKit/AppKit.h>

void RunCocoaEventLoop() {
    if (!Event::s_shouldLoopTerminate) {
        [NSApp run];
    }
}
