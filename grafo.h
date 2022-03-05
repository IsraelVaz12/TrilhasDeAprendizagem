#define grauZero 0 //vamos definir aqui as cores apenas para fim ditaticos
#define grauUm 1
#define grauDois 2

struct adjacencia{
    int vertice;
    int peso;
    struct adjacencia *prox;
};
typedef struct adjacencia adjacencia;

struct vertice{
    adjacencia *head;
};
typedef struct vertice vertice;

struct Grafo{
    int arestas;
    int vertices;
    vertice *adj;
};
typedef struct Grafo Grafo;


Grafo *grafo_create(int v){
    Grafo *g;
    g = malloc(sizeof(Grafo));

    //g->recurso = rec;
    g->vertices = v;
    g->arestas = 0;
    g->adj = malloc(sizeof(vertice));

    for(int i=0; i<v; i++){
        g->adj[i].head = NULL;
    }

    return g;
}

adjacencia *criaAdj(int v, int peso){
    adjacencia *aux;
    aux = malloc(sizeof(adjacencia));

    aux->vertice = v;
    aux->peso = peso;
    aux->prox = NULL;
    
    return aux;
}


int addAresta(Grafo *g, int vi, int vf, int p){
    if(g == NULL)
        return 0;
    if((vf < 0 ) || (vf >= g->vertices))
        return 0;
    if((vi < 0) || (vf >= g->vertices))
        return 0;

    adjacencia *novo = criaAdj(vf, p);

    novo->prox = g->adj[vi].head;
    g->adj[vi].head = novo;
    g->arestas++;

    return 1;
}

void imprime(Grafo *g){
    printf("Vertices: %d. Arestas: %d. \n",g->vertices,g->arestas); 

    for(int i=0; i<g->vertices; i++){
        printf("v%d: ", i);
        adjacencia *aux = g->adj[i].head;

            while(aux){
                printf("v%d(%d) ",aux->vertice,aux->peso); 
                aux = aux->prox;
            }
            printf("\n");
    }
}

void maiorGrau(Grafo *g){

    int qtd=0, maior=0, maiorV=0;
    for(int i=0; i<g->vertices; i++){
        adjacencia *aux = g->adj[i].head;
        while(aux){
            aux = aux->prox;
            qtd++;
        }

        if(maior < qtd){
            maior = qtd;
            maiorV = i;
        }
        qtd=0;
    }

    printf("Vertice com mais adjacencias: v%d\n", maiorV);
}

int removeAresta(Grafo *g,int vi, int vf){
    if(g == NULL)
        return 0;
    if((vf < 0 ) || (vf >= g->vertices))
        return 0;
    if((vi < 0) || (vf >= g->vertices))
        return 0;

    adjacencia *aux = g->adj[vi].head, *aux2, *aux3 = g->adj[vi].head;
    int cont=1;
    
    while(aux){
        if(aux->vertice == vf){
            if(aux->prox != NULL){
                aux2 = g->adj[vi].head->prox->prox;         //aux2 = null
                g->adj[vi].head = g->adj[vi].head->prox;    //head = segundo
                g->adj[vi].head->prox = aux2;               // 
                g->arestas--;
    
                 if(cont == 1){
                    return 1;
                }break;

            } else{
                    if(cont == 1){
                        g->adj[vi].head = g->adj[vi].head->prox;
                        g->arestas--;
                        return 1;
                    }
                    g->adj[vi].head = g->adj[vi].head->prox;
                    g->arestas--;
                    break;
                }
        }
        cont++;
        aux = aux->prox;
        g->adj[vi].head = g->adj[vi].head->prox;
    }

    if(cont == 2){
        aux3->prox = NULL;
        g->adj[vi].head = aux3;
    }
    g->adj[vi].head = aux3;
    return 0;
}

int removeVertice(Grafo *g, int vi){
    if(g == NULL){
        return 0;
    }
    if(vi < 0)
        return 0;

    g->adj[vi].head = NULL;
    //g->adj[vi] = NULL;

    return 1;
}

void liberaGrafo(Grafo *g){
    free(g);
}

int procuraMenorDistancia (int *dist, int *visitado, int NV) {

	int i, menor = -1, primeiro = 1;
	for(i = 0; i < NV; i++) {
		if(dist[i] >= 0 && visitado[i] == 0) {
		if(primeiro) {
			menor = i;
			primeiro = 0;
		} else{
			if(dist[menor] > dist[i])
				menor = i;
		}
	}
}
    return menor;
}



void menorCaminho_Grafo (Grafo *gr, int ini, int *ant, int *dist) {
	int i, cont, NV, ind, *visitidao, u;
	cont= NV = gr->nro+vertices;
	visitado = (int*) malloc(NV * sizeof(int));

	for(i=0; i < NV; i++) {
	    ant[1] = -1;
	    dist[i] = -1;
	    visitado[i] = 0;
    }   

    dist[ini] = 0;
    while(cont > 0){
	    u = procuraMenorDistancia(dist, visitado, NV);
	    if (u == -1)
		    break;
	    visitado[u] = 1;
	    cont--;
	}

	free(visitado);
    ind = gr->arestas[u][i];
	if(dist[ind] < 0) {
		dist[ind] = dist[u] + 1;
		ant[ind] = u;
    }else {
	if(dist[ind] > dist[u] + 1) {
		dist[ind] = dist[u] + 1;
		ant[ind] = u;
	}
}


void profundidade (Grafo *g){
	int cor[g->vertices];//crio um vetor com arranjo de cores (o valor tem que bater com o do grafo)
	
	int u;
	for(u=0;u<g->vertices;u++){ //inicialmente todos vérties são brancos
		cor[u] = grauZero;
	}

	for(u=0;u<g->vertices;u++){
		if (cor[u] == grauZero) // se for branco visita todos em profundida
		visitaP(g,u,cor); // repare que é recursivo, visita até o final depois volta 	
	}	
}

void visitaP(Grafo *g, int u, int *cor){
	cor[u] = grauUm; //visitar um nó marca como amarelo
	adjacencia *v = g->adj[u].head; //visito adjacencia

	while (v){ //então visitamos sua adjacencia, aresta u e v recursivamente
		if(cor[v->vertice]==grauZero) //se a cor for branco eu visito
		visitaP(g,v->vertice,cor); //veja que visito chamando a função de novo, ou seja recursivo
		v = v->prox;
	}

	cor[u] = grauDois;
}

