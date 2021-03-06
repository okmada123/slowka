#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DLZKA_SLOVA 8
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

		for (o = 0; o < strlen(slovo); o++) {
			pole_slov[test - 1][o] = slovo[o];
		}
		pole_slov[test - 1][o] = '\0';

		test++;

		slovo[i] = str[1];
		slovo[i + 1] = str[0];

		for (o = 0; o < strlen(slovo); o++) {
			pole_slov[test - 1][o] = slovo[o];
		}
		pole_slov[test - 1][o] = '\0';

		test++;

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
void nacitavanie_percent(int n, int i) {
	int percento = (n / 99) > 0 ? n / 99 : 1;

	if ((i % percento == 0) && n > 100)
		printf("#");
	else if (n < 100) {
		percento = 1 * 100 / n;
		for (int o = 0; o < percento; o++) {
			printf("#");
		}
	}
}

int vymaz_opakovane(char** pole_slov, int n) {	//aj toto trva dlho
	int i, o, pocet_zmazanych = 0;
	
	for (i = 0; i < n-1; i++) {
		nacitavanie_percent(n, i);

		for (o = i+1; o < n; o++) {

			if (!strcmp(pole_slov[i], pole_slov[o]) && pole_slov[i][0] != '*') {
				//printf("Zhoda %s%d = %s%d \n",pole_slov[i],i+1,pole_slov[o],o+1);

				pole_slov[o][0] = '*';
				pocet_zmazanych++;
			}
		}
	}
	printf("\n");
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

int zisti_pocet_struktur(int pocet_legit_slov, int  velkost_novehoP, char **pole_slovLEGIT, char** pole_slovNEW, int zaciatocny_index_pismena[]) {
	//TOTO TRVA DLHO !!!!	

	int i, o, pocet_struktur = 0;
	
	for (i = 0; i < velkost_novehoP; i++) {		//prechadza permutacie
		int zaciatok, koniec;
		char prve_pismeno_slova = pole_slovNEW[i][0];

		
		nacitavanie_percent(velkost_novehoP, i);

		zaciatok = zaciatocny_index_pismena[prve_pismeno_slova - 'A'];
		if (prve_pismeno_slova != 'Z') {
			koniec = zaciatocny_index_pismena[prve_pismeno_slova + 1 - 'A'];
		}
		else
			koniec = pocet_legit_slov;

		for (int o = zaciatok; o < koniec; o++) {		//tu musi byt optimalizovany cyklus - zaujima ma zaciatocne pismeno permutacie
			if (strlen(pole_slovLEGIT[o]) > 2 && strstr(pole_slovNEW[i], pole_slovLEGIT[o]) != NULL && pole_slovLEGIT[o][0] != '\0') {		
				pole_slovLEGIT[o][0] = '\0';

				pocet_struktur++;
			}
		}
	}
	printf("\n");
	return pocet_struktur;
}





int main() {
	char str[DLZKA_SLOVA + 1], fix[DLZKA_SLOVA + 1] = "";
	
	printf("Zadaj pismena, ktore mas (bez medzery): ");
	scanf("%8s", str);

	int i,n = fact(strlen(str));
	
	char **pole_slov = (char**)calloc(n, sizeof(char*));					//alokovanie pamate ..
	for (i = 0; i < n; i++) {
		pole_slov[i] = (char*)calloc((strlen(str) ),sizeof(char) );			//..pre 2D dynamicke pole
	}
	printf("\n");
	for (i = 1; i <= 100; i++) {
		if (i % 10 == 0)
			printf("%%");
		else
			printf(".");
	}
	

	strupr(str);
	printf("\nVytvaram permutacie...\n");
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

	//vypis vsetkych permutacii, kontrola
	/*for (i = 0; i < velkost_novehoP; i++)
		printf("%s\n", pole_slovNEW[i]);*/

	printf("Nacitavam slova zo slovnika...\n");
	int pocet_legit_slov = legit_slova_counter(strlen(str));					//
	char** pole_slovLEGIT = (char**)calloc(pocet_legit_slov, sizeof(char*));	//
	for (i = 0; i < pocet_legit_slov; i++) {
		pole_slovLEGIT[i] = (char*)calloc(strlen(str) + 1, sizeof(char));		//
		pole_slovLEGIT[i][0] = '\0';
	}
	nacitaj_legit_slova(pole_slovLEGIT,strlen(str));							//
	
	//zistenie, na akych indexoch zacinaju ktore pismena v poli legit slov:
	int index = 0;
	int zaciatocny_index_pismena[26];
	zaciatocny_index_pismena[index++] = 0;
	char hladame = 'B';
	for (i = 0; i < pocet_legit_slov; i++) {
		if (pole_slovLEGIT[i][0] == hladame) {
			zaciatocny_index_pismena[index++] = i;
			hladame++;
		}
	}
	/*for (i = 0; i < 26; i++)
		printf("%s\n", pole_slovLEGIT[zaciatocny_index_pismena[i]]);*/

	int pocet_struktur = zisti_pocet_struktur(	pocet_legit_slov,	//keby sa dalo pole poslat ako kopia, nemuseli by sa nacitavaz znovu legit slova
												velkost_novehoP,	//TOTO TRVA DLHO ALE UZ VYBAVENE
												pole_slovLEGIT, 
												pole_slovNEW,
												zaciatocny_index_pismena);
	nacitaj_legit_slova(pole_slovLEGIT, strlen(str)); //sprav nieco, aby sa nemuselo druhy krat nacitavat legit pole

	struktura_slov* slovo = (struktura_slov*)malloc(sizeof(struktura_slov) * pocet_struktur);
	
	int abc[26];


	ziskaj_hodnoty(abc); //iba nacita za kolko je ake pismeno bodov
	//TOTO TRVA DLHO !!!!!!!!!
	printf("Hladam slova...\n");

	index = 0;
	//iny sposob hladania slov:
	for (i = 0; i < velkost_novehoP; i++) {		//prechadza permutacie
		//int nejake_cislo = pole_slovNEW[i][0] - 'A';
		//printf("nejakecislo: %d\n", nejake_cislo);
		int zaciatok, koniec;
		char prve_pismeno_slova = pole_slovNEW[i][0];
		
		nacitavanie_percent(velkost_novehoP, i);

		zaciatok = zaciatocny_index_pismena[prve_pismeno_slova - 'A'];
		if (prve_pismeno_slova != 'Z') {
			koniec = zaciatocny_index_pismena[prve_pismeno_slova + 1 - 'A'];
		}
		else
			koniec = pocet_legit_slov;

		for (int o = zaciatok; o < koniec; o++) {		//tu musi byt optimalizovany cyklus - zaujima ma zaciatocne pismeno permutacie
			if (strlen(pole_slovLEGIT[o]) > 2 && strstr(pole_slovNEW[i], pole_slovLEGIT[o]) != NULL && pole_slovLEGIT[o][0] != '\0') {
				slovo[index].slovo[0] = '\0';
				strcpy(slovo[index].slovo, pole_slovLEGIT[o]);
				slovo[index].hodnota = zisti_hodnotu_slova(pole_slovLEGIT, abc, o);
				pole_slovLEGIT[o][0] = '\0';
				index++;
			}
		}
	}

	printf("\nZoradujem slova...\n");
	//zoradenie struktur:
	//pocet_struktur = pocet slov, ktore sa budu vypisovat a teda aj pocet slov, ktore treba zoradit
	for (int o = 0; o < pocet_struktur; o++) {
		for (i = 0; i < pocet_struktur - 1; i++) {
			if (slovo[i].hodnota < slovo[i + 1].hodnota) {
				//vymena tych dvoch medzi sebou
				int pom = slovo[i].hodnota;
				char pom_string[15];
				strcpy(pom_string, slovo[i].slovo);
				slovo[i].hodnota = slovo[i + 1].hodnota;
				slovo[i].slovo[0] = '\0';
				strcpy(slovo[i].slovo, slovo[i + 1].slovo);
				slovo[i + 1].hodnota = pom;
				slovo[i + 1].slovo[0] = '\0';
				strcpy(slovo[i + 1].slovo, pom_string);
			}
		}
	}


	//vypis slov
	printf("\nVyhovujuce slova: (%d)\n", pocet_struktur);
	for (i = 0; i < pocet_struktur; i++) {
		printf("%s %d\n", slovo[i].slovo, slovo[i].hodnota);
	}

	free(pole_slovNEW);	
	return 0;
}

