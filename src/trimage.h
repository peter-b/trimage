#ifndef _TRIMAGE_H_
#define _TRIMAGE_H_

#include <glib.h>
#include <cairo.h>

typedef struct {
  double x1, y1;
  double x2, y2;
  double x3, y3;
  double r, g, b, a;
} TiTriangle;

TiTriangle *triangle_new ();
TiTriangle *triangle_new_random ();
TiTriangle *triangle_copy (const TiTriangle *x);
void ti_triangle_free (TiTriangle *x);

GList *ti_triangle_random_list (int len);
void ti_triangle_free_list (GList *lst);

void ti_render_triangle (cairo_t *cr, const TiTriangle *t);
void ti_render_list (cairo_t *cr, GList *triangles);
void ti_render_clear (cairo_t *cr);
void ti_render_to_svg (const char *filename, GList *triangles,
                                 double width, double height);
void ti_render_to_png (const char *filename, GList *triangles,
                                 int width, int height);

#endif /* !_TRIMAGE_H_ */
