/* Grafo direcionado ponderado implementado por matriz
 * Grupo: Larissa Gomes e Tarcila Fernanda 
 * Disciplina: Algoritmos em Grafos 
 * PUC-MG - Ciência da Computação - Manhã
 */
#include <stdio.h>
#include <stdlib.h>

struct Graph{
    int vertices;
    int edges;
    int** adjacency_matrix;
    int** values;
};
typedef struct Graph * pGraph; 

/* Creates a graph of ver vertices
 * @param int ver
 * @return pGraph
 */
pGraph init(int ver){
    pGraph pg = (pGraph)malloc(sizeof(pGraph));
    pg->vertices = ver;
    pg->edges = 0;

    // Creating the adjacency matrix...
    pg->adjacency_matrix = (int**)malloc(sizeof(int*)*ver);
    for(int i = 0; i < ver; i++){
        pg->adjacency_matrix[i] = (int*)malloc(sizeof(int)*ver);

        for(int j = 0; j < ver; j++){
            pg->adjacency_matrix[i][j] = 0;
        }
    }

    // Creating the values matrix...
    pg->values = (int**)malloc(sizeof(int*)*ver);
    for(int i = 0; i < ver; i++){
        pg->values[i] = (int*)malloc(sizeof(int)*ver);

        for(int j = 0; j < ver; j++){
            pg->values[i][j] = 0;
        }
    }
      
       
    return pg;
}

/* Creates a link v1 -> v2
 * @param pGraph pg, int v1, int v2
 * @return 0 -> failed
           1 -> succeed
 */
int new_link(pGraph pg, int v1, int v2, int value){
    if(v1 >= 0 && v1 < pg->vertices && v2 >= 0 && v2 < pg->vertices && pg->adjacency_matrix[v1][v2] == 0){
        pg->adjacency_matrix[v1][v2] = 1;
        pg->values[v1][v2] = value;
        pg->edges++;
        return 1;
    }
    return 0;
}

/* Removes a link v1 -> v2
 * @param pGraph pg, int v1, int v2
 * @return 0 -> failed
           1 -> succeed
 */
int remove_link(pGraph pg, int v1, int v2){
    if(v1 >= 0 && v1 < pg->vertices && v2 >= 0 && v2 < pg->vertices && pg->adjacency_matrix[v1][v2] == 1){
        pg->adjacency_matrix[v1][v2] = 0;
        pg->values[v1][v2] = 0;
        pg->edges--;
        return 1;
    }
    return 0;
}

void print_graph(pGraph pg) {
    printf("\n=-=-=-=-= Adjacency Matrix =-=-=-=-=\n");
    printf("\nVertices: %d\n", pg->vertices);
    printf("Edges: %d\n", pg->edges);
    printf("\n     ");
    
    for(int i = 0; i < pg->vertices; i++){
        printf("v%d     | ", i);
    }
    
    printf("\n");
    
    for(int i = 0; i < pg->vertices; i++){
        printf("v%d | ", i);
        for(int j =0; j < pg->vertices; j++){
            printf(" %d [%d] | ",pg->adjacency_matrix[i][j], pg->values[i][j]);
        }
        printf("\n");
    }
    
    printf("\n");
}

int main(){
    pGraph G = init(5);
    new_link(G, 0, 0, 3);
    new_link(G, 0, 2, 4);
    new_link(G, 4, 4, 5);
    print_graph(G);

    remove_link(G, 4, 4);
    print_graph(G);

}
