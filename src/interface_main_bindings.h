#ifndef __INTERFACE_MAIN_BINDINGS_H__
#define __INTERFACE_MAIN_BINDINGS_H__

#include <gtk/gtk.h>

void infoButtonClick (GtkWidget *wid, GtkWidget *win);
void openButtonClick (GtkWidget *wid, GtkWidget *win);
void playButtonClick (GtkWidget *wid, GtkWidget *win);
void pauseButtonClick (GtkWidget *wid, GtkWidget *win);
void stopButtonClick (GtkWidget *wid, GtkWidget *win);
void closeButtonClick (GtkWidget *wid, GtkWidget *win);
void mainWindowClose ();

#endif /* __INTERFACE_MAIN_BINDINGS_H__ */
