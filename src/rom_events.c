#include "rom_events.h"
#include "interface_main.h"

void romOpen ()
{
    interface_main_onRomOpen();
}

void romClose()
{
    interface_main_onRomClose();
}
