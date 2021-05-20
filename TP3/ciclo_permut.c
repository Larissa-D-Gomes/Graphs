/* Encontrar todos os ciclos de um grafo simples
 * Utilizando permutação de vértices
 * Nome: Larissa Domingues Gomes
 * Matricula: 650525
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
int comp = 0;
int atr = 0;

struct Graph{
    int vertices;
    int edges;
    int** adjacency_matrix;
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
       
    return pg;
}

/* Creates a link v1 -> v2
 * @param pGraph pg, int v1, int v2
 * @return 0 -> failed
           1 -> succeed
 */
int create_relation(pGraph pg, int v1, int v2){
    if(v1 >= 0 && v1 < pg->vertices && v2 >= 0 && v2 < pg->vertices && pg->adjacency_matrix[v1][v2] == 0){
        pg->adjacency_matrix[v1][v2] = 1;
        pg->adjacency_matrix[v2][v1] = 1;
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
        pg->adjacency_matrix[v2][v1] = 0;
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
        printf("v%d | ", i);
    }
    
    printf("\n");
    
    for(int i = 0; i < pg->vertices; i++){
        printf("v%d | ", i);
        for(int j =0; j < pg->vertices; j++){
            printf(" %d | ",pg->adjacency_matrix[i][j]);
        }
        printf("\n");
    }
    
    printf("\n");
}

void print_cycle(int* v, int n){
    for(int i = 0; i < n; i++)
        printf("%i ", v[i]);
    
    printf("%i \n", v[0]);

}

/* Checks if a path exists 
 * @param int* v, int n, pGraph graph
 * @return bool -> 1 the path exists 
                -> 0 the path does not exist
 */
bool check_path(int* v, int n, pGraph graph){
    int i;
    for( i = 0; i < n-1; i++){
        comp++;
        if(graph->adjacency_matrix[v[i]][v[i+1]] != 1){
            comp++;
            return false;
        }
    }
    comp++;
    comp++;
    if(graph->adjacency_matrix[v[i]][v[0]] != 1)
            return false;
    return true;
}

/* Enumerates all cycles by permutation
 * @param int* v, int* permutation, int n, int p, pGraph graph
 */
void permutation_rec(int* v, int* permutation, int n, int p, pGraph graph){
    // Teste a partir do momento que vertor permutation tem 
    // 3 elementos
    comp++;
    if(p > 2 && check_path(permutation, p, graph))
       print_cycle(permutation, p);

    comp++;
    if(p < n){
        for(int i = 0; i < n; i++){
            comp++;
            bool achou = 0;
            atr++;
            for(int j = 0; j < p; j++){
                comp++;
                if(permutation[j] == v[i]){
                    atr++;
                    achou = 1;
                }
            }
            
            if(!achou){
                atr++;
                permutation[p] = v[i];
                permutation_rec(v, permutation, n, p+1, graph); 
            }

        }
        comp++;
    } 
        

}

/* Enumerates all cycles by permutation
 * @param  pGraph graph
 */
void enumerate_cycles(pGraph graph){
    printf("=-=-=-= CYCLES =-=-=-=\n\n");

    int* v = (int*)malloc(sizeof(int) * graph->vertices);
    atr++;

    for(int i = 0; i < graph->vertices; i++){
        comp++;
        atr++;
        v[i] = i;
    }
    comp++;

    int* permutation = (int*)malloc(sizeof(int) * graph->vertices);
    permutation_rec(v, permutation, graph->vertices, 0, graph);
}
 

int main(){
    
    pGraph graph = init(3);
    create_relation(graph, 0, 1);
    create_relation(graph, 1, 2);
    create_relation(graph, 2, 0);
    

    print_graph(graph);
    comp = 0;
    clock_t t1 = clock();

    enumerate_cycles(graph);
    clock_t t2 = clock();
    printf("TEMPO: %li %li\nCOMPARACOES: %i\nATRIBUICOES: %i\n", (t2), t1, comp, atr);
    return 0;
}


