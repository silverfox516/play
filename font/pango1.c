#include <pango/pangocairo.h>
#include <cairo/cairo-pdf.h>
#include <cairo/cairo.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    cairo_t *cr;
    char *filename;
    cairo_status_t status;
    cairo_surface_t *surface;
    PangoLayout *layout;
    PangoFontDescription *desc;
    PangoRectangle ink;
    PangoRectangle logical;
    int width;

    if (argc != 5) {
        g_printerr("Usage: %s STRING WIDTH WRAP_MODE PDF_FILE\n", argv[0]);
        return 1;
    }

    surface = cairo_pdf_surface_create(argv[4], 200, 200);
    cr = cairo_create(surface);
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_paint(cr);

    layout = pango_cairo_create_layout(cr);
    desc = pango_font_description_from_string("Sans 12");
    pango_layout_set_font_description(layout, desc);
    pango_font_description_free(desc);
    pango_layout_set_text(layout, argv[1], -1);
    pango_layout_set_width(layout, atoi(argv[2]));

    if (!strcmp(argv[3], "word")) {
        pango_layout_set_wrap(layout, PANGO_WRAP_WORD);
    } else if (!strcmp(argv[3], "char")) {
        pango_layout_set_wrap(layout, PANGO_WRAP_CHAR);
    } else if (!strcmp(argv[3], "word-char")) {
        pango_layout_set_wrap(layout, PANGO_WRAP_WORD_CHAR);
    } else {
        g_printerr("WRAP_MODE must be 'word' or 'char' or 'word-char'");
        return 1;
    }

    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_move_to(cr, 0, 0);
    pango_cairo_show_layout(cr, layout);

    pango_layout_get_size(layout, &width, NULL);
    printf("size: width=%d\n", width);
    pango_layout_get_extents(layout, &ink, &logical);
    printf("extents: ink width=%d, logical width=%d\n", ink.width, logical.width);
    pango_layout_get_pixel_extents(layout, &ink, &logical);
    printf("pixel extents: ink width=%d, logical width=%d\n", ink.width, logical.width);

    g_object_unref(layout);
    cairo_destroy(cr);
    cairo_surface_finish(surface);
    status = cairo_surface_status(surface);
    cairo_surface_destroy(surface);
    if (status != CAIRO_STATUS_SUCCESS) {
        g_printerr("Could not save pdf to '%s'\n", filename);
        return 1;
    }

    return 0;
}
