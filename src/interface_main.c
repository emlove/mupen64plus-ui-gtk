#include "interface_main.h"

static GtkWidget* _mainWindow = NULL;
static GtkWidget* playButton = NULL;
static GtkWidget* pauseButton = NULL;
static GtkWidget* stopButton = NULL;
GtkWidget* getMainWindow() {
    if (_mainWindow == NULL) {
        _mainWindow = createWindow();
    }
    return _mainWindow;
}

void interface_main_onRomOpen() {
    gtk_widget_set_sensitive(playButton, TRUE);
    gtk_widget_set_sensitive(pauseButton, TRUE);
    gtk_widget_set_sensitive(stopButton, TRUE);
}

void interface_main_onRomClose() {
    gtk_widget_set_sensitive(playButton, FALSE);
    gtk_widget_set_sensitive(pauseButton, FALSE);
    gtk_widget_set_sensitive(stopButton, FALSE);
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
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (openButtonClick), (gpointer) win);
    gtk_toolbar_insert (GTK_TOOLBAR(toolbar), button, -1);

    button = gtk_tool_button_new_from_stock (GTK_STOCK_MEDIA_PLAY);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (playButtonClick), (gpointer) win);
    gtk_toolbar_insert (GTK_TOOLBAR(toolbar), button, -1);
    playButton = (GtkWidget *)button;
    gtk_widget_set_sensitive(playButton, FALSE);

    button = gtk_tool_button_new_from_stock (GTK_STOCK_MEDIA_PLAY);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (pauseButtonClick), (gpointer) win);
    gtk_toolbar_insert (GTK_TOOLBAR(toolbar), button, -1);
    pauseButton = (GtkWidget *)button;
    gtk_widget_set_sensitive(pauseButton, FALSE);

    button = gtk_tool_button_new_from_stock (GTK_STOCK_MEDIA_STOP);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (stopButtonClick), (gpointer) win);
    gtk_widget_set_sensitive((GtkWidget *)button, FALSE);
    gtk_toolbar_insert (GTK_TOOLBAR(toolbar), button, -1);
    stopButton = (GtkWidget *)button;
    gtk_widget_set_sensitive(stopButton, FALSE);

    button = gtk_tool_button_new_from_stock (GTK_STOCK_DIALOG_INFO);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (infoButtonClick), (gpointer) win);
    gtk_toolbar_insert (GTK_TOOLBAR(toolbar), button, -1);

    button = gtk_tool_button_new_from_stock (GTK_STOCK_CLOSE);
    g_signal_connect (button, "clicked", G_CALLBACK (closeButtonClick), NULL);
    gtk_toolbar_insert (GTK_TOOLBAR(toolbar), button, -1);

    return win;
}
