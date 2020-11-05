#define _CRT_SECURE_NO_WARNINGS


/* DODAT PROVJERE JELI NULL */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Polinom* PolPok;

typedef struct Polinom {
	int broj; // 3
	int exp; // 3x2(eksponent)
	int predznak; // 1 + -1 -
	PolPok next;
	PolPok next_array;
} _Polinom;

PolPok readFromFile();
PolPok MultiplePolynoms(PolPok); // ADRESA GLAVNOG HEADA
PolPok SubmitPolynoms(PolPok);
int Ispis(PolPok);
int DeleteAll(PolPok);

int main() {

	PolPok rez = NULL; // TU DOLAZI ADRESA GOTOVOG NIZA SA UMNOZENIM
	PolPok rez2 = NULL;
	// UCITAVANJE IZ DATOTEKE
	PolPok c = readFromFile(); // C sadrzi adresu glavnom HEADA;
	Ispis(c); 
	if (c != NULL) {
		rez = MultiplePolynoms(c);
		rez2 = SubmitPolynoms(rez);
	}
	else {
		printf("Datoteka je prazna.\n");
	}
	DeleteAll(c); // OCISTI SVE
	system("pause");
	return 0;
}

PolPok readFromFile() {
	FILE *f = NULL;
	PolPok p = NULL;
	PolPok pom = NULL; // pomocni
	PolPok head = NULL;
	PolPok glavniHead = NULL;
	char c;
	int b = 0;
	int mod = 0; // 0 => broj 1 =>eksponent
	int exponenti = 0;
	int br_linija = 0; 
	f = fopen("polinomi.txt", "r");

	glavniHead = (PolPok)malloc(sizeof(_Polinom));
	if (glavniHead != NULL) {
		head = (PolPok)malloc(sizeof(_Polinom));
		if (head == NULL) return NULL;
		glavniHead->next_array = head;

		head->next_array = NULL;

		p = (PolPok)malloc(sizeof(_Polinom));
		if (p == NULL) return NULL;
		head->next = p;
		// RESETIRANJE
		p->broj = 0;
		p->exp = 0;
		p->predznak = 1;
		p->next = NULL;


		while (1) {

			c = fgetc(f);

			if (c >= 48 && c <= 57)  // BROJEVI 
			{
				if (!mod) {
					// ZA BROJEVE
					p->broj = (p->broj) * 10 + (c - '0');

				}
				else {
					if (!exponenti) { 
						p->exp = 0;
						p->exp = (p->exp) * 10 + (c - '0');
						exponenti = 1;
					}
					else {
						p->exp = (p->exp) * 10 + (c - '0');
					}

				}
			}
			else {



				if (c == 'x') {
					mod = 0;
					p->exp = 1;
					exponenti = 0;
				}
				else if (c == '^')
				{
					mod = 1;
					exponenti = 0;
				}
				else if (c == '\n') {
					// STVORITI NOVI ARRAY
					pom = head;
					p = (PolPok)malloc(sizeof(_Polinom)); // NOVI HEAD
					if (p != NULL) {
						glavniHead->next_array = p;
						p->next_array = pom;

						head = p;
						p = (PolPok)malloc(sizeof(_Polinom));
						head->next = p;
						// RESETIRANJE
						p->broj = 0;
						p->exp = 0;
						p->predznak = 1;
						p->next = NULL;

						
					}
					mod = 0;
					exponenti = 0;

				}
				else if (c == '+' || c == '-')
				{
					pom = p;

					p = (PolPok)malloc(sizeof(_Polinom));
					if (p != NULL) {
						head->next = p;
						p->next = pom;

						p->broj = 0;
						p->exp = 0;
						exponenti = 0;
						if (c == '+')
						{
							p->predznak = 1;
						}
						else {
							p->predznak = -1;
						}
					}
					mod = 0;
				}
				else {
					mod = 0;
					exponenti = 0;
				}
			}

			if (feof(f)) break;
			br_linija++;


		}

		if (!br_linija) return NULL;
	}
	return glavniHead;
}


int Ispis(PolPok MainHead) {
	if (MainHead != NULL)
	{
		PolPok p = NULL;
		PolPok p2 = NULL;
		if (MainHead->next_array != NULL)
		{
			for (p = MainHead->next_array;  p != NULL; p = p->next_array) {
				p2 = p->next;
				for (p2 = p->next; p2 != NULL; p2 = p2->next)
				{

					printf("%s%dx^%d",(p2->predznak == 1) ? "+" : "-", p2->broj, p2->exp);
					printf(" ");
				}
				printf("\n");
			}
			return 0;
		}
		return -1;
	}
	return -1;
}

int DeleteAll(PolPok MainHead) {
	if (MainHead != NULL)
	{
		PolPok p = NULL;
		PolPok p2 = NULL;
		if (MainHead->next_array != NULL)
		{
			for (p = MainHead->next_array; p != NULL; p = p->next_array) {
				p2 = p->next;
				for (p2 = p->next; p2 != NULL; p2 = p2->next)
				{

					printf("%s%dx^%d", (p2->predznak == 1) ? "+" : "-", p2->broj, p2->exp);
					printf(" ");
				}
				printf("\n");
			}
			return 0;
		}
		return -1;
	}
	return -1;
}


//

PolPok MultiplePolynoms(PolPok mainHead) {
	if (mainHead != NULL) {
		PolPok suma = NULL;
		PolPok pom = NULL;
		PolPok p = NULL;
		PolPok p2 = NULL;
		PolPok p3 = NULL;
		PolPok rez = NULL;
		if (mainHead->next_array != NULL)
		{
			p = mainHead->next_array;
			if (p->next_array != NULL) {

				p2 = p->next_array;

				suma = (PolPok)malloc(sizeof(_Polinom));
				rez = suma;
				suma->next = NULL;
				suma->next_array = NULL;
				for (p3 = p; p3->next_array != NULL; p3 = p3->next_array) {
					p = p3;
					p2 = p3->next_array;
					for (p = p->next; p != NULL; p = p->next)
					{
						p2 = p3->next_array;
						for (p2 = p2->next; p2 != NULL; p2 = p2->next)
						{
							pom = suma;
							suma = (PolPok)malloc(sizeof(_Polinom));

							suma->next = pom->next;
							pom->next = suma;

							suma->broj = (p->broj)*(p2->broj);
							suma->exp = (p->exp) + (p2->exp);
							suma->predznak = (p->predznak)*(p2->predznak);

						}
					}
				}
				return rez;
			}
			return p;
		}
		return NULL;
	}
	return NULL;
}


PolPok SubmitPolynoms(PolPok rezPok) { // ADRESA HEAD CLANA
	if (rezPok != NULL) {
		PolPok pocetni = rezPok;
		rezPok = rezPok->next;
		if (rezPok != NULL) {
			PolPok pom = NULL;
			for (rezPok; rezPok->next != NULL; rezPok = rezPok->next) {
				if (rezPok->exp == rezPok->next->exp) {
					rezPok->broj += rezPok->next->broj;
					pom = rezPok->next;
					rezPok->next = rezPok->next->next;
					free(pom);
				}
			}
			return pocetni;
		}
		return NULL;
	}
		
	return NULL;
}
