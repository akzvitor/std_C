#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Struct para a definição das variáveis que serão usadas na árvore binária
typedef struct Node{
    char elements;
    struct Node *left, *right;
}Node;

//Função que cria os nós da árvore binária fazendIndexo a inicialização das variáveis
//Usada na função de construção da árvore para inicializar o novo nó
Node *createNode(char elements){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->elements = elements;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//Função que busca o índice de um elemento da árvore binária
//Tem como parâmetro a própria string, os índices de início e fim e o valor buscado (que é retornado seu índice)
int search(char string[], int startIndex, int endIndex, char value){
    int i;
    for(i = startIndex; i <= endIndex; i++)
    {
        if(string[i] == value)
        {
            return i;
        }
    }
    return -1;
}

//Função que cria a árvore e os nós(registra os elementos)
//Tem como parâmetro, além dos índices, as strings strPrefix e strInfix, que representam os percursos prefixo e infixo
//Retorna o novo nó que foi criado
Node *createTree(char infix[], char prefix[], int infixstartIndexIndex, int infixEndIndexIndex, int *prefixIndex){
    if(infixstartIndexIndex > infixEndIndexIndex)
    {
        return NULL;
    }
    Node *newNode = createNode(prefix[*prefixIndex]);
    (*prefixIndex)++;
    if(infixstartIndexIndex == infixEndIndexIndex)
    {
        return newNode;
    }
    int inIndex = search(infix, infixstartIndexIndex, infixEndIndexIndex, newNode->elements);
    newNode->left = createTree(infix, prefix, infixstartIndexIndex, inIndex - 1, prefixIndex);
    newNode->right = createTree(infix, prefix, inIndex + 1, infixEndIndexIndex, prefixIndex);
    return newNode;
}

//Função que percorre e imprime a árvore ne maneira posfixa
//Recebe a raiz como parâmetro
void postfix(Node *root){
    if (root == NULL)
    {
        return;
    }
    postfix(root->left);
    postfix(root->right);
    printf("%c", root->elements);
}

//Função principal
int main(void){
    int n;
    scanf("%d", &n);
    while (n--)
    {
        int numNodes;
        scanf("%d", &numNodes);
        char strPrefix[numNodes + 1], strInfix[numNodes + 1];
        scanf("%s %s", strPrefix, strInfix);
        Node *root = NULL;
        int prefixIndex = 0;
        root = createTree(strInfix, strPrefix, 0, numNodes - 1, &prefixIndex);
        postfix(root);
        printf("\n");
    }
    return 0;
}