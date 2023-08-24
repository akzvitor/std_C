#include <stdio.h>
#include <stdlib.h>

#define MAX 100010

//Definição do struct que armazena informações sobre o dragão
typedef struct{
    int days, penalty, arrival;
    float value;
}Dragon;

//Definição do struct que representa a heap
typedef struct{
    Dragon *a[MAX];
    int n;
} Heap;

//Função que aloca memória e inicializa as variáveis
Dragon *createDragon(int d, int p, int a){
    Dragon *drag = (Dragon*)malloc(sizeof(Dragon));
    drag->days = d;
    drag->penalty = p;
    drag->arrival = a;
    drag->value = (float)p/(float)d;
    return drag;
}

//Função que aloca memória e cria a heap, além de inicializar o número de valores (n) 
Heap *createHeap(){
    Heap *h = (Heap*)malloc(sizeof(Heap));
    int i;
    /*for(i = 0; i < MAX; i++)
    {
    h->a[i] = createDragon(0,0);
    }*/
    h->n = 0;
    return h;
}

//Função que ajusta a heap após a inserção de um elemento
void reHeapUp(Heap *h, int i){
    Dragon *temp;
    while(i > 0 && h->a[i]->value > h->a[(i-1)/2]->value) //Compara o valor do elemento na posição i com o de seu pai e os troca se necessário
    {
        temp = h->a[i];
        h->a[i] = h->a[(i-1)/2];
        h->a[(i-1)/2] = temp;
        i = (i-1)/2;
    }
}

//Função que insere um dragão na heap
void insert(Heap *h, Dragon *d){
    h->a[h->n] = d;
    reHeapUp(h, h->n); //Chama a função de ajuste para cima
    h->n++; //Incrementa o número de elementos na heap
}

//Função que ajusta a heap após a remoção de um elemento
void reHeapDown(Heap *h, int i){
    Dragon *temp;
    int j;
    while(2*i+1 < h->n) //Compara o valor do elemento na posição i com o de seus filhos e os troca se necessário
    {
        j = 2*i+1;

        if(j+1 < h->n && h->a[j+1]->value > h->a[j]->value)
        {
            j++;
        }
        if(h->a[i]->value > h->a[j]->value)
        {
            break;
        }
        else
        {
            temp = h->a[i];
            h->a[i] = h->a[j];
            h->a[j] = temp;

            i = j;
        }
    }
}

//Função que remove o elemento de maior valor da heap
void removeMax(Heap *h){
    Dragon *temp;

    temp = h->a[0];
    h->a[0] = h->a[h->n-1];
    h->a[h->n-1] = temp;

    h->n--; //Decrementa o número de elementos

    reHeapDown(h, 0); //Chama a função de ajuste para baixo
}

//Imprime os valores da heap
void printHeap(Heap *h){
    int i;
    for(i = 0; i < h->n; i++)
    {
        printf("%f ", h->a[i]->value);
    }
    printf("\n");
}

int main(){
    Heap *priorityQueue = createHeap(); //Cria a heap

    long long int day = 0, time = 0;
    long long int totalPenalty = 0;
    long long int d, p;
    int i;

    while(scanf("%lld %lld", &d, &p) != EOF) //Lê as entradas
    {
        insert(priorityQueue, createDragon(d, p, day)); //Cria e insere cada dragão na heap

        if(time == 0) //Caso o tempo seja 0 remove o dragão de maior valor da heap e recalcula a multa
        {
            Dragon *dg = priorityQueue->a[0];
            removeMax(priorityQueue);
            totalPenalty += (day - dg->arrival) * dg->penalty;
            time = dg->days;
        }
        time--;
        day++;
    }

    while(priorityQueue->n != 0) //Processa os dragões restantes na heap
    {
        if(time == 0)
        {
            Dragon *dg = priorityQueue->a[0];
            removeMax(priorityQueue);
            totalPenalty += (day - dg->arrival) * dg->penalty;
            time = dg->days;
        }
        time--;
        day++;
    }

    printf("%lld\n", totalPenalty); //Imprime a multa total

    return 0;
}