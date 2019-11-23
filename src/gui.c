#include <gtk/gtk.h>

GtkWidget *window_start;
GtkWidget *window_main;
GtkWidget *window_about;

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

    window_start =
        GTK_WIDGET(gtk_builder_get_object(builder, "window_start"));
    window_main =
        GTK_WIDGET(gtk_builder_get_object(builder, "window_main_menu"));
    window_about =
        GTK_WIDGET(gtk_builder_get_object(builder, "window_about"));

    // file chooser button in window_main_menu
    g_fcb_image =
        GTK_WIDGET(gtk_builder_get_object(builder, "fcb_image"));

    // label just above the file chooser button
    g_window_main_label =
        GTK_WIDGET(gtk_builder_get_object(builder, "window_main_label"));

    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    gtk_widget_show(window_start);
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
    gtk_widget_destroy(window_start);
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

// called when main window is closed and on_menubar_btn_load_activate()
void on_window_main_menu_destroy()
{
	gtk_main_quit();
}

// Called in on_fcb_image_file_set() and on_menubar_btn_load_activate()
// Displays the loaded image on main_image_view
void show_loaded_image()
{
    // TODO
    // shows the loaded image
    printf("\nGUI Debug : show_loaded_image() called\n");
}

// called when a file is selected with the file chooser button
void on_fcb_image_file_set()
{
    char *filename;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(g_fcb_image);
    filename = gtk_file_chooser_get_filename(chooser);
    printf("\nGTK Debug : file selected is %s\n", filename);
    currentImage = filename;
    show_loaded_image();
}

// called when the convert button is clicked (calls main function of the OCR)
void on_btn_convert_clicked()
{
    if (currentImage)
    {
        printf("GTK Debug : current image for convert is %s\n", currentImage);
        gtk_label_set_text(GTK_LABEL(g_window_main_label),
                                        "Converting image in text...");
    }
    else
    {
        printf("GTK Debug : ERROR no image selected !!\n");
        gtk_label_set_text(GTK_LABEL(g_window_main_label),
                                        "ERROR : no file is selected");
    }
}

// ****************************************************************************
// ***************************** MENU BAR *************************************
// ****************************************************************************

void on_menubar_btn_load_activate()
{
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Choose an image",
                                            GTK_WINDOW(window_main),
                                            action,
                                            "Cancel",
                                            GTK_RESPONSE_CANCEL,
                                            "Open",
                                            GTK_RESPONSE_ACCEPT,
                                            NULL);

    // configuring the file filter
    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_add_pattern(filter, "*.png");
    gtk_file_filter_add_pattern(filter, "*.bmp");
    gtk_file_filter_add_pattern(filter, "*.jpg");
    gtk_file_filter_add_pattern(filter, "*.jpeg");
    gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(dialog), filter);

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        GFile *file = gtk_file_chooser_get_file(chooser);

        // setting the file of the FileChooserButton to the file selected with
        // this alternative method for coherence
        GtkFileChooser *chooserButton = GTK_FILE_CHOOSER(g_fcb_image);
        gtk_file_chooser_set_file(chooserButton, file, NULL);

        printf("\nGTK Debug : file selected is %s\n", filename);
        currentImage = filename;
        show_loaded_image();
    }

    gtk_widget_destroy(dialog);
}

void on_menubar_btn_save_activate()
{
    // TODO
    // save the text
    printf("\nGTK Debug : on_menubar_btn_save_activate() called\n");
}

// Shows an about dialog window (import it from the glade file each time)
void on_menubar_btn_about_activate()
{
    printf("\nGTK Debug : on_menubar_btn_about_activate() called\n");
    GtkBuilder *builder = gtk_builder_new_from_file("src/glade/gui.glade");
    GtkWidget *window_about =
        GTK_WIDGET(gtk_builder_get_object(builder, "window_about"));
    gtk_widget_show(window_about);
    g_object_unref(builder);

}