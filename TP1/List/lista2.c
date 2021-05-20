#include <stdio.h>
#include <stdlib.h>

/**
Grafo não direcionado não ponderado utilizando estrutura 
de lista de lista.

V1 -> v3,v4,v6
V2 -> v4
V3 -> v1, v6,
V4 -> v1,v2
V5 -> v6
V6 -> v1,v2,v5
**/

typedef struct {
    int index;
    int* data;
} Relation;

typedef Relation*pRelation; 

////////////////////////////////////////////

typedef struct {
    int edges;
    int vertices;
    pRelation* relations;
} Graph;

typedef Graph*pGraph; 

///////////////////////////////////////////////////

pRelation create_relation(int num_vertices, int index) {
    pRelation r = (pRelation) malloc (sizeof(Relation));
    
    r->index = index;
    
    r->data = (int*) malloc(sizeof(int)*num_vertices);
    
    //Preenchendo com -1 pois ainda não possui nenhuma relacao
    for(int i = 0; i < num_vertices; i++) {
        r->data[i] = -1;
    }
    
    return r;
}


void show_edge(pRelation r) {
    printf("V%d ->", r->index);
    
    int i = 0;
    while(i < (sizeof(r->data)) && r->data[i] != -1){
        printf(" V%d", r->data[i]);
        i++;
    }
    printf("\n");
}

//////////////////////////////////////////////////

pGraph create_graph(int v, int e) {
    int index = -1;

    pGraph g =(pGraph) malloc (sizeof(Graph));

    g->edges = e;
    g->vertices = v;
    g->relations = (pRelation*) malloc (sizeof (pRelation)*v);
    
    //Alocando espaco para cada relation
    for(int i =0; i < v; i++){
              g->relations[i] = create_relation(v, i);
    }
    
    return g;
}

void liberar_dados (pGraph g)
{
  if (g!=NULL)
  {
      for(int i = 0;i < g->vertices; i++ )
      {
         free(g->relations[i]->data);
         free(g->relations[i]);
      }
      
      free (g->relations);
      free (g);
  }
} 

void show_graph (pGraph graph){
    int vertice = -1;
    printf("Total Vertices: %d\n", graph->vertices);
    printf("Total Edges: %d\n", graph->edges);
    
    
    for(int i = 0; i < graph->vertices; i++){
        show_edge(graph->relations[i]);
    }
    
    printf("\n");
}


int main(int argc, char const *argv[]) {
    int num_vertices = 3;
    int num_edges = 3;

    pGraph g = create_graph(num_vertices, num_edges);
    
    //Para testar o show_graph com um grafo de 3 vertices completo
    g->relations[0]->data[0] = 1;
    g->relations[0]->data[1] = 2;
    g->relations[1]->data[0] = 0;
    g->relations[1]->data[1] = 2;
    g->relations[2]->data[0] = 0;
    g->relations[2]->data[1] = 1;
    
    
    
    show_graph(g);   
    liberar_dados(g);
}