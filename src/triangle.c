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

