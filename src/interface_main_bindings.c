#include "interface_main_bindings.h"

void infoButtonClick (GtkWidget *wid, GtkWidget *win)
{
    int CoreVersion;
    const char *CoreName;
    getCoreVersion(NULL, &CoreVersion, NULL, &CoreName, NULL);
    const char *message;
    asprintf(&message, MESSAGES_INFO, CoreName, VERSION_PRINTF_SPLIT(CoreVersion));
    alert(message);
}

void closeButtonClick (GtkWidget *wid, GtkWidget *win)
{
    gtk_main_quit();
}
