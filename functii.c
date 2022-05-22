#include "header.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Graph *create()
{
  Graph *g = (Graph *)malloc(sizeof(Graph));

  if (g == NULL)
    {
      printf("Nu s-a putut aloca dinamic.");
      exit(1);
    }

  g->a = NULL;
  g->cost = NULL;
  g->N = 0;
  g->M = 0;

  return g;
}

void CitireFisier(FILE *f, Graph *orientat, Graph *neorientat, char ***tabel, int *n)
{
  int i, cod = -1, ccod = -1, nr, cnr;
  char oras[100], *poras, *pnumar;

  while (fgets(oras, 100, f))
    {
      poras = strtok(oras, ",");
      pnumar = strtok(NULL, ", ");

      nr = atoi(pnumar);

      for (i = 0; i < (*n); i++)
        {
          if (strcmp(poras, (*tabel)[i]) == 0)
            cod = i;
        }

      if (cod == -1)
        {
          (*n)++;
          *tabel = (char **)realloc(*tabel, (*n) * sizeof(char *));
          (*tabel)[(*n) - 1] = (char *)malloc(100 * sizeof(char));
          strcpy((*tabel)[*n - 1], poras);
          cod = *n - 1;

          orientat->a = (int **)realloc(orientat->a, (*n) * sizeof(int *));
          orientat->a[*n - 1] = NULL;
          orientat->N++;
          for (i = 0; i < *n; i++)
            {
              orientat->a[i] = (int *)realloc(orientat->a[i], (*n) * sizeof(int));
            }

          for (i = 0; i < *n; i++)
            {
              orientat->a[i][*n - 1] = 0;
              orientat->a[*n - 1][i] = 0;
            }

          orientat->cost = (int **)realloc(orientat->cost, (*n) * sizeof(int *));
          orientat->cost[*n - 1] = NULL;

          for (i = 0; i < *n; i++)
            {
              orientat->cost[i] = (int *)realloc(orientat->cost[i], (*n) * sizeof(int));
            }

          for (i = 0; i < *n; i++)
            {
              orientat->cost[i][*n - 1] = 0;
              orientat->cost[*n - 1][i] = 0;
            }

          neorientat->a = (int **)realloc(neorientat->a, (*n) * sizeof(int *));
          neorientat->N++;
          neorientat->a[*n - 1] = NULL;
          for (i = 0; i < *n; i++)
            neorientat->a[i] = (int *)realloc(neorientat->a[i], (*n) * sizeof(int));

          for (i = 0; i < *n; i++)
            {
              neorientat->a[i][*n - 1] = 0;
              neorientat->a[*n - 1][i] = 0;
            }

          neorientat->cost = (int **)realloc(neorientat->cost, (*n) * sizeof(int *));
          neorientat->cost[*n - 1] = NULL;
          for (i = 0; i < *n; i++)
            neorientat->cost[i] = (int *)realloc(neorientat->cost[i], (*n) * sizeof(int));

          for (i = 0; i < *n; i++)
            {
              neorientat->cost[i][*n - 1] = 0;
              neorientat->cost[*n - 1][i] = 0;
            }
        }

      if (ccod != -1) //sarim primul oras
        {
          if (orientat->a[ccod][cod] == 0)
            {
              orientat->a[ccod][cod] = 1;
              orientat->M++;
              orientat->cost[ccod][cod] = nr - cnr;
            }

          if (neorientat->a[ccod][cod] == 0)
            {
              neorientat->a[cod][ccod] = 1;
              neorientat->a[ccod][cod] = 1;
              neorientat->M++;
              neorientat->cost[cod][ccod] = nr - cnr;
              neorientat->cost[ccod][cod] = nr - cnr;
            }
        }

      ccod = cod;
      cod = -1;
      cnr = nr;
    }
}

int Min(Graph *g, int *imin, int *jmin)
{
  int i, j, min, primul = 1;

  for (i = 0; i < g->N; i++)
    for (j = i; j < g->N; j++)
      if (g->a[i][j])
        {
          if (primul)
            {
              min = g->cost[i][j];
              *imin = i;
              *jmin = j;
              primul = 0;
            }
          else if (g->cost[i][j] < min)
            {
              min = g->cost[i][j];
              *imin = i;
              *jmin = j;
            }
        }

  return min;
}

int Max(Graph *g, int *imax, int *jmax)
{
  int i, j, max, primul = 1;

  for (i = 0; i < g->N; i++)
    for (j = i; j < g->N; j++)
      if (g->a[i][j])
        {
          if (primul)
            {
              max = g->cost[i][j];
              *imax = i;
              *jmax = j;
              primul = 0;
            }
          else if (g->cost[i][j] > max)
            {
              max = g->cost[i][j];
              *imax = i;
              *jmax = j;
            }
        }

  return max;
}

int parcurgere(char **tabel, int n, char *cautat)
{
  int i;

  for (i = 0; i < n; i++)
    {
      if (strcmp(tabel[i], cautat) == 0)
        return i;
    }

  return -1;
}

