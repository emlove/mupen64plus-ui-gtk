#include "rom_thread.h"

#include "main.h"

G_LOCK_DEFINE (romThread);
static GThread* romThread = NULL;

bool isRomThreadRunning() {
    return romThread != NULL;
}

gpointer playRomThread(const char *ROMFilepath)
{
    playRom(ROMFilepath);
    G_LOCK (romThread);
    romThread = NULL;
    G_UNLOCK (romThread);
}

void startRomThread(char *ROMFilepath)
{
    G_LOCK (romThread);
    romThread = g_thread_create( (GThreadFunc)playRomThread, ROMFilepath, TRUE, NULL );
    G_UNLOCK (romThread);
}

void finishRomThread() {
    if (isRomThreadRunning()) {
        g_thread_join(romThread);
    }
}
