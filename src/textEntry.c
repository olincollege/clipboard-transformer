#include<gtk/gtk.h>

// text entry box in gt

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *entry;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    entry = gtk_entry_new();

    gtk_container_add(GTK_CONTAINER(window), entry);
    gtk_widget_show(entry);
    gtk_widget_show(window);

    gtk_main();

    return 0;
}
