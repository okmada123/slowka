#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DLZKA_SLOVA 7
int test = 1;

typedef struct {
	char slovo[15];
	int hodnota;
} struktura_slov;

void perm(char fix[], char str[], char **pole_slov) {
	if (strlen(str) == 2) {
		char slovo[DLZKA_SLOVA + 1];
		unsigned int i,o;
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

		test++;
		//printf("%d: %s\n", test++, slovo);
		slovo[i] = str[1];
		slovo[i + 1] = str[0];


		//start
		for (o = 0; o < strlen(slovo); o++) {
			pole_slov[test - 1][o] = slovo[o];
		}
		pole_slov[test - 1][o] = '\0';
		//printf("%s %d\n", pole_slov[test - 1], test - 1);
		//end

		test++;
		//printf("%d: %s\n", test++, slovo);

		return;
	}
	else {
		unsigned int i;
		char novyfix[DLZKA_SLOVA + 1] = "";
		strcat(novyfix, fix);
		novyfix[strlen(novyfix) + 1] = '\0';
		novyfix[strlen(novyfix)] = '*';
		for (i = 0; i < strlen(str); i++) {
			novyfix[strlen(novyfix) - 1] = str[i];
			//printf("%s\n", novyfix); //toto vyzera ze funguje zatim
			char novystr[DLZKA_SLOVA + 1] = ""; //taky isty ako stary ale bez toho jednoho pismena
			strcat(novystr, str);
			for (unsigned int j = i; j < strlen(novystr); j++) {
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
	unsigned int i, o; {
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

int vymaz_opakovane(char** pole_slov, int n) {
	int i,o, pocet_zmazanych = 0;
	
	for (i = 0; i < n-1; i++) {
		for (o = i+1; o < n; o++) {

			if (!strcmp(pole_slov[i], pole_slov[o]) && pole_slov[i][0] != '*') {
				//printf("Zhoda %s%d = %s%d \n",pole_slov[i],i+1,pole_slov[o],o+1);

				pole_slov[o][0] = '*';
				pocet_zmazanych++;
			}
		}

	}
		
		
	/*for (i = 0, o = 0; i < n; i++) {
		if (pole_slov[i][0] != '*') {
			strcat(pole_slovNEW[o++], pole_slov[i]);
		}
	}*/
	//printf("return z funkcie: %d\n", n - pocet_zmazanych);
	return n - pocet_zmazanych;
}

void napln_nove(char** pole_slov, char** pole_slovNEW, int n) {
	int o = 0;
	for (int i = 0; i < n; i++) {
		if (pole_slov[i][0] != '*') {
			strcat(pole_slovNEW[o++], pole_slov[i]);
		}
	}
}

void ziskaj_hodnoty(int abc[]) {
	FILE* fr;
	int i, value;
	char pismeno, eoln;

	fr = fopen("hodnoty.txt", "r");
	while (fscanf(fr, "%c%d%c", &pismeno, &value, &eoln) >= 2) {
		i = (int)pismeno - 'A';
		(int) abc[i] = value;
	}
	fclose(fr);
}

int legit_slova_counter(unsigned int str_len) {
	FILE* fr;
	int pocet_legit_slov = 0;
	char pomocny_string[25];
	pomocny_string[0] = '\0';

	fr = fopen("list.txt", "r");
	while (fscanf(fr, "%s", pomocny_string) == 1) {
		if (strlen(pomocny_string) <= str_len)
			pocet_legit_slov++;
	}
	fclose(fr);
	return pocet_legit_slov;
}

void nacitaj_legit_slova(char **pole_slovLEGIT,unsigned int str_len) {
	FILE* fr;
	int i = 0;
	char pomocny_string[25];
	pomocny_string[0] = '\0';

	fr = fopen("list.txt", "r");
	while (fscanf(fr, "%s", pomocny_string) == 1) {
		if (strlen(pomocny_string) <= str_len)
			strcpy(pole_slovLEGIT[i++], pomocny_string);
	}
	fclose(fr);
}

int zisti_hodnotu_slova(char **pole_slovLEGIT,int abc[], int i) {
	unsigned int u,value = 0;

	for (u = 0; u < strlen(pole_slovLEGIT[i]); u++) {
		value += abc[pole_slovLEGIT[i][u] - 'A'];
	}
	if (strlen(pole_slovLEGIT[i]) >= 7)
		value += 50;
	return value;
}

int zisti_pocet_struktur(int pocet_legit_slov, int  velkost_novehoP, char **pole_slovLEGIT, char** pole_slovNEW) {
	int i, o, pocet_struktur = 0;
	for (i = 0; i < pocet_legit_slov; i++) {
		for ( o = 0; o < velkost_novehoP; o++) {
			if (strlen(pole_slovLEGIT[i]) > 2 && strstr(pole_slovNEW[o], pole_slovLEGIT[i]) != NULL && pole_slovLEGIT[i][0] != '\0') {
				pocet_struktur++;
				pole_slovLEGIT[i][0] = '\0';
			}
		}
	}

	return pocet_struktur;
}


int main() {
	char str[DLZKA_SLOVA + 1], fix[DLZKA_SLOVA + 1] = "";
	
	printf("Zadaj pismena, ktore mas (bez medzery): ");
	scanf("%7s", str);

	int i,n = fact(strlen(str));
	
	char **pole_slov = (char**)calloc(n, sizeof(char*));					//alokovanie pamate ..
	for (i = 0; i < n; i++) {
		pole_slov[i] = (char*)calloc((strlen(str) ),sizeof(char) );			//..pre 2D dynamicke pole
	}

	strupr(str);
	perm(fix, str,pole_slov);

	int velkost_novehoP;
	if (chars_repeat(str)) {
		velkost_novehoP = vymaz_opakovane(pole_slov, n);
	}
	else
		velkost_novehoP = n;

	char** pole_slovNEW = (char**)calloc(velkost_novehoP, sizeof(char*));	//alokovat nove pole
	for (i = 0; i < velkost_novehoP; i++) {
		pole_slovNEW[i] = (char*)calloc((strlen(str)), sizeof(char));		//2D - druhy rozmer
		pole_slovNEW[i][0] = '\0';											//mmmmmmmmmmmmmmmmmmmmmmm
	}

	napln_nove(pole_slov, pole_slovNEW, n);
	free(pole_slov);

	int pocet_legit_slov = legit_slova_counter(strlen(str));					//
	char** pole_slovLEGIT = (char**)calloc(pocet_legit_slov, sizeof(char*));	//
	for (i = 0; i < pocet_legit_slov; i++) {
		pole_slovLEGIT[i] = (char*)calloc(strlen(str) + 1, sizeof(char));		//
		pole_slovLEGIT[i][0] = '\0';
	}
	nacitaj_legit_slova(pole_slovLEGIT,strlen(str));							//
	
	int pocet_struktur = zisti_pocet_struktur(	pocet_legit_slov,	//keby sa dalo pole poslat ako kopia, nemuseli by sa nacitavaz znovu legit slova
												velkost_novehoP, 
												pole_slovLEGIT, 
												pole_slovNEW);
	
	nacitaj_legit_slova(pole_slovLEGIT, strlen(str)); //sprav nieco, aby sa nemuselo druhy krat nacitavat legit pole

	struktura_slov* slovo = (struktura_slov*)malloc(sizeof(struktura_slov) * pocet_struktur);
	
	int index = 0;
	int abc[26];

	ziskaj_hodnoty(abc);

	for (i = 0; i < pocet_legit_slov; i++) {
		for (int o = 0; o < velkost_novehoP; o++) {
			if (strlen(pole_slovLEGIT[i]) > 2 && strstr(pole_slovNEW[o], pole_slovLEGIT[i]) != NULL && pole_slovLEGIT[i][0] != '\0') {

				slovo[index].slovo[0] = '\0';
				strcpy(slovo[index].slovo, pole_slovLEGIT[i]);
				slovo[index].hodnota = zisti_hodnotu_slova(pole_slovLEGIT, abc, i);
				pole_slovLEGIT[i][0] = '\0';
				index++;
			}
		}
	}

	for (i = 0; i < pocet_struktur; i++) {
		printf("%s %d\n", slovo[i].slovo, slovo[i].hodnota);
		if (strlen(slovo[i].slovo) >= 7)
			printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	}

	free(pole_slovNEW);	
	return 0;
}

