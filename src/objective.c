#include "trimage.h"

static inline int fund_dist (unsigned char x,
                             unsigned char y)
{
  int d = y - x;
  return d*d;
}

static inline int pixel_dist (unsigned char* p1, unsigned char* p2)
{
  int d = 0, i;
  /* Start from 1 to skip alpha */
  for (i = 1; i < 4; i++) {
    d += fund_dist (p1[i], p2[i]);
  }
  return d;
}

/* Find the distance between reference and trial images.
 *
 * Returns the mean square distance between the Cairo image surfaces
 * reference and trial, evaluated over each colour component at each
 * pixel.
 */
double
objective (cairo_surface_t *reference,
           cairo_surface_t *trial)
{
  int ref_stride =
    cairo_image_surface_get_stride (reference);
  int tri_stride =
    cairo_image_surface_get_stride (trial);

  int width =
    MIN(cairo_image_surface_get_width (reference),
        cairo_image_surface_get_width (trial));
  int height =
    MIN(cairo_image_surface_get_height (reference),
        cairo_image_surface_get_height (trial));

  unsigned char *ref_data =
    cairo_image_surface_get_data (reference);
  unsigned char *tri_data =
    cairo_image_surface_get_data (trial);

  double result = 0.0;
  int x,y;
  for (x = 0; x < width; x++) {
    int ref_row = x * ref_stride;
    int tri_row = x * tri_stride;
    double row_val = 0;
    for (y = 0; y < width; y++) {
      int col = 4*y;
      row_val += pixel_dist (ref_data + ref_row + col,
                             tri_data + tri_row + col);
    }
    result += row_val;
  }

  return result / (width*height);
}
