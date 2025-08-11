#include <stdio.h>

int main(){
    double zahl1;
    double zahl2;
    char operator;

    printf("Gebe eine Zahl ein: \n");
    scanf("%lf", &zahl1);
    printf("Gebe einen Operator ein: \n");
    scanf(" %c", &operator);
    printf("Gebe noch eine Zahl ein: \n");
    scanf("%lf", &zahl2);
    

    printf("\n\n");
    if(operator == '+'){
        printf("%lf + %lf = %lf", zahl1, zahl2, zahl1 + zahl2);
    }

    if(operator == '-'){
        printf("%lf - %lf = %lf", zahl1, zahl2, zahl1 - zahl2);
    }

    if(operator == '*'){
        printf("%lf * %lf = %lf", zahl1, zahl2, zahl1 * zahl2);
    }

    if(operator == '/'){
        printf("%lf / %lf = %lf", zahl1, zahl2, zahl1 / zahl2);
    }

    return 0;
}