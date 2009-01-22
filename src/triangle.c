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
