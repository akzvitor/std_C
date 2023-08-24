#include <stdio.h>
#include <stdlib.h>

//Definição do struct que representa a estrutura de dados
typedef struct dataStructure{
    struct structure *ip; //Ponteiro utilizado para implementar a heap
    struct structure *in; //Ponteiro utilizado para implementar a fila
    int top; //Variável que representa o topo da pilha
    int *p; //Ponteiro utilizado para implementar a pilha 
}dataStructure;

//Definição da struct auxiliar usada na heap e na fila
typedef struct structure{
    int n;
    struct structure *next; //Ponteiro que aponta para o próximo elemento da estrutura
}structure;

int stack, queue, priorityQueue;

//Função que aloca memória para a estrutura utilizada
dataStructure *allocateStructure(){
	dataStructure *aux;

	aux = (dataStructure*)malloc(sizeof(dataStructure));
	aux->ip = NULL;
	aux->in = NULL;
	aux->top = 0;
	aux->p = NULL;

	return aux;
}

//Função que insere um elemento na estrutura
void insert(dataStructure *edx, int n){	
	structure *ep, *en, *aux, *ant;
	int first=1; //Variável usada para controlar se o novo nó é o primeiro da lista

	if(priorityQueue == 1) //Se a variável global de heap for igual a 1, ep é alocado em ip
	{
		ep = (structure*)malloc(sizeof(structure));
		ep->n = n;
		ep->next = NULL;

		if(edx->ip == NULL)
		{
			edx->ip = ep;
		}
		else 
		{
			aux = edx->ip;

			while(aux != NULL)
			{
				if(ep->n > aux->n)
				{ 
					break;
				}
				first=0;
				ant = aux;
				aux = aux->next;
			}

			if(first == 1)
			{
				ant = edx->ip;
				edx->ip = ep;
				ep->next = ant;
			} 
			else 
			{
				ant->next = ep;
				ep->next = aux;
			}
		}
	}

	if(queue == 1) //Se a variável global de fila for igual a 1, en é alocado em in
	{
		en = (structure*)malloc(sizeof(structure));
		en->n = n;
		en->next = NULL;

		if(edx->in == NULL)
		{ 
		edx->in = en;
		}
		else 
		{
			aux = edx->in;

			while(aux->next != NULL)
			{ 
				aux = aux->next;
			}
			aux->next = en;
		}
	}

	if(stack == 1) ////Se a variável global de pilha for igual a 1, o valor do elemento é adicionado em p
	{
		if(edx->top == 0)
		{ 
			edx->p = (int*)malloc(sizeof(int));
		}
		else
		{ 
			edx->p = (int*)realloc(edx->p ,sizeof(int)*(edx->top+1));
		}
		edx->p[edx->top] = n;
		edx->top++;
	}
}

//Função usada para remover um elemento da estrutura
void delete(dataStructure *edx, int n){
	structure *aux;

	if(edx->p != NULL && stack != 0) //Se p for diferente de nulo e a variável global de pilha estiver ativa remove elemento da pilha 
	{
		if(edx->p[edx->top-1] == n)
		{
			edx->p = (int*)realloc(edx->p, sizeof(int)*(edx->top-1));
			edx->top--;
		} 
		else
		{ 
			stack = 0;
		}
	}

	if(edx->ip != NULL && priorityQueue != 0) //Se ip for diferente de nulo e a variável global de heap estiver ativa remove elemento da heap
	{
		aux = edx->ip;

		if(aux->n == n)
		{
			aux = aux->next;
			free(edx->ip);
			edx->ip = aux;
		} 
		else 
		{
			priorityQueue = 0;
		}
	}

	if(edx->in != NULL && queue != 0) //Se in for diferente de nulo e a variável global de fila estiver ativa remove elemento da fila
	{
		aux = edx->in;

		if(aux->n == n)
		{
			aux = aux->next;
			free(edx->in);
			edx->in = aux;
		} 
		else
		{ 
			queue = 0;
		}
	}
}

int main(){
    dataStructure *edx;
    int qttOp, i, opType, n; 

    while(scanf("%d", &qttOp) == 1)
	{
    	stack=1;
    	queue=1;
    	priorityQueue=1;

    	edx = allocateStructure();

		for(i=0; i<qttOp; i++)
		{
			scanf("%d %d", &opType, &n);
			if(opType == 1) insert(edx, n);
			else delete(edx, n);
		}

		if(stack == 1 && priorityQueue == 1 || priorityQueue == 1 && queue == 1 || stack == 1 && queue == 1)
		{
			printf("not sure\n");
		}
		else if(priorityQueue)
		{
			printf("priority queue\n");
		}
		else if(queue)
		{
			printf("queue\n");
		}
		else if(stack)
		{ 
			printf("stack\n");
		}
		else 
		{
			printf("impossible\n");
		}
		free(edx);
	}
	return 0;
}