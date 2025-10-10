#include <stdio.h>
#include "bookshelf.h"

int main() {
	char bookshelf [100][256];
	start(mainMenu());

	return 0;
}

void start(int nextIndex /*to be declared*/, char ) {
	switch(mainMenu) {
		case 0:
			listAllBooks();
			break;
		case 1:
			break;
			bookCount();
		case 2:
			break;
			addBook();
		default:
			printf("ERROR"); // maybe change		
	}
}

void mainMenu() {
	int selection;

	printf("------------------------------\n");
	printf("------(0)-LIST-ALL-BOOKS------\n"); // sort authors in submenu
	printf("------(1)-DISPLAY-BOOK-COUNT--\n");
	printf("------(2)-ADD-BOOK------------\n");
	printf("------(3)-EXIT----------------\n");
	printf("------------------------------\n\n");

	printf("What do you want to do?: \n");
	scanf("%d", &selection);
	printf("\n\n");
	if(selection == 0 || selection == 1 || selection == 2) {
		return selection;
	} else {
		printf("This is not a valid option!\n");
		return mainMenu();
	}
}
