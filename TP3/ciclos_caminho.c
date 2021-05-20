/* Encontrar todos os ciclos de um grafo simples
 * Utilizando caminhamento 
 * Nome: Larissa Domingues Gomes
 * Matricula: 650525
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int* visited;
int* color;
int* path;
int* aux;


int comp = 0;
int atr;

typedef struct Relation*pRelation; 
typedef struct Relation Relation; 
struct Relation{
    int index;
    pRelation next;
}; 

typedef struct Graph*pGraph; 
typedef struct Graph Graph;
struct Graph{
    int edges;
    int vertices;
    pRelation* relations;
};

/* Creates a new graph of v vertices
 * @param int v
 * @return pGraph
 */
pGraph create_graph(int v) {
    pGraph g =(pGraph) malloc (sizeof(Graph));

    g->edges = 0;
    g->vertices = v;
    g->relations = (pRelation*) malloc (sizeof(pRelation)*v);
    
    for(int i =0; i < v; i++){
        g->relations[i] = (pRelation) malloc(sizeof(Relation)); //Head
    }
    
    return g;
}

/* Creates a new relation
 * @param int index
 * @return pRelation
 */
pRelation new_relation(int index){  
    pRelation new = (pRelation) malloc(sizeof(Relation));
    new->index = index;
    new->next = NULL;
    return new;
}



/* Creates a link v1 - v2
 * @param pGraph pg, int v1, int v2
 * @return 0 -> failed
           1 -> succeed
 */
int create_relation(pGraph pg, int v1, int v2) {
    pRelation a = pg->relations[v1];
    for (; a != NULL; a = a->next) ;
     

    // adding edge
    a = pg->relations[v1]->next;
    pg->relations[v1]->next = new_relation(v2);
    pg->relations[v1]->next->next = a;
   
    a = pg->relations[v2]->next;
    pg->relations[v2]->next = new_relation(v1);
    pg->relations[v2]->next->next = a;

    pg->edges++;
    
    return 1;
}

void show_graph (pGraph graph){
    printf("\n=-=-=-=-= Graph =-=-=-=-=\n");
    printf("\nVertices: %d\n", graph->vertices);
    printf("Edges: %d\n\n", graph->edges);
    
    
    for(int i = 0; i < graph->vertices; i++){
        printf("V%d ", i);
        for(pRelation r = graph->relations[i]->next; r != NULL; r = r->next)
            printf("-> %d ", r->index );

        printf("\n");
    }
    
}

void enumarate_rec(pGraph g, int u, int parent, int* visited, int* path, int n){
    visited[u] = 1;
    path[n] = u; // adicionar vértice à pilha de caminho
     atr+=2;
    for(pRelation r = g->relations[u]->next; r != NULL; r = r->next ){
        comp++;
        comp++;
        if(visited[r->index] == 0){
            enumarate_rec(g, r->index, u, visited, path, n+1);
            visited[r->index] = 0; // Vétice pode estar presente em outros ciclos
            atr++;
        }
        else{ 
            comp++;
            if(r->index != parent  && r->index == path[0]){ // Se voltar para vértice inicial, encontrou um ciclo
                for(int i = 0; i <= n; i++){
                    comp++;
                    printf("%i ", path[i]);
                }
                comp++;
                printf("%i \n", r->index);
            }
        }
        
    }
    comp++;
}

/* Calls enumarate_rec
 * @param  pGraph g
 */
void enumarate_cycles(pGraph g){
    visited = (int*)malloc(sizeof(int) * g->vertices);
    path = (int*)malloc(sizeof(int) * g->vertices);

    int i = 0;

    for (int i = 0; i < g->vertices; i++){
        comp++;
        visited[i] = 0; 
        path[i] = -1;
        atr+=2; 
    }
    comp++;

    for (int i = 0; i < g->vertices; i++) {
        comp++;
        enumarate_rec(g, i, -1, visited, path, 0); 
        for (int i = 0; i < g->vertices; i++){ // Começar busca do zero para cada vértice
            comp++;
            visited[i] = 0; 
            atr++;
        }
        comp++;
    }
    comp++;

}

int main(){
    pGraph graph = create_graph(3);
    create_relation(graph, 0, 1);
    create_relation(graph, 1, 2);
    create_relation(graph, 2, 0);
    show_graph(graph);

    comp = 0;
    atr = 0;
    clock_t t1 = clock();
    enumarate_cycles(graph);
    clock_t t2 = clock();
    printf("TEMPO: %li %li\nCOMPARACOES: %i\nATRIBUICOES: %i \n", (t2), t1, comp, atr);
    return 0;
}


