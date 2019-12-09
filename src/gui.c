#include <gtk/gtk.h>
#include <string.h>
#include "ocr.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "image_operations.h"
#include "spellcheck.h"

GtkWidget *window_start;
GtkWidget *window_main;
GtkWidget *window_about;
GtkWidget *window_advanced;
GtkWidget *window_result;

GtkWidget *g_fcb_image;
GtkWidget *g_window_main_label;
GtkWidget *btn_convert;
GtkWidget *btn_rr;
GtkWidget *btn_rl;

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

GtkWidget *window_spellcheck;
GtkLabel *current_wd_lbl;
GtkLabel *suggested_lbl;
GtkLabel *corrected_lbl;

gboolean show_advanced;

// the current image selected (default is NULL)
char *currentImage;

int open_main_win = 0;
int is_converted = 0;

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

	btn_rr = GTK_WIDGET(gtk_builder_get_object(builder, "btn_rr"));
	btn_rl = GTK_WIDGET(gtk_builder_get_object(builder, "btn_rl"));

    // image previewing
    g_main_image_preview =
        GTK_IMAGE(gtk_builder_get_object(builder, "main_image_preview"));
    g_image_viewport =
        GTK_WIDGET(gtk_builder_get_object(builder, "image_viewport"));

    // GtkTextView Result
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
	gtk_widget_set_sensitive(btn_rl,
            FALSE);
	gtk_widget_set_sensitive(btn_rr,
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
    gtk_widget_set_sensitive(btn_convert,
            TRUE);
	gtk_widget_set_sensitive(btn_rr,
            TRUE);
	gtk_widget_set_sensitive(btn_rl,
            TRUE);
    show_loaded_image();
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

// defined later but needed in on_btn_convert_clicked
void result_to_text_view(GtkTextView *text_view, gchar *text);

// called when the convert button is clicked (calls main function of the OCR)
void on_btn_convert_clicked()
{
    if (currentImage)
    {
        printf("GTK Debug : current image for convert is %s\n", currentImage);
        gtk_label_set_text(GTK_LABEL(g_window_main_label),
                                        "Converting image in text...");

        gchar *recognized_text;
        recognized_text = ocr_main(currentImage);
        result_to_text_view(txt_result, recognized_text);

        if (recognized_text == NULL)
            return;

        is_converted = 1;

        if (show_advanced)
        {
            create_advanced_window();
        }
        gtk_widget_show(window_result);
    }
}

SDL_Surface *load_rotimage()
{
	// Image loading
    init_sdl();
    SDL_Surface *image_surface;
    image_surface = load_image(currentImage);
    size_t image_width = image_surface->w;
    size_t image_height = image_surface->h;

    SDL_Surface *image_rotated_surface;
    image_rotated_surface = SDL_CreateRGBSurface(0, image_height,
			image_width, 32, 0, 0, 0, 0);

    SDL_FreeSurface(image_surface);
    return image_rotated_surface;
}

//rotation right of the picture
void on_btn_rr_clicked()
{

    SDL_Surface *image_rotated = load_rotimage();
    size_t rotated_width = image_rotated->w;

    SDL_Surface *image_surface;
    image_surface = load_image(currentImage);
    size_t image_width = image_surface->w;
    size_t image_height = image_surface->h;

    for (size_t x = 0; x < image_width; x++)
    {
        for (size_t y = 0; y < image_height; y++)
		{
	    	Uint32 pixel = get_pixel(image_surface, x, y);
	    	put_pixel(image_rotated, rotated_width-y, x, pixel);
		}
    }

	Uint32 pixel = get_pixel(image_surface, image_width /2 , 0);

	for (size_t x = 0; x < rotated_width; x++)
	{
		for(size_t y = 0; y < 3; y++)
		{
			put_pixel(image_rotated, x, y, pixel);
		}
	}

    save_image(image_rotated, "tmp/rotated.bmp");

    currentImage = "tmp/rotated.bmp";
    show_loaded_image();
    SDL_FreeSurface(image_rotated);
    SDL_FreeSurface(image_surface);
}

//rotation left of the picture
void on_btn_rl_clicked()
{
	on_btn_rr_clicked();
	on_btn_rr_clicked();
	on_btn_rr_clicked();
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
		gtk_widget_set_sensitive(btn_rr,
            TRUE);
    	gtk_widget_set_sensitive(btn_rl,
            TRUE);
    }

    gtk_widget_destroy(dialog);
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

void result_to_text_view(GtkTextView *text_view, gchar *text)
{
    GtkTextBuffer *textBuffer;
    textBuffer = gtk_text_view_get_buffer(text_view);
    gtk_text_buffer_set_text(textBuffer, text, strlen(text));
}

// if closed with top right "X" gtk_widget_hide_on_delete() is directly called
// as defined in the gui.glade file
void on_btn_close_result_clicked()
{
    gtk_widget_hide(window_result);
}

// Copies the text in the system clipboard
void on_btn_copy_clicked()
{
    GtkTextIter start, end;
    gchar *text;
    GtkTextBuffer *txt_buff = gtk_text_view_get_buffer(txt_result);

    gtk_text_buffer_get_bounds(txt_buff, &start, &end) ;

    text = gtk_text_buffer_get_text(txt_buff, &start, &end, FALSE);

    gtk_clipboard_set_text(gtk_clipboard_get(GDK_SELECTION_CLIPBOARD),
            text, strlen(text));
    gtk_clipboard_store(gtk_clipboard_get(GDK_SELECTION_CLIPBOARD));
    printf("\nGTK Debug : copy \"%s\"\n", text);
}

// called in on_btn_save_result_clicked() for saving the result in a .txt file
void save_result(char *path)
{
    printf("\nGTK Debug : saving result at %s\n", path);

    GtkTextIter start, end;
    gchar *text;
    GtkTextBuffer *txt_buff = gtk_text_view_get_buffer(txt_result);

    gtk_text_buffer_get_bounds(txt_buff, &start, &end);

    text = gtk_text_buffer_get_text(txt_buff, &start, &end, FALSE);

    FILE *fs;
    fs = fopen(path, "w");
    fprintf(fs, "%s", text);
    g_free(text);
    fclose(fs);
}

// Called when :
// - the save button is clicked in the result window
// - the save button in the menubar is clicked
void on_btn_save_result_clicked()
{
    // we don't open the save window since nothing has been converted
    // it shows to the user an alert
    if (!is_converted)
    {
        GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(GTK_WINDOW(window_main),
                                        flags,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_CLOSE,
                        "The image has not been converted to text yet !");

        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    GtkWidget *dialog;
    GtkFileChooser *chooser;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Save Result",
                                        GTK_WINDOW(window_result),
                                        action,
                                        "Cancel",
                                        GTK_RESPONSE_CANCEL,
                                        "Save",
                                        GTK_RESPONSE_ACCEPT,
                                        NULL);

    chooser = GTK_FILE_CHOOSER(dialog);

    // for overwriting a file
    gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);

    gtk_file_chooser_set_current_name(chooser, "Untitled.txt");

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *result_path;
        result_path = gtk_file_chooser_get_filename(chooser);
        save_result(result_path);
        g_free(result_path);
    }

    gtk_widget_destroy(dialog);
}

