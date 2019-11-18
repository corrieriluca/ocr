#include <gtk/gtk.h>


GtkWidget *window;
GtkWidget *window_main;

int open_main_win = 0;

void launch_gui(int argc, char *argv[])
{
    GtkBuilder *builder;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("src/glade/gui.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_start"));
    window_main = GTK_WIDGET(gtk_builder_get_object(builder, "window_main_menu"));

    gtk_builder_connect_signals(builder, NULL);
    
    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();
}

// called when starting window is closed
void on_window_start_destroy()
{
	if(open_main_win == 0)
    	gtk_main_quit();
}

void on_window_main_menu_destroy()
{
	gtk_main_quit();
}

// the "start" button is clicked
void on_btn_start_app_clicked()
{
	open_main_win = 1;
	gtk_widget_destroy(window);
	gtk_widget_show(window_main);
}

// called when the user quits the app from the
// start window
void on_btn_quit_start_app_clicked()
{
    gtk_main_quit();
}
