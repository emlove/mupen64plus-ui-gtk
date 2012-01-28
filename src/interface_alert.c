#include "interface_alert.h"

void alert (const char *message)
{
    GtkWidget *dialog = NULL;
    GtkWidget *win = NULL;
    
    /* Load the main Window to display alert against */
    win = getMainWindow();

    dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "%s", message);
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}
