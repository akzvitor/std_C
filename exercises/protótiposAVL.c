Node *newRoot(int x){
    Node *new = malloc(sizeof(Node));

    if(new)
    {
        new->CRM = x;
        new->left = NULL;
        new->right = NULL;
        new->height = 0;
    }
    else
    {
        printf("\nErro ao cadastrar!\n");
    }
    return new;
}

Node *register_doctor(Node *root, int x){
    if(root == NULL)
    {
        return newRoot(x);
    }
    else
    {
        if(x < root->CRM)
        {
            root->left = register_doctor(root->left, x);
        }
        else if(x > root->CRM)
        {
            root->left = register_doctor(root->right, x);
        }
        else
        {
            printf("\nRegistro não realizado! O Medico %d já está registrado!\n", x);
        }
    }
    //Ajusta a altura da árvore em relação aos novos elementos inseridos
    root->height = largest_value(node_height(root->left), node_height(root->right)) + 1;
    //Verifica se é necessário rebalancear a árvore e, caso seja, executa o balanceamento
    root = balancing(root);
    return root;
}

int tree_height(Node *root)
{
    if(root == NULL)
    {
        return -1;
    }
    else
    {
        int l = tree_height(root->left); //variável que recebe a altura da subárvore esquerda (l = left)
        int r = tree_height(root->right); //variável que recebe a altura da subárvore direita (r = right)
        if(l > r)
        {
            return l + 1;
        }
        else
        {
            return r + 1;
        }
    }
}