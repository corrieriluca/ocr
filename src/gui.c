#include <gtk/gtk.h>

GtkWidget *window_start;
GtkWidget *window_main;
GtkWidget *window_about;
GtkWidget *window_advanced;
GtkWidget *window_result;

GtkWidget *g_fcb_image;
GtkWidget *g_window_main_label;
GtkWidget *btn_convert;

GtkWidget *g_image_viewport;
GtkImage *g_main_image_preview;
GdkPixbuf *pixbuf;

GtkWidget *g_advanced_viewport;
GtkImage *g_advanced_preview;
GdkPixbuf *advanced_pixbuf;
GtkTextView *txt_result;

GtkToggleButton *rb_original;
GtkToggleButton *rb_grayscale;
GtkToggleButton *rb_binarize;
GtkToggleButton *rb_segmentation;

gboolean show_advanced;

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
        GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    window_about =
        GTK_WIDGET(gtk_builder_get_object(builder, "window_about"));
	window_result =
		GTK_WIDGET(gtk_builder_get_object(builder, "window_result"));

    // file chooser button in window_main_menu
    g_fcb_image =
        GTK_WIDGET(gtk_builder_get_object(builder, "fcb_image"));

    // label just above the file chooser button
    g_window_main_label =
        GTK_WIDGET(gtk_builder_get_object(builder, "window_main_label"));

    btn_convert = 
		GTK_WIDGET(gtk_builder_get_object(builder, "btn_convert"));

	g_main_image_preview =
        GTK_IMAGE(gtk_builder_get_object(builder, "main_image_preview"));
    g_image_viewport =
        GTK_WIDGET(gtk_builder_get_object(builder, "image_viewport"));
	txt_result =                                                                    
        GTK_TEXT_VIEW(gtk_builder_get_object(builder, "txt_result"));

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
	gtk_widget_set_sensitive(btn_convert,
            FALSE);
}


// called when starting window is closed
void on_window_start_destroy()
{
	if(open_main_win == 0)
    	gtk_main_quit();
}

// ****************************************************************************
// ***************************** ADVANCED WINDOW ******************************
// ****************************************************************************

void on_window_advanced_size_allocate()
{
    // if no image is loaded
    if (!advanced_pixbuf)
        return;

    GtkAllocation allocation;
    gtk_widget_get_allocation(g_advanced_viewport, &allocation);
    int wanted_width = allocation.width;
    int wanted_height = allocation.height;
    float viewport_ratio = (float) wanted_height / wanted_width;
    float image_ratio = (float) gdk_pixbuf_get_height(advanced_pixbuf) /
        gdk_pixbuf_get_width(advanced_pixbuf);

    if (viewport_ratio > image_ratio)
    {
        wanted_width -= 4;
        wanted_height = (int)(wanted_width * image_ratio);
    }
    else
    {
        wanted_height -= 4;
        wanted_width = (int)(wanted_height / image_ratio);
    }
    gtk_image_set_from_pixbuf(g_advanced_preview,
                                gdk_pixbuf_scale_simple(
                                    advanced_pixbuf,
                                    wanted_width, wanted_height,
                                    GDK_INTERP_BILINEAR));

    gtk_widget_queue_resize(window_advanced);
}

void change_advanced_image(char *path)
{
    advanced_pixbuf = gdk_pixbuf_new_from_file(path, NULL);
    gtk_image_set_from_pixbuf(g_advanced_preview, pixbuf);
    on_window_advanced_size_allocate();
}

// called if show_advanced is set to TRUE
void create_advanced_window()
{
    if (window_advanced)
        gtk_widget_destroy(window_advanced);

    GtkBuilder *builder = gtk_builder_new_from_file("src/glade/gui.glade");
    
    window_advanced =
        GTK_WIDGET(gtk_builder_get_object(builder, "window_advanced"));
    
    rb_original =
        GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "rb_original"));
    rb_grayscale =
        GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "rb_grayscale"));
    rb_binarize =
        GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "rb_binarize"));
    rb_segmentation =
        GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "rb_segmentation"));

    g_advanced_preview =
        GTK_IMAGE(gtk_builder_get_object(builder, "advanced_preview"));
    g_advanced_viewport =
        GTK_WIDGET(gtk_builder_get_object(builder, "advanced_viewport"));

    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(window_advanced);
    change_advanced_image("tmp/original.bmp");
    g_object_unref(builder);
}

// called on destroy window_advanced
void on_window_advanced_destroy(GtkWidget *object)
{
    //gtk_widget_destroy(object);
    gtk_widget_destroyed(object, &window_advanced);
}

