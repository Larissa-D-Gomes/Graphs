/* Grafo não direcionado ponderado utilizando estrutura lista encadeada
 * Grupo: Larissa Gomes e Tarcila Fernanda
 * Disciplina: Algoritmos em Grafos 
 * PUC-MG - Ciência da Computação - Manhã
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Relation*pRelation; 
typedef struct Relation Relation; 
struct Relation{
    int index;
    int value;
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
pRelation new_relation(int index, int value){  
    pRelation new = (pRelation) malloc(sizeof(Relation));
    new->index = index;
    new->next = NULL;
    new->value = value;
    return new;
}


/* Creates a link v1 - v2
 * @param pGraph pg, int v1, int v2
 * @return 0 -> failed
           1 -> succeed
 */
int create_relation(pGraph pg, int v1, int v2, int value) {
    pRelation a = pg->relations[v1];
    for (; a != NULL; a = a->next) 
      if (a->index == v2) return 0;

    // adding edge
    a = pg->relations[v1]->next;
    pg->relations[v1]->next = new_relation(v2, value);
    pg->relations[v1]->next->next = a;
   
    a = pg->relations[v2]->next;
    pg->relations[v2]->next = new_relation(v1, value);
    pg->relations[v2]->next->next = a;

    pg->edges++;
    
    return 1;
}

/* Removes a link v1 - v2
 * @param pGraph pg, int v1, int v2
 * @return 0 -> failed
           1 -> succeed
 */
int remove_relation(pGraph pg, int v1, int v2) {
    pRelation a;
    for (a = pg->relations[v1]; a->next != NULL && a->next->index != v2; a = a->next);
    
    if(a->next == NULL)
        return 0;

    // removing edge
    pRelation aux = a->next;
    a->next = a->next->next;
    free(aux);

    for (a = pg->relations[v2]; a->next != NULL && a->next->index != v1; a = a->next);
   
    // removing edge
    aux = a->next;
    a->next = a->next->next;
    free(aux);

    pg->edges--;
    
    return 1;
}

void show_graph (pGraph graph){
    printf("\n=-=-=-=-= Graph =-=-=-=-=\n");
    printf("\nVertices: %d\n", graph->vertices);
    printf("Edges: %d\n\n", graph->edges);
    
    
    for(int i = 0; i < graph->vertices; i++){
        printf("V%d ", i);
        for(pRelation r = graph->relations[i]->next; r != NULL; r = r->next)
            printf("-> %d [%d]", r->index, r->value );

        printf("\n");
    }
    
}

int main(){
    pGraph graph = create_graph(5);
    printf("%d\n", create_relation(graph, 1, 2, 10));
    printf("%d\n", create_relation(graph, 2, 1, 11));
    printf("%d\n", create_relation(graph, 1, 3, 25));
    printf("%d\n", create_relation(graph, 0, 3, 42));
    show_graph(graph);
    printf("%d\n", remove_relation(graph, 0, 3));
    show_graph(graph);
    return 0;
}


