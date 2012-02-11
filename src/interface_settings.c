/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus-ui-gtk - interface_settings.c                             *
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

#include "interface_settings.h"

static GtkWidget* _settingsWindow = NULL;

static GtkWidget* createWindow();

GtkWidget* getSettingsWindow() {
    if (_settingsWindow == NULL) {
        _settingsWindow = createWindow();
    }
    return _settingsWindow;
}

static GtkWidget* createWindow()
{
    GtkWidget *win = NULL;

    /* Create the main window */
    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (win), GTK_SETTINGS_TITLE);
    gtk_window_resize (GTK_WINDOW (win), 300, 100);
    gtk_widget_realize (win);
    g_signal_connect (win, "delete_event", (GCallback)gtk_widget_hide_on_delete, NULL);

    return win;
}
