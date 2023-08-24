#include <stdio.h>
int main(){

    char operator;
    int i, j;
    float matriz[12][12], amount=0, average=0;

    scanf("%c", &operator);
    for(i=0; i<=11; i++){

        for(j=0; j<=11; j++){
            scanf("%f", &matriz[i][j]);
            if(i > j){
                amount += matriz[i][j];
                average += matriz[i][j];
            }
        }

    }

    average = average/66;

    if(operator == 'S'){
        printf("%.2f\n", amount);
    }
    else if(operator == 'M'){
        printf("%.2f\n", average);
    }

return 0;
}