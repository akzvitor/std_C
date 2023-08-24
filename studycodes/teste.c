#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

//Definição do struct que representa um nó da tabela hash
typedef struct node{
    struct node *next;
    int value;
} TNode;

//Definição do struct da tabela hash
typedef struct{
    TNode *start, *end;
} HashTable;

//Função responsável por inicializar a tabela hash
//Recebe um ponteiro que vai representar a tabela e um inteiro n que será o tamanho da tabela
void inicialize(HashTable *array, int n){
	int i;

	for(i=0; i<n; i++)
    {
		array[i].start = NULL;
		array[i].end = NULL;
	}
}

//Função responsável por inserir um valor na tabela hash
//Recebe um ponteiro que representa a tabela, o índice e o valor a ser inserido
void instertNode(HashTable *array, int ind, int e){
	TNode *aux = (TNode *)malloc(sizeof(TNode));
	aux->value = e;
	aux->next = NULL;

	if(array[ind].start == NULL) //Se não tiver elemento no início a tabela está vazia, então insere o novo elemento no início
    {
		array[ind].start = aux;
    }
	else //Caso contrário insere no final
    {
		array[ind].end->next = aux;
    }
	array[ind].end = aux;
}

//Função responsável por percorrer a lista e imprimir os nós
//Recebe o ponteiro de início e o índice da tabela hash
void print(TNode *start, int ind){
	TNode *aux = start;

	printf("%d -> ", ind);

	while(aux != NULL)
    {
		printf("%d -> ", aux->value);
		aux = aux->next;
	}		

	printf("\\");
	printf("\n");
}

int main(){
	HashTable array[MAX];
	int key, num, n, e, i, j;
	
	scanf("%d", &n);
	
	for(j=0; j<n; j++)
    {	
		scanf("%d %d", &key, &num);
		inicialize(array, key);
		
		for(i=0; i<num; i++)
        {
			scanf("%d", &e);
			instertNode(array, e % key, e);
		}
		for(i=0; i<key; i++)
        {
			print(array[i].start, i);	
        }
		if(j + 1 < n)
        {
			printf("\n");
        }
	}
	return 0;
}