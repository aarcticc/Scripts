#include <stdio.h>

int main(){
    char* anrede[256];
    int anhaenge = 2;

    scanf("%s[256]", &anrede);
    	 
    printf("%s\n\n", anrede);
    printf("Hier sind die Unterlagen:\n\n");

    printf("Anhänge: %d", anhaenge);
    
    return 0;
}
