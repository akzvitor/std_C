#include <stdio.h>
#include <stdlib.h>

#define MAX 55

int tests, node, vertices, lines, vist[MAX], time;

//Definição da struct que armazenará o array e seu tamanho
typedef struct {
    int data[MAX];
    int size;
} Vector;

//Função que adiciona um elemento ao final do vetor
void pushBack(Vector *vertices, int x) {
    vertices->data[vertices->size] = x;
    vertices->size++;
}

Vector graph[MAX];

//Função bfs (busca de profundidade) que recebe um vértice x como parâmetro
int dfs(int x) {
    vist[x] = time;  //Marca x como visitado
    int vVertices = 1;  //Variável que controla o número de vértices visitados

    for (int i = 0; i < graph[x].size; i++) //Itera sobre os vértices adjacentes
    {
        int vertices = graph[x].data[i];
        if (vist[vertices] == time) continue;
        vVertices += dfs(vertices) + 1; //Chama a função dfs recursivamente caso não tenham sido visitados
    }

    return vVertices;
}

int main() {
    scanf("%d", &tests);
    time = 1;

    while (tests--)
    {
        scanf("%d %d %d", &node, &vertices, &lines);

        for (int i = 0; i < lines; i++)  //Preenche o grafo com as linhas (arestas)
        {
            int x, y;
            scanf("%d %d", &x, &y);

            pushBack(&graph[x], y);  //Coloca y como adjacente de x
            pushBack(&graph[y], x);  //Coloca x como adjacente de y
        }

        printf("%d\n", dfs(node) - 1);
        time++;

        for (int i = 0; i < vertices; i++)
        {
            graph[i].size = 0;
        }
    }

    return 0;
}