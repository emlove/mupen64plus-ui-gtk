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

#include "interface_settings_bindings.h"
#include "config_interface.h"

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
    GtkWidget *notebook = NULL;
    GtkWidget *vbox = NULL;
    GtkWidget *checkbutton = NULL;
    int checkValue;

    /* Create the main window */
    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (win), TITLE_WINDOW_SETTINGS);
    gtk_window_set_default_size (GTK_WINDOW (win), 300, 100);
    gtk_widget_realize (win);
    g_signal_connect (win, "delete_event", G_CALLBACK (gtk_widget_hide_on_delete), NULL);
    
    notebook = gtk_notebook_new ();
    gtk_container_add (GTK_CONTAINER (win), notebook);
    
    vbox = gtk_vbox_new (FALSE, 6);
    gtk_notebook_append_page (GTK_NOTEBOOK (notebook), vbox, 
                gtk_label_new(TITLE_TAB_SETTINGS_GENERAL));
                
    /* BEGIN GENERAL TAB */
    checkbutton = gtk_check_button_new_with_label (LABEL_SETTINGS_OnScreenDisplay);
    gtk_widget_set_tooltip_text (checkbutton, TOOLTIP_SETTINGS_OnScreenDisplay);
    ConfigGet(CONFIG_SECTION_CORE, "OnScreenDisplay", M64TYPE_BOOL, &checkValue, sizeof(checkValue));
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), checkValue);
    gtk_container_add (GTK_CONTAINER (vbox), checkbutton);
    g_signal_connect (checkbutton, "toggled", G_CALLBACK (toggle_OnScreenDisplay), NULL);
    /* END GENERAL TAB */

    return win;
}
