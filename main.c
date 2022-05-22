#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  FILE *f, *g;
  Graph *orientat = NULL, *neorientat = NULL;
  int n = 0, minim, maxim, imin, jmin, imax, jmax, total, *dist, *pred, id_B, id_F, **mdist, **mnext, id_O;
  char fisier[100], **tabel = NULL;
  f = fopen("_all_files.txt", "rt");

  orientat = create();
  neorientat = create();

  while (fgets(fisier, 100, f))
    {

      fisier[strlen(fisier) - 1] = 0;
      g = fopen(fisier, "rt");

      if (!g)
        exit(0);

      CitireFisier(g, orientat, neorientat, &tabel, &n);
      fclose(g);
    }

  fclose(f);
  f = fopen("min.txt", "wt");
  g = fopen("max.txt", "wt");

  minim = Min(neorientat, &imin, &jmin);

  fprintf(f, "%s-%s distanta %dkm\n", tabel[imin], tabel[jmin], minim);

  fclose(f);
  maxim = Max(neorientat, &imax, &jmax);
  fprintf(g, "%s-%s distanta %dkm\n", tabel[imax], tabel[jmax], maxim);
  fclose(g);

  f = fopen("total.txt", "wt");
  total = Total(neorientat);
  fprintf(f, "total: %d km\n", total);
  fclose(f);

  f = fopen("ruta.txt", "wt");

  id_B = parcurgere(tabel, neorientat->N, "Bucuresti Nord");
  id_F = parcurgere(tabel, neorientat->N, "Fagaras");

  Dijkstra(neorientat, id_B, &pred, &dist);

  fprintf(f, "%dkm\n", dist[id_F]);
  printDrum(neorientat, tabel, pred, id_F, f);
  fclose(f);

  f = fopen("departe.txt", "wt");

  int max = maxDistance(dist, neorientat->N);

  fprintf(f, "%d km\n", dist[max]);
  printDrum(neorientat, tabel, pred, max, f);

  fclose(f);

  f = fopen("drum_lung.txt", "wt");
  FW(neorientat, &mdist, &mnext);
  print_Max_dist(neorientat, tabel, mdist, f);

  fclose(f);

  f = fopen("bucuresti_oradea.txt", "wt");
  id_O = parcurgere(tabel, neorientat->N, "Oradea");
  print_all_paths(neorientat, id_B, id_O, tabel, f);

  fclose(f);

  return 0;
}
