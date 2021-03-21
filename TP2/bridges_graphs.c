/* Nome: Larissa Domingues Gomes
 * Matricula: 650525
 * Desafio encontrar pontes em grafos
 */

#include <stdio.h>
#include <stdlib.h>

int* visited;
int* low;
int* parent;

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


void dfsBridge(pGraph g, int u, int* time, int* visited, int* low, int* parent){
    visited[u] = (*time); // Vértice visitado pela primeira vez
    low[u] = (*time); // Vértice visitado pela primeira vez
    (*time) = (*time) + 1;

    // Repetição para visitar todos vizinhos de u
    for(pRelation r = g->relations[u]->next; r != NULL; r = r->next){
        
        if(visited[r->index] == 0){ // Se o vizinho não foi visitado ainda
            parent[r->index] = u; // Marcar u como parent
            dfsBridge(g, r->index, time, visited, low, parent); // Chamar recursiva

            // Após busca em profundidade em r->index
            // Se o tempo de descorberta mais baixo que r->index tem acesso for menor que o de u
            // atualizar low de u
            if(low[u] > low[r->index]) 
                low[u] = low[r->index];
            // Se o menor valor que r->index tem acesso for maior que o tempo de descoberta
            // de u, então não há outras formas de acessar os decedentes de r->index, logo
            // o vértice r->index - u é uma ponte
            if (low[r->index] > visited[u])  
                printf("Bridge %d -> %d\n", u, r->index); 
        }else{
            // Se o vizinho já foi acessado e não é parent de u
             if(r->index != parent[u])
                // Se o tempo mais baixo que r->index tem aceeso for menor que u, então 
                // há outros caminhos para acessar r->index
                if(low[u] > low[r->index])
                    low[u] = low[r->index];
        }
    }
}

void dfs_g(pGraph g, int init){
    int count = 1;
    int time = 1;

    visited = (int*) malloc(sizeof(int)*g->vertices);
    low = (int*) malloc(sizeof(int)*g->vertices);
    parent = (int*) malloc(sizeof(int)*g->vertices);
    
    for(int i = 0; i < g->vertices; i++){
        visited[i] = 0; // vértice não visitado
        low[i] = 0; // vértice não visitado
        parent[i] = -1; // parent invalido
    }

    for (int i = 0; i < g->vertices; i++) 
        if (visited[i] == 0) // Fazer busca em todos componentes
             dfsBridge(g, i, &time, visited, low, parent); 
        

}

int main(){
    pGraph graph = create_graph(4);
    create_relation(graph, 0, 2);
    create_relation(graph, 0, 1);
    create_relation(graph, 0, 3);
    create_relation(graph, 1, 3);
    show_graph(graph);
    dfs_g(graph, 1);
    return 0;
}


