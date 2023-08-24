#include <stdio.h>
#include <stdlib.h>

//Estrutura para representar o atendimento do funcionário
typedef struct {
    int employee;
    int serviceTime;
} Service;

//Estrutura para representar a heap
typedef struct {
    Service *services;
    int size;
} Heap;

//Função que cria e inicizliza a heap
//Recebe como parâmetro a capacidade da heap
Heap *createHeap(int capacity) {
    Heap *queue = (Heap*) malloc(sizeof(Heap));
    queue->size = 0;
    queue->services = (Service*) malloc(capacity * sizeof(Service));
    return queue;
}

//Função que exclui a heap, liberando a memória
//Recebe como parâmetro um ponteiro para a fila
void deleteHeap(Heap *queue) {
    free(queue->services);
    free(queue);
}

//Função auxiliar que troca dois atendimentos de posição
//Recebe como parâmetros o array de atendimentos e os índices dos atendimentos que vão ser trocados
void exchangeServices(Service *services, int i, int j) {
    Service aux = services[i];
    services[i] = services[j];
    services[j] = aux;
}

//Função que mantém a heap estruturada após inserir um elemento
//Recebe como parâmetros a fila e o índice do elemento inserido 
void reHeapUp(Heap *queue, int index) {
    int fatherNode = (index - 1) / 2;
    if (index > 0 && queue->services[index].serviceTime < queue->services[fatherNode].serviceTime) //Compara o tempo de atendimento do índice com o nó pai
    {
        exchangeServices(queue->services, index, fatherNode); //Troca os atendimentos de posição utilizando a função auxiliar
        reHeapUp(queue, fatherNode); //Chama a função recursivamente para continuar subindo na heap
    }
}

//Função que mantém a heap estruturada após remover um elemento
//Recebe como parâmetros a fila e o índice do elemento a ser removido
void reHeapDown(Heap *queue, int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int minor = index;
    if (leftChild < queue->size && queue->services[leftChild].serviceTime < queue->services[minor].serviceTime)
    {
        minor = leftChild;
    }
    if (rightChild < queue->size && queue->services[rightChild].serviceTime < queue->services[minor].serviceTime)
    {
        minor = rightChild;
    }
    if (minor != index)
    {
        exchangeServices(queue->services, index, minor);
        reHeapDown(queue, minor);
    }
}

//Função que insere um elemento na heap
//Recebe como parâmetros a fila, o número do funcionário e o tempo necessário para o atendimento
void insertOnHeap(Heap *queue, int employee, int serviceTime) {
    queue->services[queue->size].employee = employee;
    queue->services[queue->size].serviceTime = serviceTime;
    reHeapUp(queue, queue->size);
    queue->size++;
}


//Função que remove e retorna o atendimento mais rápido
Service removeMinimal(Heap *queue) {
    Service minimal = queue->services[0];
    queue->size--;
    queue->services[0] = queue->services[queue->size];
    reHeapDown(queue, 0);
    return minimal;
}

int main() {
    int N, M, totalTime = 0;
    scanf("%d %d", &N, &M); //Lê o número de funcionários e o número de atendimentos necessários (ou clientes)
    int *processingTimes = (int*) malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &processingTimes[i]); //Lê o tempo de processamento dos funcionários
    }

    Heap *queue = createHeap(N); //Cria a heap
    for (int i = 0; i < N; i++)
    {
        insertOnHeap(queue, i + 1, 0); //Insere os atendimentos na heapo
    }

    for (int i = 0; i < M; i++)
    {
        int items;
        scanf("%d", &items); //Lê a quantidade de itens/produtos 
        Service atendimento = removeMinimal(queue); //Remove o atendimento mais rápido (será colocado em uso)
        int employee = atendimento.employee; //Armazena os dados do atendimento mais rápido para serem usados
        int serviceTime = atendimento.serviceTime; //Armazena os dados do atendimento mais rápido para serem usados
        serviceTime += processingTimes[employee - 1] * items; //Calcula o tempo de atendimento
        insertOnHeap(queue, employee, serviceTime); //Insere o atendimento atualizado na heap novamente
        if (serviceTime > totalTime)
        {
            totalTime = serviceTime; //Atualiza o tempo total
        }
    }

    deleteHeap(queue);
    free(processingTimes);

    printf("%d\n", totalTime);

    return 0;
}