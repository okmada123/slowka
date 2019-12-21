#include <stdio.h>
#include <string.h>
#define DLZKA_SLOVA 10

int test = 1;

void perm(char fix[], char str[]) {
	if (strlen(str) == 2) {
		char slovo[DLZKA_SLOVA + 1];
		int i;
		for (i = 0; i < strlen(fix); i++)
			slovo[i] = fix[i];
		slovo[i + 2] = '\0';
		slovo[i] = str[0];
		slovo[i + 1] = str[1];
		printf("%d: %s\n", test++, slovo);
		slovo[i] = str[1];
		slovo[i + 1] = str[0];
		printf("%d: %s\n", test++, slovo);
		return;
	}
	else {
		int i;
		char novyfix[DLZKA_SLOVA + 1] = "";
		strcat(novyfix, fix);
		novyfix[strlen(novyfix) + 1] = '\0';
		novyfix[strlen(novyfix)] = '*';
		for (i = 0; i < strlen(str); i++) {
			novyfix[strlen(novyfix) - 1] = str[i];
			//printf("%s\n", novyfix); //toto vyzera ze funguje zatim
			char novystr[DLZKA_SLOVA + 1] = ""; //taky isty ako stary ale bez toho jednoho pismena
			strcat(novystr, str);
			for (int j = i; j < strlen(novystr); j++) {
				novystr[j] = novystr[j + 1];
			}
			perm(novyfix, novystr);
		}
		return;
	}
}

int main() {
	char str[DLZKA_SLOVA + 1], fix[DLZKA_SLOVA + 1] = "";
	//neviem jak dostat const. do toho scanf...
	printf("Zadaj pismena, z ktorych chces skladat permutacie (bez medzery): ");
	scanf("%10s", str);
	strupr(str);
	perm(fix, str);
	return 0;
}