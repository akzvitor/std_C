#include <stdio.h>

int main(){
    int n; //Casos de teste

    scanf("%d", &n);

    while(n > 0) 
    {
        int lines, i, j, hash = 0, ind;
        char string[51];

        scanf("%d", &lines);

        for(i = 0; i < lines; i++)  //Percorre os elementos
        {
            scanf("%s", string);

            for(j = 0; string[j] != '\0'; j++) //Percorre a string
            {
                ind = string[j] - 'A'; //Calcula a posição da letra no alfabeto 
                hash += ind + i + j; //Incrementa o valor do hash
            }
        }

        printf("%d\n", hash);
        n--;
    }

    return 0;
}