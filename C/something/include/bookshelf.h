#include <stdio.h>
#include <stdbool.h>

#ifdef
#define BOOL YESNO


char bookshelf[100][256];

void listAllBooks(){

}

void displayBookCount(){

}

void addBook(){
	char bookName[256];
	char bookAuthor[100];
	char tempDecision;

	printf("What book should be addet?\n\n");

	printf("Name: \n");
	scanf("%s", &bookName);

	printf("Author: \n");
	scanf("%s", &bookAuthor);

	printf("Do you want to add: %s, %s. [TRUE/false]? ", bookName, bookAuthor);
	while (scanf("%c", &tempDecision) < 3){
		if (tempDecision == 2)
			displayBookCount();
		}
	} else {
		printf("This is not a valid input!");
		addBook();
	}
}

void exitProgram(){

}

#endif