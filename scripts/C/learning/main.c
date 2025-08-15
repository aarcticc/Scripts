#include "stdio.h"

// menu with seletcion

int showMenu(){
	int selection;

	printf("###### Welcome ######\n");
	printf("#### (0) Menu #1 ####\n");
	printf("#### (1) Menu #2 ####\n");
	scanf("%d", &selection);
	
	if(selection == 0 || selection == 1){
		return selection;
	} else {
		printf("Eingabe Ungültig!\n");
		return showMenu();
	}
}

int main(){
	showMenu();
	
	return 0;
}