// called when the value of a radio button changes
void on_rb_advanced_toggled()
{
    if (gtk_toggle_button_get_active(rb_original))
        change_advanced_image("tmp/original.bmp");
    else if (gtk_toggle_button_get_active(rb_grayscale))
        change_advanced_image("tmp/grayscale.bmp");
    else if (gtk_toggle_button_get_active(rb_binarize))
        change_advanced_image("tmp/binarized.bmp");
    else if (gtk_toggle_button_get_active(rb_segmentation))
        change_advanced_image("tmp/segmentation.bmp");
}

// ****************************************************************************
// ***************************** MAIN WINDOW **********************************
// ****************************************************************************

// called when main window is closed
void on_window_main_menu_destroy()
{
	gtk_main_quit();
}

// Called when the main window need to be resized
// (manually or by show_loaded_image)
// It applies a best fit zoom to the image preview
void on_window_main_menu_size_allocate()
{
    // if no image is loaded
    if (!pixbuf)
        return;

    GtkAllocation allocation;
    gtk_widget_get_allocation(g_image_viewport, &allocation);
    int wanted_width = allocation.width;
    int wanted_height = allocation.height;
    float viewport_ratio = (float) wanted_height / wanted_width;
    float image_ratio = (float) gdk_pixbuf_get_height(pixbuf) /
        gdk_pixbuf_get_width(pixbuf);

    if (viewport_ratio > image_ratio)
    {
        wanted_width -= 4;
        wanted_height = (int)(wanted_width * image_ratio);
    }
    else
    {
        wanted_height -= 4;
        wanted_width = (int)(wanted_height / image_ratio);
    }
    gtk_image_set_from_pixbuf(g_main_image_preview,
                                gdk_pixbuf_scale_simple(
                                    pixbuf,
                                    wanted_width, wanted_height,
                                    GDK_INTERP_BILINEAR));

    gtk_widget_queue_resize(window_main);
}

// Called in on_fcb_image_file_set() and on_menubar_btn_load_activate()
// Displays the loaded image on main_image_preview
void show_loaded_image()
{
    pixbuf = gdk_pixbuf_new_from_file(currentImage, NULL);
    gtk_image_set_from_pixbuf(g_main_image_preview, pixbuf);
    on_window_main_menu_size_allocate();
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
    gtk_widget_set_sensitive(btn_convert,
            TRUE);
}

void on_cb_advanced_toggled(GtkToggleButton *toggleButton)
{
    show_advanced = gtk_toggle_button_get_active(toggleButton);
    if (show_advanced)
    {
        printf("\nGTK Debug : show_advanced is TRUE\n");
    }
    else
    {
        printf("\nGTK Debug : show_advanced is FALSE\n");
    }
}

// called when the convert button is clicked (calls main function of the OCR)
void on_btn_convert_clicked()
{
    if (currentImage)
    {
        printf("GTK Debug : current image for convert is %s\n", currentImage);
        gtk_label_set_text(GTK_LABEL(g_window_main_label),
                                        "Converting image in text...");
        if (show_advanced)
        {
            create_advanced_window();
        }
    }

	gtk_widget_show(window_result);
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

		gtk_widget_set_sensitive(btn_convert,
            TRUE);
    }

    gtk_widget_destroy(dialog);
}

// Called when the save button is clicked in the menubar
void on_menubar_btn_save_activate()
{
    // TODO
    // save the text
    printf("\nGTK Debug : on_menubar_btn_save_activate() called\n");
}

// Shows an about dialog window (import it from the glade file each time)
void on_menubar_btn_about_activate()
{
    GtkBuilder *builder = gtk_builder_new_from_file("src/glade/gui.glade");
    GtkWidget *window_about =
        GTK_WIDGET(gtk_builder_get_object(builder, "window_about"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(window_about);
    g_object_unref(builder);
}

// Called when the user tries to close the about window
// with the close button of the dialog
void on_window_about_response(GtkDialog *dialog)
{
    gtk_widget_destroy(GTK_WIDGET(dialog));
}

// ****************************************************************************
// *************************** RESULT WINDOW **********************************
// ****************************************************************************

//if closed with top right "X" widget is destroyed and window can't be reopened
//could use "gtk_widget_hide_on_delete ()" to solve if necessary
void on_btn_close_result_clicked()
{
    gtk_widget_hide(window_result);
}

void on_btn_copy_clicked()
{
    GtkTextIter start, end;
    gchar *text;
    GtkTextBuffer *txt_buff = gtk_text_view_get_buffer (txt_result);

    gtk_text_buffer_get_bounds (txt_buff, &start, &end);

    text = gtk_text_buffer_get_text (txt_buff, &start, &end, FALSE);

    printf("\nGTK Debug : copy \"%s\" \n", text);
}
