#include <gtk/gtk.h>

GtkWidget *window;
GtkWidget *window_main;

GtkWidget *g_fcb_image;
GtkWidget *g_window_main_label;

// the current image selected (default is NULL)
char *currentImage;

int open_main_win = 0;

void launch_gui(int argc, char *argv[])
{
    GtkBuilder *builder;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("src/glade/gui.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_start"));
    window_main = GTK_WIDGET(gtk_builder_get_object(builder, "window_main_menu"));

    // file chooser button in window_main_menu
    g_fcb_image = GTK_WIDGET(gtk_builder_get_object(builder, "fcb_image"));
    // label just above the file chooser button
    g_window_main_label = GTK_WIDGET(gtk_builder_get_object(builder, "window_main_label"));

    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    gtk_widget_show(window);
    gtk_main();
}

// called when the user quits the app from the
// - start window
// - the main window (menu bar)
// - the main window (quit button) NOT IMPLEMENTED
void on_btn_quit_clicked()
{
    gtk_main_quit();
}

// ****************************************************************************
// ***************************** START WINDOW *********************************
// ****************************************************************************

// the "start" button is clicked
void on_btn_start_app_clicked()
{
    open_main_win = 1;
    gtk_widget_destroy(window);
    gtk_widget_show(window_main);
}


// called when starting window is closed
void on_window_start_destroy()
{
	if(open_main_win == 0)
    	gtk_main_quit();
}

// ****************************************************************************
// ***************************** MAIN WINDOW **********************************
// ****************************************************************************

// called when main window is closed
void on_window_main_menu_destroy()
{
	gtk_main_quit();
}

// called when a file is selected with the file chooser button
void on_fcb_image_file_set()
{
    char *filename;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(g_fcb_image);
    filename = gtk_file_chooser_get_filename(chooser);
    printf("\nGTK Debug : file selected is %s\n", filename);
    currentImage = filename;
}

// called when the convert button is clicked (calls the main function of the OCR)
void on_btn_convert_clicked()
{
    printf("\nGTK Debug : on_btn_convert_clicked called !\n");
    if (currentImage)
    {
        printf("GTK Debug : current image for convert is %s\n", currentImage);
        gtk_label_set_text(GTK_LABEL(g_window_main_label), "Converting image in text...");
    }
    else
    {
        printf("GTK Debug : ERROR no image selected !!\n");
        gtk_label_set_text(GTK_LABEL(g_window_main_label), "ERROR : no file is selected");
    }
}

// ****************************************************************************
// ***************************** MENU BAR *************************************
// ****************************************************************************

void on_menubar_btn_load_activate()
{
    // TODO
    // something similar to on_fcb_image_file_set() but with a dialog window
    printf("\nGTK Debug : on_menubar_btn_load_activate() called\n");
}

void on_menubar_btn_save_activate()
{
    // TODO
    // save the text
    printf("\nGTK Debug : on_menubar_btn_save_activate() called\n");
}

void on_menubar_btn_about_activate()
{
    // TODO
    // show an 'about' window
    printf("\nGTK Debug : on_menubar_btn_about_activate() called\n");

}