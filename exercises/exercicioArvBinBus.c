#include <stdio.h>
#include <stdlib.h>

//Struct para definição das variáveis usadas na árvore binária de busca
typedef struct Node{
    int elements;
    struct Node *left, *right;
}Node;

//Função que cria e inicializa novos nós
Node *createNode(int elements){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->elements = elements;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//Função que adiciona nós à árvore binária de busca
Node *addNode(Node *root, int key){
    if (root == NULL)
    {
        return createNode(key);
    }
    if(key < root->elements)
    {
        root->left = addNode(root->left, key);
    }
    else
    {
        root->right = addNode(root->right, key);
    }
    return root;
}

//Função que percorre e imprime os elementos da árvore fazendo o percurso prefixo
void prefix(Node *root){
    if(root == NULL)
    {
        return;
    }
    printf("%d ", root->elements);
    prefix(root->left);
    prefix(root->right);
}

//Função que percorre e imprime os elementos da árvore fazendo o percurso infixo
void infix(Node *root){
    if (root == NULL)
    {
        return;
    }
    infix(root->left);
    printf("%d ", root->elements);
    infix(root->right);
}

//Função que percorre e imprime os elementos da árvore fazendo o percurso posfixo
void postfix(Node *root){
    if (root == NULL)
    {
        return;
    }
    postfix(root->left);
    postfix(root->right);
    printf("%d ", root->elements);
}

//Função principal
int main(void){
    int n, i, j, numElements, elements;
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &numElements);
        Node *root = NULL;
        for (j = 0; j < numElements; j++)
        {
            scanf("%d", &elements);
            root = addNode(root, elements);
        }
        printf("Case %d:\n", i);
        printf("Pre.: ");
        prefix(root);
        printf("\n");
        printf("In..: ");
        infix(root);
        printf("\n");
        printf("Post: ");
        postfix(root);
        printf("\n");
    }
    return 0;
}