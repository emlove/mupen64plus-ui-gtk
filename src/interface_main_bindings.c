#include "interface_main_bindings.h"

#include "strings.h"
#include "interface_main.h"
#include "interface_alert.h"
#include "core_interface.h"
#include "version.h"
#include "rom_thread.h"

void infoButtonClick (GtkWidget *wid, GtkWidget *win)
{
    int CoreVersion;
    const char *CoreName;
    getCoreVersion(NULL, &CoreVersion, NULL, &CoreName, NULL);
    const char *message;
    asprintf(&message, MESSAGES_INFO, CoreName, VERSION_PRINTF_SPLIT(CoreVersion));
    alert(message);
}

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

void closeGUI() {
    (*CoreDoCommand)(M64CMD_STOP, 0, NULL);
    finishRomThread();
    gtk_main_quit();
}

void mainWindowClose ()
{
    closeGUI();
}

void closeButtonClick (GtkWidget *wid, GtkWidget *win)
{
    closeGUI();
}
