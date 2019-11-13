#include <gtk/gtk.h>

void launch_gui(int argc, char *argv[])
{
    GtkBuilder *builder;
    GtkWidget *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("src/glade/gui.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_start"));
    
    gtk_builder_connect_signals(builder, NULL);
    
    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();
}

// called when starting window is closed
void on_window_start_destroy()
{
    gtk_main_quit();
}

// the "start" button is clicked
void on_btn_start_app_clicked()
{
    gtk_main_quit();
}

// called when the user quits the app from the
// start window
void on_btn_quit_start_app_clicked()
{
    gtk_main_quit();
}