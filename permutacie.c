#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DLZKA_SLOVA 10
int test = 1;

void perm(char fix[], char str[], char **pole_slov) {
	if (strlen(str) == 2) {
		char slovo[DLZKA_SLOVA + 1];
		int i,o;
		for (i = 0; i < strlen(fix); i++)
			slovo[i] = fix[i];
		slovo[i + 2] = '\0';
		slovo[i] = str[0];
		slovo[i + 1] = str[1];


		//start
		for (o = 0; o < strlen(slovo); o++) {
			pole_slov[test - 1][o] = slovo[o];
		}
		pole_slov[test - 1][o] = '\0';
		//printf("%s %d\n", pole_slov[test - 1],test-1);
		//end


		printf("%d: %s\n", test++, slovo);
		slovo[i] = str[1];
		slovo[i + 1] = str[0];


		//start
		for (o = 0; o < strlen(slovo); o++) {
			pole_slov[test - 1][o] = slovo[o];
		}
		pole_slov[test - 1][o] = '\0';
		//printf("%s %d\n", pole_slov[test - 1], test - 1);
		//end


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
			perm(novyfix, novystr,pole_slov);
		}
		return;
	}
}

int fact(int n) {
	if (n == 1) return 1;
	else {
		n *= fact(n - 1);
		return n;
	}
}

int chars_repeat(char *str) {
	int i, o; {
		for (i = 0; i < strlen(str)-1; i++) {
			for (o = i+1; o < strlen(str); o++) {
				//printf("i = %c, o = %c\n",str[i], str[o]);
				if (str[i] == str[o]) {
					return 1;
				}
			}
		}
	}
	return 0;
}



int main() {
	char str[DLZKA_SLOVA + 1], fix[DLZKA_SLOVA + 1] = "";
	//neviem jak dostat const. do toho scanf...
	printf("Zadaj pismena, z ktorych chces skladat permutacie (bez medzery): ");
	scanf("%10s", str);
	
	// start upravy
	int n = fact(strlen(str));

	char **pole_slov = (char**)calloc(n, sizeof(char*));					//alokovanie pamate ..
	int i;																	//..
	for (i = 0; i < n; i++) {
		pole_slov[i] = (char*)calloc((strlen(str) ),sizeof(char) );			//..pre 2D dynamicke pole
	}
	//end


	strupr(str);
	perm(fix, str,pole_slov);

	//start
	if (chars_repeat(str)) {
		printf("Opakuju sa\n");
	}

	for (i = 0; i < n; i++) {
		printf("%s\n",	pole_slov[i]);
	}

	free(pole_slov);
	//end
	
	return 0;
}