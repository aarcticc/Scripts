#include <stdio.h>
#include "bookshelf.h"

int main(){
	start(mainMenu());

	return 0;
}

void mainMenu() {
	int menuSelection;

	printf("------------------------------\n");
	printf("------(0)-LIST-ALL-BOOKS------\n"); // sort authors in submenu
	printf("------(1)-DISPLAY-BOOK-COUNT--\n");
	printf("------(2)-ADD-BOOK------------\n");
	printf("------(3)-EXIT----------------\n");
	printf("------------------------------\n\n");

	printf("What do you want to do?: \n");
	scanf("%d", &menuSelection);

	switch(menuSelection) {
		case 0:
			listAllBooks();
			break;
		case 1:
			displayBookCount();
			break;
		case 2:
			addBook();
			break;
		case 3:
			exitProgram();
			break;

		default:
			printf("That is not an option\n");
			break;
	}
}


