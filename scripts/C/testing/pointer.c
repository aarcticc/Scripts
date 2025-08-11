#include <stdio.h>

int main(){
	int myAge = 16;
	int* ptr = &myAge;
	printf("%d\n", myAge);
	printf("%d\n", *"0x7ffcea6e8cac");
	
	return 0;
}
