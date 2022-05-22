#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Graph Graph;
struct Graph
{
  int N, M, **a, **cost;
};

Graph *create();
void CitireFisier(FILE *f, Graph *orientat, Graph *neorientat, char ***tabel, int *n);
int Min(Graph *g, int *imin, int *jmin);
int parcurgere(char **tabel, int n, char *cautat);
int Max(Graph *g, int *imax, int *jmax);
int Total(Graph *g);
void Dijkstra(Graph *g, int s, int **ppred, int **pdist);
void printDrum(Graph *g, char **tabel, int *prev, int d, FILE *f);
int maxDistance(int dist[], int V);
void print_Max_dist(Graph *g, char **tabel, int **dist, FILE *f);
void FW(Graph *g, int ***pdist, int ***pnext);
void print_all_paths(Graph *g, int s, int d, char **table, FILE *f);
void all_paths(Graph *g, int s, int d, char **table, int *visited, int *path, int poz_path, FILE *f, int *nr);