#include "trimage.h"

void
ti_render_triangle (cairo_t *cr, const TiTriangle *t)
{
  cairo_set_source_rgba (cr, t->r, t->g, t->b, t->a);
  cairo_new_path (cr);
  cairo_move_to (cr, t->x1, t->y1);
  cairo_line_to (cr, t->x2, t->y2);
  cairo_line_to (cr, t->x3, t->y3);
  cairo_fill (cr);
}

void
ti_render_list (cairo_t *cr, GList *triangles)
{
  GList *iter = triangles;
  while (iter != NULL) {
    ti_render_triangle (cr, (TiTriangle *) iter->data);
    iter = g_list_next (iter);
  }
}

void
ti_render_clear (cairo_t *cr)
{
  cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
  cairo_reset_clip (cr);
  cairo_paint (cr);
}

void
ti_render_to_svg (const char *filename, GList *triangles,
                  double width, double height)
{
  cairo_surface_t *surface =
    cairo_svg_surface_create (filename, width, height);

  /* Draw triangle list */
  cairo_t *cr = cairo_create (surface);
  cairo_scale (cr, width, height);
  ti_render_clear (cr);
  ti_render_list (cr, triangles);

  cairo_destroy(cr);
  cairo_surface_destroy (surface);
}


void
ti_render_to_png (const char *filename, GList *triangles,
                  int width, int height)
{
  cairo_surface_t *surface =
    cairo_image_surface_create (CAIRO_FORMAT_ARGB32,
                                width, height);

  /* Draw triangle list */
  cairo_t *cr = cairo_create (surface);
  cairo_scale (cr, width, height);
  ti_render_clear (cr);
  ti_render_list (cr, triangles);

  cairo_surface_write_to_png (surface, filename);

  cairo_destroy(cr);
  cairo_surface_destroy (surface);
}
