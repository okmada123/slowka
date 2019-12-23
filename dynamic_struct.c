#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char meno[12];
	int vek;
} clovek;

int main() {
	clovek * adam = (clovek*)malloc(sizeof(clovek) * 100);

	adam[0].meno[0] = '\0';
	char test[] = "ADAM";
	strcpy(adam[0].meno, test);

	adam[10].meno[0] = '\0';
	char str[] = "BERENIK";
	strcpy(adam[10].meno, str);
	
	printf("%s\n", adam[0].meno);
	printf("%s\n", adam[10].meno);
	return 0;
}