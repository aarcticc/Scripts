#include <stdio.h>

void startMenu(){
    int selection;

    printf("(0) Start Calculator\n");
    printf("(1) Show Calc History\n");
    printf("(2) Exit Calculator\n");
    scanf(" %d", &selection);
}

// count newline for asking if a new operator is needet
void countNumber(){
    int c, nl;

	nl = 0;
	while ((c = getchar()) != EOF)
		if (c == '\n')
			++nl;
}