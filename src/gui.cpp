#include "gui.h"
#include <gtk/gtk.h>
#include <iostream>

void start_gui(int argc, char* argv[], std::shared_ptr<TransformationMap> txfnMap, std::string input) {
  gtk_init(&argc, &argv);

  gint window_height = 200;
  gint window_width = 400;
  // Create the window
  GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_decorated(GTK_WINDOW(window), FALSE); // hide top bar
  gtk_window_set_type_hint(GTK_WINDOW(window), GDK_WINDOW_TYPE_HINT_DOCK);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
  gtk_window_set_default_size(GTK_WINDOW(window), window_width, window_height);

  // Create the overlay
  create_overlay(window, txfnMap, input);

  // Show the window
  gtk_widget_show_all(window);
  gtk_main();
}

void close_error_screen(GtkWidget* widget, gpointer data) {
  GtkWidget* window = (GtkWidget*)data;
  gtk_widget_destroy(window);
}

void show_error_screen(GtkWidget* parent_window, const char* error_message) {
  // Create the window
  GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_decorated(GTK_WINDOW(window), FALSE); // hide top bar
  gtk_window_set_modal(GTK_WINDOW(window), TRUE); // model window for alert
  gtk_window_set_transient_for(GTK_WINDOW(window), GTK_WINDOW(parent_window)); // link to parent window
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ON_PARENT);
  // set default size equal to parent window
  gtk_window_set_default_size(GTK_WINDOW(window),
                              gtk_widget_get_allocated_width(parent_window),
                              gtk_widget_get_allocated_height(parent_window));

  // Create a box to hold the overlay
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(window), box);

  // Create the error message label
  GtkWidget* label = gtk_label_new(error_message);
  // center the label
  gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);

  // Create the close button
  GtkWidget* close_button = gtk_button_new_with_label("Close");
  g_signal_connect(close_button, "clicked", G_CALLBACK(close_error_screen),
                   window);
  gtk_box_pack_end(GTK_BOX(box), close_button, FALSE, FALSE, 0);

  // Show the window
  gtk_widget_show_all(window);
}

// Define a callback function to filter the results
void filter_results(GtkEntry* entry, gpointer data) {
  // Get the text entered in the search entry
  const char* search_text = gtk_entry_get_text(entry);

  // Cast the data pointer back to a GtkListStore pointer
  GtkListStore* store = GTK_LIST_STORE(data);

  // Clear the current results in the list store
  gtk_list_store_clear(store);

  // Get the stored pointer to the txfcMap object
  std::unordered_map<std::string, Transformation*>* txfcMapPtr = reinterpret_cast<std::unordered_map<std::string, Transformation*>*>(
    g_object_get_data(G_OBJECT(store), "txfc_map"));

  // update list store with filtered results
  GtkTreeIter iter;
  for (auto const& txfc : *txfcMapPtr) {
    if (txfc.first.find(search_text) != std::string::npos) {
      gtk_list_store_append(store, &iter);
      gtk_list_store_set(store, &iter, 0, txfc.first.c_str(), -1);
    }
  }
}

void select_transformation(GtkTreeView* tree_view, gpointer data) {
  GtkTreeSelection* selection = gtk_tree_view_get_selection(tree_view);

  GtkListStore* store = GTK_LIST_STORE(data);

  GtkTreeModel* model;
  GtkTreeIter iter;
  if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
    gchar* name;
    gtk_tree_model_get(model, &iter, 0, &name, -1);

    // Get the stored pointer to the txfcMap object
    std::unordered_map<std::string, Transformation*>* txfcMap = reinterpret_cast<std::unordered_map<std::string, Transformation*>*>(
      g_object_get_data(G_OBJECT(store), "txfc_map"));

    // Get the stored pointer to the input string
    std::string* input = reinterpret_cast<std::string*>(
      g_object_get_data(G_OBJECT(store), "input"));

    auto txf_it = txfcMap->find(name);
    if (txf_it != txfcMap->end()) {
      // Transformation* selected_txfn = txf_it->second;
      Transformation* selected_txfn = txfcMap->at(name);

      // Run the selected transformation
      TransformationResult* output = selected_txfn->transform(input);

      // handle output
      if (output->exitCode != 0) {
        show_error_screen(gtk_widget_get_toplevel(GTK_WIDGET(tree_view)),
                      ("Transformation failed with exit code " + std::to_string(output->exitCode) + "\n" + output->output).c_str());
      } else {
        clip::set_text(output->output);
      }
      delete output; 
    }
    g_free(name);
  }
  // kill gtk main loop
  gtk_main_quit();
}

void overlay_destroyed(GtkWidget* overlay, gpointer data) {
  GtkListStore* store = GTK_LIST_STORE(data);

  // Free the input string and txfcMap pointers stored in the list store's object data
  std::string* inputPtr = static_cast<std::string*>(g_object_get_data(G_OBJECT(store), "input"));
  delete inputPtr;

  // Loop through the txfcMap and delete all the Transformation objects
  std::unordered_map<std::string, Transformation*>* txfcMapPtr =
      static_cast<std::unordered_map<std::string, Transformation*>*>(g_object_get_data(G_OBJECT(store), "txfc_map"));
  for (auto const& txfc : *txfcMapPtr) {
    delete txfc.second;
  }
  delete txfcMapPtr;

  gtk_widget_destroy(overlay);
}

void check_enter_key(GtkTreeView* tree_view, GdkEventKey* event, gpointer data) {
  if (event->keyval == GDK_KEY_Return) {
    // run select transformation callback
    select_transformation(tree_view, data);
  }
}

void create_overlay(GtkWidget* window, std::shared_ptr<TransformationMap> txfcMap, std::string input) {
  // Create a box to hold the overlay
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(window), box);

  // Create the search entry
  GtkWidget* search_entry = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(box), search_entry, FALSE, FALSE,
                     0);  // pack search entry as first element from top in box

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

  // Add txfcMap keys to list store
  GtkTreeIter iter;
  for (auto const& txfc : *txfcMap) {
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, 0, txfc.first.c_str(), -1);
  }

  // Allocate the txfcMap object on the heap and store a pointer to it in the list store's object data
  std::unordered_map<std::string, Transformation*>* txfcMapPtr = new std::unordered_map<std::string, Transformation*>(*txfcMap);
  g_object_set_data(G_OBJECT(store), "txfc_map", txfcMapPtr);

  std::string* inputPtr = new std::string(input);
  g_object_set_data(G_OBJECT(store), "input", inputPtr);

  // Connect the "changed" signal of the search entry to the filter_results callback
  g_signal_connect(search_entry, "changed", G_CALLBACK(filter_results), store);

  // g_signal_connect(tree_view, "cursor-changed", G_CALLBACK(select_transformation), store);
  g_signal_connect(tree_view, "key-press-event", G_CALLBACK(check_enter_key), store);

  // connect destroy signal to overlay_destroyed callback
  g_signal_connect(window, "destroy", G_CALLBACK(overlay_destroyed), NULL);
}
