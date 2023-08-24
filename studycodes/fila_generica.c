#include <stdio.h>
#include <stdlib.h>

/*
yhll! Esse código, construído principalmente para fins de aprendizagem, consiste na criação de uma estrutura de dados do tipo FILA (FIFO - FIRST IN FIRST OUT) em linguagem C.
Por esse motivo, trata-se de uma fila genérica com os conceitos e as funcionalidades básicas dessa estrutura de dados. 
*/

//Definição do struct de nós da estrutura de dados FILA.
//Consiste em um valor qualquer e um ponteiro utilizado para apontar para o próximo nó.
typedef struct node{
    int value;
    struct node *next;
}Node;

//Função de inserção na fila, insere um elemento qualquer.
//Tem como parâmetros um ponteiro de ponteiro do tipo Node e um inteiro, este que será o elemento inserido.
void insertOnQueue (Node **queue, int num) {
    Node *aux, *new = malloc(sizeof(Node));  //Criação das varíaveis, uma auxiliar e uma que será o novo nó ou elemento da fila.
    if (new != NULL) 
    {
        new->value = num;  //Inicializa as variáveis de new, value recebe o elemento inserido.
        new->next = NULL;  //next recebe nulo, já que ainda não averá outro elemento.
        if (*queue == NULL)  
        {
            *queue = new;  //Cria um novo elemento caso a fila esteja vazia.
        }
        else
        {
            aux = *queue;
            while (aux->next != NULL)  //Percorre toda a fila.
            {
                aux = aux->next;
            }
            aux->next = new;  //Insere o elemento no final da fila.
        }
    }
    else
    {
        printf("\nErro ao alocar memoria.\n");
    }
}

//Função de remoção da fila, remove o elemtento escolhido.
//Tem como parâmetro apenas um ponteiro para ponteiro do tipo node, que será o elemento escolhido para a remoção.
Node *removeOfQueue (Node **queue) {
    Node *remove = NULL;  //Inicialização do ponteiro que será usado para remover o elemento.
    if (*queue != NULL)
    {
        remove = *queue;  //remove recebe o primeiro elemento da fila.
        *queue = remove->next; //Primeiro elemento da fila recebe next, ou seja, o segundo elemento da fila, que agora se torna o primeiro. O_o
    }
    else
    {
        printf("\tA fila não possui nenhum elemento.\n");
    }
    return remove;
}

//Função que imprime a fila na tela.
//Tem como parâmetro um ponteiro para a fila.
void printQueue(Node *queue) {
    printf("\t-------- FILA --------\n\t");
    while (queue != NULL)  //Enquanto o elemento for diferente de nulo, imprime os elementos da fila.
    {
        printf("%d ", queue->value);
        queue = queue->next;  //queue recebe o próximo elemento para que a fila seja percorrida.
    }
    printf("\n\t-------- FIM --------\n\n");
}

//Função principal que, além de apresentar um menu, utiliza todas as funcionalidades da fila.
int main() {
    Node *remove, *queue = NULL;
    int option, value;

    do
    {
        printf("\t0 - Sair\n\t1 - Inserir\n\t2 - Remover\n\t3 - Imprimir\n");
        scanf("%d", &option);

        switch(option)
        {
            case 1:
                printf("Digite um valor: ");
                scanf("%d", &value);
                insertOnQueue(&queue, value);
                break;
            case 2:
                remove = removeOfQueue(&queue);
                if (remove != NULL)
                {
                    printf("Elemento removido: %d\n", remove->value);
                    free(remove);
                }
                break;
            case 3:
                printQueue(queue);
                break;
            default:
                if (option != 0)
                {
                    printf("\nOpcao invalida!\n");
                }
        }
    } while (option != 0);
    
    return 0;
}