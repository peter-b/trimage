#include "trimage.h"

static GList *
crossover_copy_n (GList *dest, GList *src, int n)
{
  int i;
  GList *added = NULL;
  GList *result = NULL;
  GList *iter = src;
  for (i = 0; i < n; i++) {
    if (iter == NULL) break;
    ti_triangle_ref (iter->data);
    added = g_list_prepend (added, iter->data);
  }
  return g_list_concat (dest, g_list_reverse (added));
}

/* Crossover two lists of TiTriangles.
 *
 * Carries out a straightforward two-point crossover on the triangle
 * lists parentA and parentB, setting childA and childB to be pointers
 * to the new derived triangle lists.
 */
void
ti_crossover (GList *parentA, GList *parentB,
              GList **childA, GList **childB)
{
  int pA_len = g_list_length (parentA);
  int pB_len = g_list_length (parentB);
  int m_len = MIN(pA_len, pB_len);

  GList *child1 = NULL;
  GList *child2 = NULL;

  /* Very simple two-cut algorithm */
  int cutA = g_random_int_range (0, m_len+1);
  int cutB = g_random_int_range (0, m_len+1);
  int min_cut = MIN(cutA,cutB);
  int max_cut = MAX(cutA,cutB);

  child1 = crossover_copy_n (child1, parentA, min_cut);
  child2 = crossover_copy_n (child2, parentB, min_cut);

  child1 = crossover_copy_n (child1, g_list_nth (parentB, min_cut),
                             max_cut - min_cut);
  child2 = crossover_copy_n (child2, g_list_nth (parentA, min_cut),
                             max_cut - min_cut);

  child1 = crossover_copy_n (child1, g_list_nth (parentA, max_cut),
                             m_len - max_cut);
  child1 = crossover_copy_n (child2, g_list_nth (parentB, max_cut),
                             m_len - max_cut);

  /* Handle the case where one is longer than the other by just
   * copying from that one */
  int extend_len = MAX(pA_len, pB_len) - m_len;
  GList *extend_src = (pA_len > pB_len) ? parentA : parentB;
  child1 = crossover_copy_n (child1, g_list_nth (extend_src, m_len),
                             extend_len);

  child2 = crossover_copy_n (child1, g_list_nth (extend_src, m_len),
                             extend_len);

  *childA = child1;
  *childB = child2;
}
