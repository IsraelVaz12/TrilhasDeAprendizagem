#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

int main()
{
	
	Grafo *gr = grafo_create(5);
	addAresta(gr, 0, 1, 2);
	addAresta(gr, 1, 2, 4);
	addAresta(gr, 2, 0, 12);
	addAresta(gr, 2, 4, 40);
	addAresta(gr, 3, 1, 3);
	addAresta(gr, 4, 3, 8);
    
    imprime(gr);
    maiorGrau(gr);
    int r = removeAresta(gr,0,1);
    int r2 = removeAresta(gr,3,1);
    //int r3 = removeVertice(gr, 2);
    imprime(gr);
    printf("%d", r2);
    //printf("%d", r3);
    
    return 0;
}