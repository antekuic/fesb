#define _CRT_SECURE_NO_WARNINGS

/*
MAIN HEAD -> HEAD1 -> HEAD2 -> .... (head)
				|		|
			 lista1	  lista2 ..... (Polinom)

*/

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

typedef struct _Polinom* PolPok;

typedef struct _Polinom {
	int broj; // ->koeficijent
	int eksponent; // -> eksponent
	PolPok next;
	PolPok next_array;
} Polinom;



PolPok loadingData(); // SORTIRANO UCITAVANJE IZ DATOTEKE -> VRACA ADRESU MAIN HEADA
PolPok createPolynomList(char *); // VRACA ADRESU HEAD CLANA
int addPolynom(PolPok, int []);
PolPok ZbrojiPolinome(PolPok); // VRACA ADRESU HEADA OD REZULTATA ZBRAJANJA
int Ispis(PolPok);

int main() {
	PolPok c = NULL, rez_z = NULL;
	int ind = 0, opcija = 0;
	printf("Unesite opciju: \n"
		"1- Ucitavanje iz datoteke\n2 - Mnozenje polinoma\n3 - Zbrajanje polinoma\n4 - Ispis trenutni\n"
	"Opcija: ");
	while (!ind) {
		scanf(" %d", &opcija);
		switch (opcija) {
		case 1: // ASCII 1
			c = loadingData();
			if (c != NULL) {
				printf("Polinomi ucitani iz datoteke.");
			}
			break;
		case 3: 

			// DODATI I BRISANJE rez_z ovdje
			if ((rez_z = ZbrojiPolinome(c)) != NULL) {
				printf("Polinomi uspjesno zbrojeni");
			}
			else {
				printf("Dogodila se greska");
			}
			break;
		case 4: 
			if (Ispis(c) == -1) {
				printf("Nema se sto ispisati");
			}
			break;
		default:
			printf("Nepostojeca opcija.");
			ind = 1;
			break;
		}

		printf("\nUnesite opciju: ");
	}

	system("pause");
	return 0;
}

PolPok loadingData() {

	FILE *f = NULL;
	PolPok main = NULL;
	PolPok heads = NULL;
	PolPok pom = NULL;
	int brojac = 0;
	char text[BUFFER_SIZE];
	
	main = (PolPok)malloc(sizeof(Polinom));
	main->next_array = NULL;

	if (main != NULL) {
		f = fopen("polinomi.txt", "r");
		if (f != NULL)
		{
			while (fgets(text, BUFFER_SIZE, f) != NULL) {
				heads = createPolynomList(text);
				pom = main->next_array;
				main->next_array = heads;
				heads->next_array = pom;
				brojac++;
			}
		}

		fclose(f);
	}

	if (!brojac) { // UKOLIKO SE NISTA NIJE DOGODILO OCISTI MEMORIJU
		free(main);
	}

	return main;
}

PolPok createPolynomList(char *buffer) { /* OBLIK PRIMJERA 22x^3 */

	PolPok main = NULL; // -> MAIN HEAD ZA LISTU
	int temp[3] = { 0, 0, 1 }; // 0 -> broj 1 -> exp 2->predznak
	int mod = 0; // 0 -> brojevi 1 -> exponent
	int ind = 0;

	main = (PolPok)malloc(sizeof(Polinom));
	if (main == NULL) {
		return NULL;
	}
	main->next = NULL;

	for (int i = 0; buffer[i] != '\n' && buffer[i] != '\0'; i++)
	{
		switch (buffer[i])
		{
			case '+': 
				// RESETIRAJ VARIJABLE
				addPolynom(main, temp);
				mod = 0;
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 1;

				break;
			case '-': 
				mod = 0;
				addPolynom(main, temp);
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = -1;
				break;
			case 'x':
				temp[1] = 1; // ne treba ^ ako je exp 1
				mod = 0;
				break;
			case '^':
				mod = 1;
				temp[1] = 0;
				break;
			default: // BROJEVI
				if (buffer[i] >= 48 && buffer[i] <= 57) {
					if (!mod) {
						temp[0] = temp[0] * 10 + (buffer[i] - '0');
					}
					else {
						temp[1] = temp[1] * 10 + (buffer[i] - '0');
					}
				}
				break;
		}

		
	}
	addPolynom(main, temp);
	printf("\n");

	return main;
}

int addPolynom(PolPok head, int values[]) { // HEAD SADRZAVA VRIJEDNOST POCETKA LISTE
	if (values[0] != 0)
	{
		if (head != NULL) {
			PolPok p = NULL;
			PolPok pom2 = NULL;
			PolPok p1 = head;
			
			/* SORTIRANI UNOS */
			while (p1->next != NULL && p1->next->eksponent >= values[1])
			{
				p1 = p1->next;
			}

			if (p1 != NULL && p1->eksponent == values[1])
			{
				p1->broj += values[0] * values[2];
				return 0;
			}

			p = (PolPok)malloc(sizeof(Polinom));
			if (p == NULL) return -1;
			p->broj = values[0] * values[2];
			p->eksponent = values[1];

			pom2 = p1->next;
			p1->next = p;
			p->next = pom2;
			return 0;
		}
		return -1;
	}
	return -1; // ERROR
}

int Ispis(PolPok head) {
	if (head != NULL)
	{
		PolPok p = head;
		PolPok p2 = NULL;
		for (p = p->next_array; p != NULL; p = p->next_array)
		{
			for (p2 = p->next; p2 != NULL; p2 = p2->next) {
				if (p2->broj > 0) printf("+");

					printf("%d", p2->broj);
					if (p2->eksponent > 0)
					{
						printf("x^%d", p2->eksponent);
					}
					printf(" ");
			}
			printf("\n");
		}
		return 0;
	}
	return -1;
}

PolPok ZbrojiPolinome(PolPok c) {
	if (c != NULL) {
		PolPok Novi = NULL;
		PolPok NoviEl = NULL;
		PolPok p = NULL;
		PolPok p_s = NULL;
		PolPok pom = NULL;
		int ind = 0;
		Novi = (PolPok)malloc(sizeof(Polinom));
		Novi->next = NULL;
		if (Novi != NULL)
		{
			for (p = c->next_array; p != NULL; p = p->next_array)
			{
				for (p_s = p->next; p_s != NULL; p_s = p_s->next) {
					for (NoviEl = Novi->next; NoviEl != NULL; NoviEl = NoviEl->next) // PROVJERIT JE LI POSTOJI VEC NEKI ELEMENT
					{
						if (NoviEl->eksponent == p_s->eksponent)
						{
							NoviEl->broj += p_s->broj;
							ind = 1;
						}
					}
					if (!ind) { // TREBA STVORIT NOVI ELEMENT
						NoviEl = (PolPok)malloc(sizeof(Polinom));
						if (NoviEl != NULL) {
							NoviEl->eksponent = p_s->eksponent;
							NoviEl->broj = p_s->broj;
							pom = Novi->next;
							Novi->next = NoviEl;
							NoviEl->next = pom;
						}
					}
					ind = 0;

				}
			}
		}
		return Novi;
	}
	return NULL;
}
