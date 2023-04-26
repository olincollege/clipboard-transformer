#pragma once
#include <gtk/gtk.h>

void start_gui(int argc, char* argv[]);
void create_overlay(GtkWidget* window);
void filter_results(GtkEntry* entry, GtkListStore* store);
