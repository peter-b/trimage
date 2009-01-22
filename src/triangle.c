#include "trimage.h"

/* Create a new triangle.
 *
 * Returns a new TiTriangle with all parameters set to 0. The returned
 * TiTriangle must be freed with ti_triangle_free() when no longer
 * needed.
 */
TiTriangle *
ti_triangle_new ()
{
  return g_new0 (TiTriangle, 1);
}

/* Create a new randomised triangle.
 *
 * Returns a new TiTriangle with all parameters randomised. The
 * returned TiTriangle must be freed with ti_triangle_free() when no
 * longer needed.
 */
TiTriangle *
ti_triangle_new_random ()
{
  TiTriangle *t = ti_triangle_new ();
  int i;

  /* Horrible, horrible hack */
  double* d = (double *) t;
  for (i = 0; i < 10; i++) {
    d[i] = g_random_double ();
  }

  return t;
}

/* Copy a TiTriangle.
 *
 * Returns a new TiTriangle with the same parameters as x. The
 * returned TiTriangle must be freed with ti_triangle_free() when no
 * longer needed.
 */
TiTriangle *
ti_triangle_copy (const TiTriangle *x)
{
  return (TiTriangle *) g_memdup (x, sizeof (TiTriangle));
}

/* Free a TiTriangle.
 *
 * The triangle x is destroyed and all its resources freed.
 */
void
ti_triangle_free (TiTriangle *x)
{
  g_free (x);
}

/* Create a list of randomised triangles.
 *
 * Returns a list of new randomised TiTriangles. The list should be
 * freed with ti_triangle_free_list() when no longer needed.
 */
GList *
ti_triangle_random_list (int len) {
  GList *lst = NULL;
  int i;
  for (i = 0; i < len; i++) {
    TiTriangle *t = ti_triangle_new_random ();
    lst = g_list_prepend (lst, t);
  }
  return lst;
}

/* Free a list of triangles.
 *
 * Destroys a list of TiTriangles, freeing the resources used by the
 * list and all of the TiTriangles in it.
 */
void
ti_triangle_free_list (GList *lst)
{
  GList *iter = lst;
  while (iter != NULL) {
    ti_triangle_free (iter->data);
    iter = g_list_next (iter);
  }
  g_list_free (lst);
}