// ****************************************************************************
// *************************** SPELLCHECK *************************************
// ****************************************************************************

GtkTextIter nextIterator;

GtkTextIter startCorrection;
GtkTextIter endCorrection;

GtkTextMark *mark;

gchar *corrected;
gint word_length;

void next_word_spellcheck()
{
    gtk_label_set_text(corrected_lbl, "");
    GtkTextIter current, endOfWord;
    gchar *word;
    GtkTextBuffer *txt_buff = gtk_text_view_get_buffer(txt_result);

    current = nextIterator;

    endOfWord = current;

    if (gtk_text_iter_is_end(&nextIterator))
        gtk_text_buffer_get_start_iter(txt_buff, &nextIterator);

    while (!gtk_text_iter_starts_word(&current))
    {
        if (gtk_text_iter_is_end(&current))
            break;
        gtk_text_iter_forward_char(&current);
    }

    while (!gtk_text_iter_ends_word(&endOfWord))
    {
        if (gtk_text_iter_is_end(&endOfWord))
            break;
        gtk_text_iter_forward_char(&endOfWord);
    }

    word = gtk_text_buffer_get_text(txt_buff, &current, &endOfWord, FALSE);

    if (strlen(word))
    {
        word_length = strlen(word);
        gtk_label_set_text(current_wd_lbl, word);
        corrected = spellcheck(word);
        gtk_label_set_text(suggested_lbl, corrected);
        startCorrection = current;
        endCorrection = endOfWord;
    }

    if (gtk_text_iter_is_end(&endOfWord))
    {
        gtk_text_buffer_get_start_iter(txt_buff, &nextIterator);
        return;
    }

    while (!gtk_text_iter_starts_word(&endOfWord))
    {
        if (gtk_text_iter_is_end(&endOfWord))
            break;
        gtk_text_iter_forward_char(&endOfWord);
    }

    nextIterator = endOfWord;
    gtk_text_buffer_move_mark(txt_buff, mark, &nextIterator);
}

void on_btn_spellchecker_clicked()
{
    GtkBuilder *builder = gtk_builder_new_from_file("src/glade/gui.glade");

    window_spellcheck =
        GTK_WIDGET(gtk_builder_get_object(builder, "window_spellcheck"));

    suggested_lbl = GTK_LABEL(gtk_builder_get_object(builder, "suggested_lbl"));

    current_wd_lbl =
        GTK_LABEL(gtk_builder_get_object(builder, "current_wd_lbl"));

    corrected_lbl =
        GTK_LABEL(gtk_builder_get_object(builder, "corrected_lbl"));

    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(window_spellcheck);
    g_object_unref(builder);

    GtkTextBuffer *txt_buff = gtk_text_view_get_buffer(txt_result);
    gtk_text_buffer_get_start_iter(txt_buff, &nextIterator);

    mark =
        gtk_text_buffer_create_mark(txt_buff, "spellcheck", &nextIterator,TRUE);

    next_word_spellcheck();
}

void on_btn_cancel_clicked()
{
    gtk_widget_destroy(window_spellcheck);
}

void on_next_btn_clicked()
{
    next_word_spellcheck();
}

void on_correct_btn_clicked()
{
    GtkTextBuffer *txt_buff = gtk_text_view_get_buffer(txt_result);
    gtk_text_buffer_delete(txt_buff, &startCorrection, &endCorrection);
    gtk_text_buffer_insert(txt_buff, &startCorrection, corrected, word_length);
    gtk_label_set_text(corrected_lbl, "Corrected");
    gtk_text_buffer_get_iter_at_mark(txt_buff, &nextIterator, mark);
}