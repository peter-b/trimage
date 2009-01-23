#include "trimage.h"

int
main (int argc, char** argv)
{
  const char *filename = "test_triangle.png";
  if (argc > 1) {
    filename = argv[1];
  }
  TiTriangleList *tris = ti_triangle_list_new_random (50);
  ti_render_to_png (filename, tris, 400, 400);
  ti_triangle_list_unref (tris);
  return 0;
}
