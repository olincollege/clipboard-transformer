#include <gtk/gtk.h>

static void show_overlay(GtkWidget* widget, gpointer data) {
  GtkWindow* window = GTK_WINDOW(data);
  gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc, char* argv[]) {
  gtk_init(&argc, &argv);

  // Create the window
  GtkWidget* window = gtk_window_new(GTK_WINDOW_POPUP);
  gtk_window_set_type_hint(GTK_WINDOW(window), GDK_WINDOW_TYPE_HINT_DOCK);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 50);

  // Create a box to hold the search entry
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(window), box);

  // Create the search entry
  GtkWidget* search_entry = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(box), search_entry, FALSE, FALSE, 0);

  // Connect the search entry to a keyboard shortcut
  GtkAccelGroup* accel_group = gtk_accel_group_new();
  gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);
  guint keyval = GDK_KEY_space;
  GdkModifierType modifier = GDK_CONTROL_MASK;
  gtk_widget_add_accelerator(search_entry, "activate", accel_group, keyval,
                             modifier, GTK_ACCEL_VISIBLE);
  g_signal_connect(search_entry, "activate", G_CALLBACK(show_overlay), window);

  gchar* accelerator_label = gtk_accelerator_get_label(keyval, modifier);
  g_print("Accelerator: %s\n", accelerator_label);
  g_free(accelerator_label);

  // Show the window
  gtk_widget_show_all(window);

  gtk_main();
  return 0;
}
