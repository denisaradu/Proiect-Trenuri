# Proiect-Trenuri
Acest proiect are ca scop prelucrarea unor fisiere text cu informatie despre toate statiile de tren din Romania si utilizarea mai multor algoritmi asupra grafurilor, precum Dijkstra sau Floyd-Warshall in C.

Initial, am citit datele din arhiva.
Am creat un graf neorientat si altul orientat din fisierele atasate. Am creat si matricea de adiancenta si separat graful de costuri.
Ulterior, am lucrat doar cu graful neorientat.

Am gasit statiile consecutive care au distanta minima/maxima intre ele si am inregistrat cele doua rezultate in fisierele min.txt si max.txt.

In fisierul total.txt, am aflat cati km de cale ferata exista in baza de date.

Am calculat drumul de cost minim de la Bucuresti la Fagaras, orasul meu natal, si am salvat rezultatele in fisierul ruta.txt.

Am gasit statia cea mai departe de Bucuresti si drumul, rezultatele aflandu-se in fisierul departe.txt.

Am gasit toate drumurile de la Bucuresti la Oradea, in fisierul bucuresti_oradea.txt. (Cum erau foarte multe, m-am limitat afisarea la doar cateva).

In final, am gasit cele doua statii din graf care sunt la distanta maxima (pe drumul de cost minim) si am pastrat rezultatul in fișierul drum_lung.txt.
