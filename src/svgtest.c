#include "trimage.h"

int
main (int argc, char** argv)
{
  const char *filename = "test_triangle.svg";
  if (argc > 1) {
    filename = argv[1];
  }
  GList *tris = ti_triangle_random_list (50);
  ti_render_to_svg (filename, tris, 400, 400);
  ti_triangle_free_list (tris);
  return 0;
}
