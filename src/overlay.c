#include <gtk/gtk.h>

static void show_overlay(GtkWidget* widget, gpointer data) {
  GtkWindow* window = GTK_WINDOW(data);
  gtk_widget_show_all(GTK_WIDGET(window));
}

static void create_overlay(GtkWindow* window) {
  // Create a box to hold the overlay
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(window), box);

  // Create the search entry
  GtkWidget* search_entry = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(box), search_entry, FALSE, FALSE, 0);

  // Connect the search entry to a keyboard shortcut
  GtkAccelGroup* accel_group = gtk_accel_group_new();
  gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);
  guint keyval = GDK_KEY_space;
  GdkModifierType modifier = GDK_CONTROL_MASK | GDK_SHIFT_MASK;
  gtk_widget_add_accelerator(search_entry, "activate", accel_group, keyval,
                             modifier, GTK_ACCEL_VISIBLE);
  g_signal_connect(search_entry, "activate", G_CALLBACK(show_overlay), window);

  // Create the results list
  GtkListStore* store = gtk_list_store_new(1, G_TYPE_STRING);
  GtkTreeView* tree_view =
      GTK_TREE_VIEW(gtk_tree_view_new_with_model(GTK_TREE_MODEL(store)));
  gtk_tree_view_set_headers_visible(tree_view, FALSE);  // Hide the headers
  GtkCellRenderer* renderer = gtk_cell_renderer_text_new();
  GtkTreeViewColumn* column = gtk_tree_view_column_new_with_attributes(
      NULL, renderer, "text", 0, NULL);  // Set the column title to NULL
  gtk_tree_view_append_column(tree_view, column);

  // Create a scrolled window and add the tree view to it
  GtkWidget* scrolled_window = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                 GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_container_add(GTK_CONTAINER(scrolled_window), GTK_WIDGET(tree_view));
  gtk_box_pack_start(GTK_BOX(box), scrolled_window, TRUE, TRUE, 0);

  // Add some sample results to the list
  GtkTreeIter iter;
  for (int i = 0; i < 20; i++) {
    gtk_list_store_append(store, &iter);
    char* text = g_strdup_printf("Result %d", i);
    gtk_list_store_set(store, &iter, 0, text, -1);
  }

  // Show the overlay
  gtk_widget_show_all(box);
}

int main(int argc, char* argv[]) {
  gtk_init(&argc, &argv);

  // Create the window
  GtkWidget* window = gtk_window_new(GTK_WINDOW_POPUP);
  gtk_window_set_type_hint(GTK_WINDOW(window), GDK_WINDOW_TYPE_HINT_DOCK);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

  // Create the overlay
  create_overlay(window);

  // Show the window
  gtk_widget_show_all(window);

  gtk_main();
  return 0;
}
