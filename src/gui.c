#include <gtk/gtk.h>

GtkWidget *window;
GtkWidget *window_main;

GtkWidget *fcb_image;

int open_main_win = 0;

void launch_gui(int argc, char *argv[])
{
    GtkBuilder *builder;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("src/glade/gui.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_start"));
    window_main = GTK_WIDGET(gtk_builder_get_object(builder, "window_main_menu"));

    // file chooser button in window_main_menu
    fcb_image = GTK_WIDGET(gtk_builder_get_object(builder, "fcb_image"));

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

// called when main window is closed
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
// - start window
// - the main window (menu bar)
// - the main window (quit button)
void on_btn_quit_clicked()
{
    gtk_main_quit();
}

// called when a file is selected with the file chooser button
void on_fcb_image_file_set()
{
    char *filename;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(fcb_image);
    filename = gtk_file_chooser_get_filename(chooser);
    printf("\nGTK Debug : file selected is %s\n", filename);
    g_free(filename);
}

// called when the convert button is clicked (calls the main function of the OCR)
void on_btn_convert_clicked()
{
    printf("\nGTK Debug : btn_convert clicked\n");
}
