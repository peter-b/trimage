#include "trimage.h"

/* Create a new triangle.
 *
 * Returns a new TiTriangle with all parameters set to 0. The returned
 * TiTriangle must be freed with ti_triangle_unref() when no longer
 * needed.
 */
TiTriangle *
ti_triangle_new ()
{
  TiTriangle *t = g_new0 (TiTriangle, 1);
  t->refcount = 1;
  return t;
}

/* Create a new randomised triangle.
 *
 * Returns a new TiTriangle with all parameters randomised. The
 * returned TiTriangle must be freed with ti_triangle_unref() when no
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
 * returned TiTriangle must be freed with ti_triangle_unref() when no
 * longer needed.
 */
TiTriangle *
ti_triangle_copy (const TiTriangle *x)
{
  TiTriangle *t =
    (TiTriangle *) g_memdup (x, sizeof (TiTriangle));
  t->refcount = 1;
  return t;
}

/* Reference a TiTriangle.
 *
 * Increment the reference count of the triangle x.
 */
void
ti_triangle_ref (TiTriangle *x)
{
  x->refcount++;
}

/* Unreference a TiTriangle.
 *
 * Decrements the reference count of the triangle x. If the refcount
 * has reached zero, x is destroyed and all its resources freed.
 */
void
ti_triangle_unref (TiTriangle *x)
{
  x->refcount--;
  if (x->refcount <= 0) g_free (x);
}

/* Test if two triangles are equal.
 *
 * Compares the TiTriangles a and b, and returns non-zero if they are
 * equal. If they differ, returns 0.
 */
int
ti_triangle_equal (TiTriangle *a, TiTriangle *b)
{
  int i;
  if (a == b) return 1;

  /* Horrible, horrible hack */
  for (i = 0; i < 10; i++) {
    double *x = (double *) a;
    double *y = (double *) b;
    if (x[i] != y[i]) return 0;
  }
  return 1;
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
 * list and unrefing all of the TiTriangles in it.
 */
void
ti_triangle_free_list (GList *lst)
{
  GList *iter = lst;
  while (iter != NULL) {
    ti_triangle_unref (iter->data);
    iter = g_list_next (iter);
  }
  g_list_free (lst);
}

/* Copy a list of triangles.
 *
 * Copies a list of TiTriangles, incrementing the reference counts of
 * the individual elements. The returned list should be freed with
 * ti_triangle_free_list() when no longer needed.
 */
GList *
ti_triangle_copy_list (GList *lst)
{
  GList *result = NULL;
  GList *iter = lst;
  while (iter != NULL) {
    ti_triangle_ref (iter->data);
    result = g_list_prepend (result, iter->data);
    iter = g_list_next (iter);
  }
  return g_list_reverse (result);
}
