#include "rom_events.h"
#include "interface_main.h"

void romOpen ()
{
    interface_main_onRomOpenChange(TRUE);
}

void romClose()
{
    interface_main_onRomOpenChange(FALSE);
}
