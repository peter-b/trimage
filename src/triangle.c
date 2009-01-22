#include "trimage.h"

TiTriangle *
ti_triangle_new ()
{
  return g_new0 (TiTriangle, 1);
}

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

TiTriangle *
ti_triangle_copy (const TiTriangle *x)
{
  return (TiTriangle *) g_memdup (x, sizeof (TiTriangle));
}

void
ti_triangle_free (TiTriangle *x)
{
  g_free (x);
}
