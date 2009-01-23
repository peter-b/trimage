#include "trimage.h"
#include <math.h>
#include <string.h>

#define LIST_EXPAND_FACTOR 1.2

static void
list_expand (TiTriangleList *lst)
{
  int nmax = (int) ceil (LIST_EXPAND_FACTOR * lst->max);
  lst->triangles = g_realloc (lst->triangles,
                              nmax * sizeof(TiTriangle *));
  lst->max = nmax;
}

/* Create an empty triangle list.
 *
 * Returns a TiTriangleList with specified initial capacity. The list
 * must be freed with ti_triangle_list_unref() when no longer needed.
 */
TiTriangleList *
ti_triangle_list_new (int capacity)
{
  TiTriangleList *lst = g_new0 (TiTriangleList, 1);
  lst->triangles = g_new0 (TiTriangle *, capacity);
  lst->max = capacity;
  lst->len = 0;
  lst->refcount = 1;
  return lst;
}

/* Append a triangle to a triangle list.
 *
 * Appends the TiTriangle x to the TiTriangleList lst.
 */
void
ti_triangle_list_append (TiTriangleList *lst, TiTriangle *x)
{
  if (lst->len == lst->max)
    list_expand (lst);

  ti_triangle_ref (x);
  lst->triangles[lst->len++] = x;
}

/* Create a list of randomised triangles.
 *
 * Returns a list of new randomised TiTriangles. The list should be
 * freed with ti_triangle_free_list() when no longer needed.
 */
TiTriangleList *
ti_triangle_list_new_random (int len) {
  TiTriangleList *lst = ti_triangle_list_new (len);
  int i;
  for (i = 0; i < len; i++) {
    TiTriangle *t = ti_triangle_new_random ();
    ti_triangle_list_append (lst, t);
    ti_triangle_unref (t);
  }
  return lst;
}

/* Reference a TiTriangleList.
 *
 * Increment the reference count of the triangle list lst.
 */
void
ti_triangle_list_ref (TiTriangleList *lst)
{
  lst->refcount++;
}

/* Unreference a TiTriangleList.
 *
 * Decrements the reference count of the triangle list lst. If the
 * refcount has reached zero, lst is destroyed, all of its triangles
 * are unrefed, and all of the lists resources are freed.
 */
void
ti_triangle_list_unref (TiTriangleList *lst)
{
  int i;

  lst->refcount--;
  if (lst->refcount > 0) return;

  for (i = 0; i < lst->len; i++) {
    ti_triangle_unref (lst->triangles[i]);
  }
  g_free (lst->triangles);
  g_free (lst);
}

/* Copy a list of triangles.
 *
 * Copies a list of TiTriangles, incrementing the reference counts of
 * the individual elements. The returned list should be freed with
 * ti_triangle_free_list() when no longer needed.
 */
TiTriangleList *
ti_triangle_list_copy (TiTriangleList *lst)
{
  TiTriangleList *result = ti_triangle_list_new (lst->len);
  int i;
  for (i = 0; i < lst->len; i++) {
    ti_triangle_list_append (result, lst->triangles[i]);
  }
  return result;
}
