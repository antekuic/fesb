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
int DodajPolinom(PolPok, int []);
PolPok ZbrojiPolinome(PolPok); // VRACA ADRESU HEADA OD REZULTATA ZBRAJANJA
PolPok PomnoziPolinome(PolPok);
int Ispis(PolPok);
int Ispis_l(PolPok);
int DodajPolinom_l(PolPok, int, int);
int DeleteArrays(PolPok);
int DeleteList(PolPok, PolPok);

int main() {
	PolPok c = NULL, rez_z = NULL;
	int ind = 0, opcija = 0;
	printf("Unesite opciju: \n"
		"0- Ucitavanje iz datoteke\n1 - Mnozenje polinoma\n2 - Zbrajanje polinoma\n3 - Ispis trenutno stanje\n"
	"Opcija: ");
	while (!ind) {
		scanf("%d", &opcija);
		switch (opcija) {
		case 0: 
			// DODATI BRISANJE c-ova ovdje;
			DeleteArrays(c);
			c = loadingData();
			if (c != NULL) {
				printf("Polinomi ucitani iz datoteke.");
			}
			break;
		case 1:
			// DODATI I BRISANJE rez_z ovdje
			DeleteList(rez_z, rez_z);
			if ((rez_z = PomnoziPolinome(c)) != NULL) {
				printf("\n");
				Ispis_l(rez_z);
			}
			else {
				printf("Dogodila se greska");
			}
			break;
		case 2: 

			// DODATI I BRISANJE rez_z ovdje
			DeleteList(rez_z, rez_z);
			if ((rez_z = ZbrojiPolinome(c)) != NULL) {
				printf("\n");
				Ispis_l(rez_z);
			}
			else {
				printf("Dogodila se greska");
			}
			break;
		case 3: 
			printf("\n");
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
				DodajPolinom(main, temp);
				mod = 0;
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 1;

				break;
			case '-': 
				mod = 0;
				DodajPolinom(main, temp);
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
	DodajPolinom(main, temp);
	printf("\n");

	return main;
}

int DodajPolinom(PolPok head, int values[]) { // HEAD SADRZAVA VRIJEDNOST POCETKA LISTE
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

int Ispis_l(PolPok head) {
	if (head != NULL)
	{
		PolPok p = NULL;
		for (p = head->next; p != NULL; p = p->next) {
			if (p->broj > 0) printf("+");
			printf("%d", p->broj);
			if (p->eksponent > 0)
			{
				printf("x^%d", p->eksponent);
			}
			printf(" ");
		}
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
		Novi = (PolPok)malloc(sizeof(Polinom));
		
		if (Novi != NULL)
		{
			Novi->next = NULL;
			for (p = c->next_array; p != NULL; p = p->next_array)
			{
				for (p_s = p->next; p_s != NULL; p_s = p_s->next) {
					DodajPolinom_l(Novi, p_s->eksponent, p_s->broj); // SORTIRANO DODAVANJE
				}
			}
		}
		return Novi;
	}
	return NULL;
}

int DodajPolinom_l(PolPok head, int exp, int broj) {
	if (head != NULL) {
		PolPok NoviEl = NULL;
		PolPok pom = NULL;
		PolPok p = head;
		int ind = 0;
		while (p->next != NULL) {
			if (p->next->eksponent <= exp)
			{
				if (p->next->eksponent == exp) {
					ind = 1;
					pom = p->next;
				}
				break;
			}
			p = p->next;
		}

		if(ind)
		{
			pom->broj += broj;
		}
		else {
			NoviEl = (PolPok)malloc(sizeof(Polinom));
			NoviEl->broj = broj;
			NoviEl->eksponent = exp;

			pom = p->next;
			p->next = NoviEl;
			NoviEl->next = pom;
		}
		return 0;
	}
	return -1;
}

PolPok PomnoziPolinome(PolPok mainHead) {

	// JOS DODAT BRISANJE...
	if (mainHead != NULL)
	{
		PolPok p = mainHead;
		PolPok p1 = NULL;
		PolPok p2 = NULL;
		PolPok head = NULL;
		PolPok pom = NULL;
		PolPok pomSuma = NULL;
		int ind = 0;
		head = (PolPok)malloc(sizeof(Polinom));
		if (head != NULL) {
			head->next = NULL;
			p = p->next_array;
			while(p->next_array != NULL)
			{
				if (ind) {
					p = head;
					pomSuma = head; // ZA OBRISAT
					head = (PolPok)malloc(sizeof(Polinom));
					head->next = NULL;
				}
				for (p1 = p->next; p1 != NULL; p1 = p1->next) // KROZ LISTU
				{	
					if (p->next_array != NULL)
					{
						for (p2 = p->next_array->next; p2 != NULL; p2 = p2->next) // KROZ DRUGU LISTU
						{
								DodajPolinom_l(head, p2->eksponent + p1->eksponent, (p2->broj)*(p1->broj));
						}
					}
					ind = 1;
				}
				
				// DODATI SUMU IZA Next_ARRAYA
				if (p->next_array != NULL)
				{

					pom = p->next_array->next_array;
					p->next_array->next_array = head;
					head->next_array = pom;
					p = head;
					
					
				}
				

			}
		}
		return head;

	}
	return NULL;
}

int DeleteList(PolPok head, PolPok head2) {
	if (head == NULL) return 0;
	DeleteList(head->next, head2);
	if (head != head2) {
		free(head);
	}
	return 0;
}

int DeleteArrays(PolPok head) {
	PolPok pomocni = NULL;
	if (head != NULL && head->next != NULL)
	{
		while (head != NULL)
		{
			DeleteList(head, head);
			head = head->next;

		}
	}
	return 0;
}
