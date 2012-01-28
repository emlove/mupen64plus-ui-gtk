#include "interface_main_bindings.h"

#include "strings.h"
#include "interface_main.h"
#include "interface_alert.h"
#include "core_interface.h"
#include "version.h"
#include "main.h"

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
        g_thread_create( (GThreadFunc)playRomThread, filename, FALSE, NULL );
    }
    gtk_widget_destroy (dialog);
}

void closeButtonClick (GtkWidget *wid, GtkWidget *win)
{
    gtk_main_quit();
}
