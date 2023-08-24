#include <stdio.h>
#include <stdlib.h>

//Definição do struct que representa a guilda
typedef struct{
    int parent;
    int rank;
    int points;
} Guild;

//Função Find
//Recebe o índice de um jogador e um ponteiro que será o array de guilds
//Retorna o índice do representante da guilda ao qual o jogador x pertence
int find(int x, Guild *guilds){
    if(x != guilds[x].parent) //Se x não for o elemento pai da guilda busca este elemento de forma recursiva
    {
        guilds[x].parent = find(guilds[x].parent, guilds);
    }
    return guilds[x].parent;
}

//Função Union
//Recebe os índices de dois jogadores e o array de guilds
void unionSets(int x, int y, Guild *guilds){
    int rootX = find(x, guilds); //Encontra o representante da guilda do jogador x
    int rootY = find(y, guilds); //Encontra o representante da guilda do jogador y
    
    if(rootX != rootY) //Caso o representante da guilda do jogador x seja diferente do representante da guilda do jogador y, realiza a união
    {
        if(guilds[rootX].rank < guilds[rootY].rank) //Caso o rank da guilda de x for menor que o rank da guilda de y, y se torna pai de x
        {
            guilds[rootX].parent = rootY; //Representante de y passa a ser representante de x também
            guilds[rootY].points += guilds[rootX].points; //Calcula a pontuação da nova guilda 
        } 
        else if(guilds[rootX].rank > guilds[rootY].rank) //Caso o rank da guilda de y for menor que o rank da guilda de x, x se torna pai de y
        {
            guilds[rootY].parent = rootX; //Representante de x passa a ser representante de y também
            guilds[rootX].points += guilds[rootY].points; //Calcula a pontuação da nova guilda
        } 
        else //Caso os ranks sejam iguais não importa quem será pai de quem
        {
            guilds[rootY].parent = rootX;
            guilds[rootX].rank++;
            guilds[rootX].points += guilds[rootY].points;
        }
    }
}

int main(){
    int players, actions;
    
    while(scanf("%d %d", &players, &actions) == 2 && players != 0 && actions != 0) 
    {
        Guild *guilds = (Guild*)malloc((players + 1) * sizeof(Guild)); //Aloca memória para o array de guilds
        
        for(int i = 1; i <= players; i++)  //Inicializa o array e as variáveis
        {
            scanf("%d", &guilds[i].points);
            guilds[i].parent = i;
            guilds[i].rank = 0;
        }
        
        int wonBattles = 0;
        
        for(int i = 0; i < actions; i++)
        {
            int op, playerA, playerB;
            scanf("%d %d %d", &op, &playerA, &playerB);
            
            if(op == 1) //Se a operação for 1 realiza a união das guildas dos jogadores A e B
            {
                unionSets(playerA, playerB, guilds);
            } 
            else if (op == 2) //Se a operação for 2 acontece uma batalha entre as guildas dos jogadores A e B
            {
                int rootA = find(playerA, guilds);
                int rootB = find(playerB, guilds);
                
                if(rootA == 1 && guilds[rootA].points > guilds[rootB].points)
                {
                    wonBattles++;
                }
                else if(rootB == 1 && guilds[rootB].points > guilds[rootA].points)
                {
                    wonBattles++;
                }
            }
        }
        printf("%d\n", wonBattles);
        free(guilds);
    }
    return 0;
}