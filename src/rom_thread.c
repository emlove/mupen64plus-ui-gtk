/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus-ui-gtk - rom_thread.c                                     *
 *   Mupen64Plus homepage: http://code.google.com/p/mupen64plus/           *
 *   Copyright (C) 2012 Adam Mills                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "rom_thread.h"

#include "main.h"

G_LOCK_DEFINE (romThread);
static GThread* romThread = NULL;

int isRomThreadRunning() {
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
