/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus-ui-gtk - interface_main.c                                 *
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

#include "interface_main.h"

static GtkWidget* _mainWindow = NULL;
static GtkWidget* playButton = NULL;
static GtkWidget* stopButton = NULL;

static int playButtonHandler = 0;

GtkWidget* getMainWindow() {
    if (_mainWindow == NULL) {
        _mainWindow = createWindow();
    }
    return _mainWindow;
}
void interface_main_onRomOpenChange(bool romOpen) {
    gtk_widget_set_sensitive(playButton, romOpen);
    gtk_widget_set_sensitive(stopButton, romOpen);
    interface_main_onRomPauseChange(!romOpen);
}
void interface_main_onRomPauseChange(bool romPaused) {
    if (playButtonHandler != 0) {
        g_signal_handler_disconnect (G_OBJECT (playButton), playButtonHandler);
    }
    if (romPaused) {
        gtk_tool_button_set_stock_id((GtkToolButton*)playButton, GTK_STOCK_MEDIA_PLAY);
        playButtonHandler = g_signal_connect (G_OBJECT (playButton), "clicked", G_CALLBACK (playButtonClick), NULL);
    } else {
        gtk_tool_button_set_stock_id((GtkToolButton*)playButton, GTK_STOCK_MEDIA_PAUSE);
        playButtonHandler = g_signal_connect (G_OBJECT (playButton), "clicked", G_CALLBACK (pauseButtonClick), NULL);
    }
}

static GtkWidget* createWindow()
{    
    GtkToolItem *button = NULL;
    GtkWidget *win = NULL;
    GtkWidget *toolbar = NULL;
    GtkWidget *vbox = NULL;

    /* Create the main window */
    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (win), 8);
    gtk_window_set_title (GTK_WINDOW (win), GTK_UI_TITLE);
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_window_resize (GTK_WINDOW (win), 300, 100);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", mainWindowClose, NULL);

    /* Create a vertical box with buttons */
    toolbar = gtk_toolbar_new ();
    vbox = gtk_vbox_new (FALSE, 6);
    gtk_container_add (GTK_CONTAINER (win), vbox);
    gtk_container_add (GTK_CONTAINER (vbox), toolbar);

    button = gtk_tool_button_new_from_stock (GTK_STOCK_OPEN);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (openButtonClick), NULL);
    gtk_toolbar_insert (GTK_TOOLBAR(toolbar), button, -1);

    button = gtk_tool_button_new_from_stock (GTK_STOCK_MEDIA_PLAY);
    gtk_toolbar_insert (GTK_TOOLBAR(toolbar), button, -1);
    playButton = (GtkWidget *)button;

    button = gtk_tool_button_new_from_stock (GTK_STOCK_MEDIA_STOP);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (stopButtonClick), NULL);
    gtk_widget_set_sensitive((GtkWidget *)button, FALSE);
    gtk_toolbar_insert (GTK_TOOLBAR(toolbar), button, -1);
    stopButton = (GtkWidget *)button;

    button = gtk_tool_button_new_from_stock (GTK_STOCK_DIALOG_INFO);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (infoButtonClick), NULL);
    gtk_toolbar_insert (GTK_TOOLBAR(toolbar), button, -1);
    
    interface_main_onRomOpenChange(FALSE);

    return win;
}
