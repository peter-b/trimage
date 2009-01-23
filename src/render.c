#include "trimage.h"

/* Render a single triangle.
 *
 * Renders the TiTriangle t to the Cairo context cr.
 */
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

/* Render a list of triangles.
 *
 * Renders a list of TiTriangles to the Cairo context cr.
 */
void
ti_render_list (cairo_t *cr, TiTriangleList *lst)
{
  int i;
  for (i = 0; i < lst->len; i++) {
    ti_render_triangle (cr, lst->triangles[i]);
  }
}

/* Clear a Cairo context to black.
 *
 * Fills the Cairo context cr with uniform opaque black.
 */
void
ti_render_clear (cairo_t *cr)
{
  cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
  cairo_reset_clip (cr);
  cairo_paint (cr);
}

/* Render a list of triangles directly to SVG.
 *
 * Renders the list of TiTriangles triangles to filename as an SVG
 * image with the given width and height in points.
 */
void
ti_render_to_svg (const char *filename, TiTriangleList *lst,
                  double width, double height)
{
  cairo_surface_t *surface =
    cairo_svg_surface_create (filename, width, height);

  /* Draw triangle list */
  cairo_t *cr = cairo_create (surface);
  cairo_scale (cr, width, height);
  ti_render_clear (cr);
  ti_render_list (cr, lst);

  cairo_destroy(cr);
  cairo_surface_destroy (surface);
}

/* Render a list of triangles directly to PNG.
 *
 * Renders the list of TiTriangles triangles to filename as an PNG
 * image with the given width and height in pixels.
 */
void
ti_render_to_png (const char *filename, TiTriangleList *lst,
                  int width, int height)
{
  cairo_surface_t *surface =
    cairo_image_surface_create (CAIRO_FORMAT_ARGB32,
                                width, height);

  /* Draw triangle list */
  cairo_t *cr = cairo_create (surface);
  cairo_scale (cr, width, height);
  ti_render_clear (cr);
  ti_render_list (cr, lst);

  cairo_surface_write_to_png (surface, filename);

  cairo_destroy(cr);
  cairo_surface_destroy (surface);
}
