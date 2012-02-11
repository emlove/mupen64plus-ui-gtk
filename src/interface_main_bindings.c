/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus-ui-gtk - interface_main_bindings.c                        *
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

#include "interface_main_bindings.h"

#include "strings.h"
#include "interface_main.h"
#include "interface_settings.h"
#include "interface_alert.h"
#include "core_interface.h"
#include "version.h"
#include "rom_thread.h"

void openButtonClick (GtkWidget *wid, GtkWidget *win)
{
    if (isRomThreadRunning()) {
        return;
    }
    GtkWidget *dialog;

    dialog = gtk_file_chooser_dialog_new ("Open ROM",
			          NULL,
			          GTK_FILE_CHOOSER_ACTION_OPEN,
			          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
			          GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
			          NULL);

    char *filename = NULL;
    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
    {
        filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
        startRomThread(filename);
    }
    gtk_widget_destroy (dialog);
    interface_main_onRomPauseChange(FALSE);
}

void playButtonClick (GtkWidget *wid, GtkWidget *win)
{
    (*CoreDoCommand)(M64CMD_RESUME, 0, NULL);
    interface_main_onRomPauseChange(FALSE);
}

void pauseButtonClick (GtkWidget *wid, GtkWidget *win)
{
    (*CoreDoCommand)(M64CMD_PAUSE, 0, NULL);
    interface_main_onRomPauseChange(TRUE);
}

void stopButtonClick (GtkWidget *wid, GtkWidget *win)
{
    (*CoreDoCommand)(M64CMD_STOP, 0, NULL);
}

void settingsButtonClick (GtkWidget *wid, GtkWidget *win)
{
    gtk_widget_show_all (getSettingsWindow());
}

void infoButtonClick (GtkWidget *wid, GtkWidget *win)
{
    int CoreVersion;
    const char *CoreName;
    getCoreVersion(NULL, &CoreVersion, NULL, &CoreName, NULL);
    const char *message;
    asprintf(&message, MESSAGES_INFO, CoreName, VERSION_PRINTF_SPLIT(CoreVersion));
    alert(message);
}

void closeGUI() {
    (*CoreDoCommand)(M64CMD_STOP, 0, NULL);
    finishRomThread();
    gtk_main_quit();
}

void mainWindowClose ()
{
    closeGUI();
}