int Total(Graph *g)
{
  int i, j, suma = 0;

  for (i = 0; i < g->N; i++)
    for (j = i; j < g->N; j++)
      suma += g->cost[i][j];

  return suma;
}

void printDrum(Graph *g, char **tabel, int *prev, int d, FILE *f)
{
  int i, drum[g->N], nr = 0;

  i = d;
  while (i != -1)
    {
      drum[nr] = i;
      nr++;
      i = prev[i];
    }

  for (i = nr - 1; i >= 0; i--)
    fprintf(f, "%s\n", tabel[drum[i]]);
}

int minDistance(int dist[], int sps[], int V)
{
  int v, min = INT_MAX, min_index;
  for (v = 0; v < V; v++)
    if (sps[v] == 0 && dist[v] < min)
      {
        min = dist[v];
        min_index = v;
      }

  return min_index;
}

void Dijkstra(Graph *g, int s, int **ppred, int **pdist)
{
  int i, j, u;
  int sps[g->N];

  int *dist = (int *)malloc(sizeof(int) * g->N);
  int *pred = (int *)malloc(sizeof(int) * g->N);

  for (i = 0; i < g->N; i++)
    {
      dist[i] = INT_MAX;
      sps[i] = 0;
      pred[i] = -1;
    }

  dist[s] = 0;

  for (j = 0; j < g->N - 1; j++)
    {
      u = minDistance(dist, sps, g->N);

      sps[u] = 1;

      for (i = 0; i < g->N; i++)
        if (sps[i] == 0 && g->cost[u][i] != 0 && dist[u] != INT_MAX && dist[u] + g->cost[u][i] < dist[i])
          {
            dist[i] = dist[u] + g->cost[u][i];
            pred[i] = u;
          }
    }

  *ppred = pred;
  *pdist = dist;
}

int maxDistance(int dist[], int V)
{
  int v, max = 0, max_index;
  for (v = 0; v < V; v++)
    if (dist[v] > max)
      {
        max = dist[v];
        max_index = v;
      }

  return max_index;
}

void FW(Graph *g, int ***pdist, int ***pnext)
{
  int **dist, **next, i, j, k, cost_nou;

  dist = (int **)malloc(sizeof(int *) * g->N);
  for (i = 0; i < g->N; i++)
    dist[i] = (int *)malloc(sizeof(int) * g->N);

  for (i = 0; i < g->N; i++)
    for (j = 0; j < g->N; j++)
      dist[i][j] = INT_MAX;

  next = (int **)malloc(sizeof(int *) * g->N);
  for (i = 0; i < g->N; i++)
    next[i] = (int *)malloc(sizeof(int) * g->N);

  for (i = 0; i < g->N; i++)
    dist[i][i] = 0;

  for (i = 0; i < g->N; i++)
    for (j = 0; j < g->N; j++)
      if (g->a[i][j])
        {
          dist[i][j] = g->cost[i][j];
          next[i][j] = j;
        }

  for (k = 0; k < g->N; k++)
    for (i = 0; i < g->N; i++)
      for (j = 0; j < g->N; j++)
        {
          if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
            {
              cost_nou = dist[i][k] + dist[k][j];
              if (cost_nou < dist[i][j])
                {
                  dist[i][j] = cost_nou;
                  next[i][j] = next[i][k];
                }
            }
        }

  *pdist = dist;
  *pnext = next;
}

void print_Max_dist(Graph *g, char **tabel, int **dist, FILE *f)
{
  int i, j, max = 0, maxi, maxj;

  for (i = 0; i < g->N; i++)
    for (j = 0; j < g->N; j++)
      {
        if (dist[i][j] > max)
          {
            maxi = i;
            maxj = j;
            max = dist[i][j];
          }
      }

  fprintf(f, "%dkm\n", dist[maxi][maxj]);
  i = maxi;

  fprintf(f, "%s %s\n", tabel[maxi], tabel[maxj]);
}

void print_path(int *path, int poz_path, char **table, FILE *f)
{
  int i;

  for (i = 0; i < poz_path; i++)
    {
      fprintf(f, "%s ", table[path[i]]);
    }

  fprintf(f, "\n");
}

void all_paths(Graph *g, int s, int d, char **table, int *visited, int *path, int poz_path, FILE *f, int *nr)
{
  int i;

  if (*nr == 100)
    return;

  if (s == d)
    {
      print_path(path, poz_path, table, f);
      (*nr)++;
      return;
    }

  visited[s] = 1;

  for (i = 0; i < g->N; i++)
    if (!visited[i] && g->a[i][s])
      {
        path[poz_path++] = i;
        all_paths(g, i, d, table, visited, path, poz_path, f, nr);
        poz_path--;
      }

  visited[s] = 0;
}

void print_all_paths(Graph *g, int s, int d, char **table, FILE *f)
{
  int path[g->N], visited[g->N], nr = 0;

  for (int i = 0; i < g->N; i++)
    visited[i] = 0;

  visited[s] = 1;
  path[0] = s;

  all_paths(g, s, d, table, visited, path, 1, f, &nr);
}
