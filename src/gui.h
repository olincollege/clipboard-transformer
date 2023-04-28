#pragma once
#include <gtk/gtk.h>

/**
 * @brief Start the GUI
 * 
 * Initialize GTK, create the window, and run the create_overlay function.
 * 
 * @param argc The number of command line arguments
 * @param argv The command line arguments
 * @return GtkWidget* 
 */
GtkWidget* start_gui(int argc, char* argv[]);

/**
 * @brief Create the overlay
 * 
 * Create the overlay containing the search bar and the results list and
 * add it to the window.
 * 
 * @param window The window to add the overlay to
 */
void create_overlay(GtkWidget* window);

/**
 * @brief Filter the results
 * 
 * G_CALLBACK function to filter the results based on the search bar text.
 * 
 * @param overlay Pointer to the search bar which triggered the callback
 * @return GtkWidget* 
 */
void filter_results(GtkEntry* entry, GtkListStore* store);

/**
 * @brief Show the error screen
 * 
 * Create a new window to display an error message. Also add a button which
 * destroys the window when clicked.
 * 
 * @param parent_window Pointer to the parent window
 * @param error_message The error message to display
 */
void show_error_screen(GtkWidget* window, const char* error_message);

/**
 * @brief Close the error screen
 * 
 * G_CALLBACK function to close the error screen. Connected to the "close"
 * button in the error screen.
 * 
 * @param widget Pointer to the close button which triggered the callback
 * @param data Pointer to the error screen window
 */
void close_error_screen(GtkWidget* widget, gpointer data);
