#include "trimage.h"
#include <stdio.h>

int
main (int argc, char **argv)
{
  if (argc < 3) {
    printf ("You must specify two PNG image files to compare\n");
    return 1;
  }

  cairo_surface_t* a =
    cairo_image_surface_create_from_png (argv[1]);
  cairo_surface_t* b =
    cairo_image_surface_create_from_png (argv[2]);

  double dist = ti_objective (a, b);

  printf("Distance: %e\n", dist);
  return 0;
}
