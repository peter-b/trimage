#include "trimage.h"

int
main (int argc, char** argv)
{
  const char *filename = "test_triangle.svg";
  if (argc > 1) {
    filename = argv[1];
  }
  TiTriangle *t = ti_triangle_new_random ();
  GList *l = g_list_prepend (NULL, t);
  ti_render_to_svg (filename, l, 400, 400);
  g_list_free (l);
  ti_triangle_free (t);
  return 0;
}
