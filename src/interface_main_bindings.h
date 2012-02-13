/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus-ui-gtk - interface_main_bindings.h                        *
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

#ifndef __INTERFACE_MAIN_BINDINGS_H__
#define __INTERFACE_MAIN_BINDINGS_H__

#include <gtk/gtk.h>

void openButtonClick (GtkWidget *wid, GtkWidget *win);
void playButtonClick (GtkWidget *wid, GtkWidget *win);
void pauseButtonClick (GtkWidget *wid, GtkWidget *win);
void stopButtonClick (GtkWidget *wid, GtkWidget *win);
void settingsButtonClick (GtkWidget *wid, GtkWidget *win);
void mainWindowClose ();

#endif /* __INTERFACE_MAIN_BINDINGS_H__ */
