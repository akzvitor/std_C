#include <stdio.h>

#define MAX_BANKS 100000

//Array onde serão armazenados os bancos
int parent[MAX_BANKS + 1];

//Função que inicializa o array de bancos 
//Recebe o numero de bancos como parâmetro
void initialize(int n){
    for(int i = 1; i <= n; i++)
    {
        parent[i] = i; //Cada banco é seu próprio pai no início
    }
}

//Função Find
//Recebe um elemento qualquer (x) como parâmetro
//Retorna o representante do conjunto que contém x (raiz da estrutura)
int find(int x){
    if(parent[x] != x) 
    {
        parent[x] = find(parent[x]);
    }
    return parent[x]; //Caso o pai de x seja o próprio x, retorna ele mesmo
}

//Função Union
//Recebe dois elementos como parâmetros e une seus respectivos conjuntos
void unionSets(int x, int y){
    int rootX = find(x); //Encontra o representante do conjunto o qual o elemento x pertence
    int rootY = find(y); //Encontra o representante do conjunto o qual o elemento y pertence
    parent[rootX] = rootY; //Representante do conjunto de x passa a ser o representante do conjunto de y
}

int main(){
    int n, i;

    scanf("%d %d", &n, &i);
    initialize(n);
    while(i--)
    {
        char op;
        int x, y;

        scanf(" %c %d %d", &op, &x, &y);
        if(op == 'F')
        {
            unionSets(x, y);
        } 
        else if(op == 'C')
        {
            if(find(x) == find(y))
            {
                printf("S\n");
            } else
            {
                printf("N\n");
            }
        }
    }
    return 0;
}
