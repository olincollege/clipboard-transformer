#pragma once
#include <gtk/gtk.h>
#include <unordered_map>
#include "transformation.h"
#include "clip/clip.h"

/**
 * @brief Start the GUI
 * 
 * Initialize GTK, create the window, and run the create_overlay function.
 * 
 * @param argc The number of command line arguments
 * @param argv The command line arguments
 * @param txfnMap A pointer to the transformation map
 * @param input The input string to pass to the transformations
 */
void start_gui(int argc, char* argv[], std::shared_ptr<TransformationMap> txfnMap, std::string input);

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
 * @brief Filter the results
 * 
 * G_CALLBACK function to filter the results based on the search bar text.
 * 
 * @param entry Pointer to the search bar
 * @param data Pointer to data passed to the callback
 */
void filter_results(GtkEntry* entry, gpointer data);

/**
 * @brief Run transformation selected in the tree view
 * 
 * G_CALLBACK function to run the transformation selected in the tree view. 
 * 
 * @param tree_view Pointer to the tree view displaying the transformations
 * @param data Pointer to the data passed to the callback 
 */
void select_transformation(GtkTreeView* tree_view, gpointer data);

/**
 * @brief Check if user presses the enter key in the tree view.
 * 
 * G_CALLBACK function to check if the user presses the enter key in the tree
 * view. If so, run the select_transformation function and clear the search bar.
 * Also check for the up and down arrow keys and move in the tree view accordingly.
 * 
 * @param tree_view Pointer to the tree view displaying the transformations
 * @param event Pointer to the key press event
 * @param data Pointer to the data passed to the callback
 */
void check_key_press(GtkTreeView* tree_view, GdkEventKey* event, gpointer data);

/**
 * @brief Create the GUI overlay window
 * 
 * Create the GUI overlay window containing the search bar, results list, success label
 * and exit button.
 * 
 * @param window Pointer to the window to add the overlay to
 * @param txfcMap Pointer to the transformation map
 * @param input Pointer to the input string
 */
void create_overlay(GtkWidget* window, std::shared_ptr<TransformationMap> txfcMap, std::string input);
