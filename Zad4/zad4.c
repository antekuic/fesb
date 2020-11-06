#define _CRT_SECURE_NO_WARNINGS

/*
MAIN HEAD -> HEAD1 -> HEAD2 -> .... (head)
				|		|
			 lista1	  lista2 ..... (Polinom)

 PRIMJER FILEA:
6x^2 +4x
3x
6x +4x^2
3x +4x^5

*/

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

typedef struct _Polinom* PolPok;

typedef struct _Polinom {
	int broj; // ->koeficijent
	int eksponent; // -> eksponent
	int ind;
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
int DeleteList(PolPok);
int DeleteAll(PolPok);

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
			if (c != NULL && c->next_array != NULL) {
				DeleteAll(c); // OBRISI SVE
			}

			c = loadingData();
			if (c != NULL) {
				printf("Polinomi ucitani iz datoteke.");
			}
			break;
		case 1:
			// DODATI I BRISANJE rez_z ovdje
			if ((rez_z = PomnoziPolinome(c)) != NULL) {
				printf("\n");
				Ispis_l(rez_z);
				DeleteArrays(c); // IZBRISI UMNOZENE POLINOME
			}
			else {
				printf("Dogodila se greska");
			}
			break;
		case 2: 

			// DODATI I BRISANJE rez_z ovdje
			if ((rez_z = ZbrojiPolinome(c)) != NULL) {
				printf("\n");
				Ispis_l(rez_z);
				DeleteList(rez_z);
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
	
	DeleteAll(c); // OBRISI SVE
	system("pause");
	return 0;
}

int DeleteArrays(PolPok mainHead) {
	PolPok pom = NULL;
	while (mainHead != NULL && mainHead->next_array != NULL) {
		pom = mainHead->next_array;
		if (pom->ind == 1) {
			mainHead->next_array = pom->next_array;
			DeleteList(pom);
			free(pom);
		}
		mainHead = mainHead->next_array;
	}
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

PolPok createPolynomList(char *data) { /* OBLIK PRIMJERA 22x^3 */

	PolPok main = NULL; // -> MAIN HEAD ZA LISTU
	int polinom[2] = { 0 }; // 0 -> broj 1 -> exp 2->predznak
	int ind = 0, ind2 = 0;
	int n, offset;

	main = (PolPok)malloc(sizeof(Polinom));
	if (main == NULL) {
		return NULL;
	}
	main->next = NULL;

	while (sscanf(data, "%d%n%*[^\n]%*[^\0]", &n, &offset) == 1)
	{

		data += offset;
		if (data[0] == 'x' && data[1] == '^')
		{
			// NEKA DRUGA POTENCIJA
			data += 2;
			polinom[0] = n;
			ind = 1;
			ind2 = 1;
		}
		else if (data[0] == 'x' && data[1] != '^')
		{
			// PODETNCIJA 1
			polinom[0] = n;
			polinom[1] = 1;
			data++;
		}
		else {
			// OBICAN BROJ
			if (ind) {
				ind = 0;
				polinom[1] = n;
				ind2 = 0;
			}
			else {
				polinom[0] = n;
				polinom[1] = 0;
			}
		}
		if (!ind2) {
			printf("%d %d\n", polinom[0], polinom[1]);
			DodajPolinom(main, polinom);
			// NOVI ELEMENT
		}
	}
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
				p1->broj += values[0];
				return 0;
			}

			p = (PolPok)malloc(sizeof(Polinom));
			if (p == NULL) return -1;
			p->broj = values[0];
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

	if (mainHead != NULL && mainHead->next_array != NULL) {
		PolPok p = mainHead->next_array;
		PolPok q = NULL;
		PolPok new = (PolPok)malloc(sizeof(Polinom));
		PolPok pom1 = NULL, pom2 = NULL, pom = NULL;
		int ind = 0;
		new->next = NULL;
		if (p->next_array == NULL) return p;
		while ((q = p->next_array) != NULL) {
			if (ind) {
				new = (PolPok)malloc(sizeof(Polinom));
				new->next = NULL;
			}
			pom1 = p;
			pom2 = q;
			while (p->next != NULL) {
				p = p->next;
				while (q->next != NULL) {
					q = q->next;
					DodajPolinom_l(new, q->eksponent + p->eksponent, (q->broj)*(p->broj));
					ind = 1;
				}
				q = pom2;
			}
			p = pom1;

			pom = pom2->next_array;
			pom2->next_array = new;
			new->next_array = pom;
			new->ind = 1;
			p = new;
		}
		return new;
	}
	return NULL;
}

int DeleteList(PolPok head) {
	if (head != NULL)
	{
		PolPok temp = NULL;
		PolPok temp2 = head;
		temp2 = temp2->next;
		while (temp2 != NULL) {
			temp = temp2;
			temp2 = temp2->next;
			free(temp);
		}
		return 0;
	}
	return -1;

}

int DeleteAll(PolPok mainHead) {
	PolPok pom = NULL;
	while (mainHead != NULL && mainHead->next_array != NULL) {
		pom = mainHead->next_array;
		mainHead->next_array = pom->next_array;
		DeleteList(pom); // BRISE LISTU
		free(pom); // BRISI HEAD OD LISTE
		mainHead = mainHead->next_array;
	}
	return 0;
}
