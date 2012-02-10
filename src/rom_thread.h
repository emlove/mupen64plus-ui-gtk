#ifndef __ROM_THREAD_H__
#define __ROM_THREAD_H__

#include <gtk/gtk.h>
#include <stdbool.h>

void startRomThread(char *ROMFilepath);
void finishRomThread();
bool isRomThreadRunning();

#endif /* __ROM_THREAD_H__ */
