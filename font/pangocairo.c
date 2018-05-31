#include <pango/pangocairo.h>

#define FONT    "Ubuntu Regular 13"
#define TEXT    "The quick brown fox jumps over the lazy dog"

static void draw_text(cairo_t* cr)
{
    PangoLayout *layout;
    PangoFontDescription *desc;
    
    layout = pango_cairo_create_layout(cr);
    pango_layout_set_text(layout, TEXT, -1);
    desc = pango_font_description_from_string(FONT);
    pango_layout_set_font_description(layout, desc);
    pango_font_description_free(desc);

    cairo_save(cr);
    cairo_set_source_rgb(cr, 0, 0, 0);
    pango_cairo_update_layout(cr, layout);
    cairo_move_to(cr, 20, 20);
    pango_cairo_show_layout(cr, layout);
    cairo_restore(cr);
    g_object_unref(layout);
}

int main(void)
{
    cairo_t *cr;
    gchar *filename = "image.png";
    cairo_status_t status;
    cairo_surface_t *surface;

    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 400, 100);
    cr = cairo_create(surface);
    cairo_set_source_rgb(cr, 0.5, 1.0, 0.7);
    cairo_paint(cr);
    draw_text(cr);
    cairo_destroy(cr);

    status = cairo_surface_write_to_png(surface, filename);
    cairo_surface_destroy(surface);
    if (status != CAIRO_STATUS_SUCCESS) {
        g_printerr("Could not save png to '%s', err %d\n", filename, status);
        return 1;
    }

	return 0;
}
