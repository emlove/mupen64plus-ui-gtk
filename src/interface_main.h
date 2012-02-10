#ifndef __INTERFACE_MAIN_H__
#define __INTERFACE_MAIN_H__

#include <gtk/gtk.h>
#include <stdbool.h>

#include "strings.h"
#include "interface_main_bindings.h"

GtkWidget* getMainWindow();
static GtkWidget* createWindow();

void interface_main_onRomOpenChange(bool romOpen);
void interface_main_onRomPauseChange(bool romPaused);

#endif /* __INTERFACE_MAIN_H__ */
