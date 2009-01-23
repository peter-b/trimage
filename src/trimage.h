#ifndef _TRIMAGE_H_
#define _TRIMAGE_H_

#include <glib.h>
#include <cairo.h>

typedef struct {
  double x1, y1;
  double x2, y2;
  double x3, y3;
  double r, g, b, a;
  int refcount;
} TiTriangle;

typedef struct {
  TiTriangle **triangles;
  int len;
  int max;
  int refcount;
} TiTriangleList;

TiTriangle *triangle_new ();
TiTriangle *triangle_new_random ();
TiTriangle *triangle_copy (const TiTriangle *x);
void ti_triangle_ref (TiTriangle *x);
void ti_triangle_unref (TiTriangle *x);

TiTriangleList *ti_triangle_list_new (int capacity);
void ti_triangle_list_append (TiTriangleList *lst, TiTriangle *x);
TiTriangleList *ti_triangle_list_new_random (int len);
void ti_triangle_list_ref (TiTriangleList *lst);
void ti_triangle_list_unref (TiTriangleList *lst);
TiTriangleList *ti_triangle_list_copy (TiTriangleList *lst);

void ti_render_triangle (cairo_t *cr, const TiTriangle *t);
void ti_render_list (cairo_t *cr, TiTriangleList *lst);
void ti_render_clear (cairo_t *cr);
void ti_render_to_svg (const char *filename, TiTriangleList *lst,
                                 double width, double height);
void ti_render_to_png (const char *filename, TiTriangleList *lst,
                                 int width, int height);

double objective (cairo_surface_t *reference, cairo_surface_t *trial);

void ti_crossover (TiTriangleList *parentA, TiTriangleList *parentB,
                   TiTriangleList **childA, TiTriangleList **childB);
TiTriangle *ti_mutate (TiTriangle *x, double prob);
void ti_mutate_list (TiTriangleList *lst, double prob);

#endif /* !_TRIMAGE_H_ */
