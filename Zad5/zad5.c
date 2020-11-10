#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* ZADATAK 5
Presjek i unija*/

#define BUFFER_SIZE 256

typedef struct _Element* ListaP;

typedef struct _Element {

	int el;
	ListaP next;

} Lista;

int loadData(ListaP, ListaP);
int bufferFormating(ListaP, char *);
int sortUnos(ListaP, int);
int Ispis(ListaP);
int DeleteList(ListaP);
ListaP Unija(ListaP, ListaP); // VRACA ADRESU UNIJE
ListaP Presjek(ListaP, ListaP); // VRACA ADRESU PRESJEK

int main() {
	ListaP l1 = (ListaP)malloc(sizeof(Lista)); // HEAD; ( PROVJERE ZA ISPRAVNO MALLOCIRANJE U loadData )
	l1->next = NULL;
	ListaP l2 = (ListaP)malloc(sizeof(Lista)); // HEAD;
	l2->next = NULL;
	ListaP rez = NULL; // REZULTAT OPERACIJE
	int opcija = 0;
	
	// UCITAVANJE LISTI IZ DATOTEKE;
	if (!loadData(l1, l2)) {
		printf("Ucitane liste: \n");
		printf("L1: ");
		Ispis(l1);
		printf("\nL2: ");
		Ispis(l2);
		printf("\n0: UNIJA | 1: PRESJEK:\nUnesite opciju: ");

		while (opcija != -1)
		{
			scanf(" %d", &opcija);
			switch (opcija) {
			case 0:
				if (rez != NULL)
				{
					DeleteList(rez);
				}
				rez = Unija(l1, l2);
				printf("L1 U L2: ");
				Ispis(rez);
				printf("\n");
				break;
			case 1:
				if (rez != NULL)
				{
					DeleteList(rez);
				}
				rez = Presjek(l1, l2);
				printf("L1 PRESJEK L2: ");
				Ispis(rez);
				printf("\n");
				break;
			default:
				opcija = -1;
				printf("\nProgram gotov. Sva memorija ociscena.");
				break;
			}
			printf("\nUnesite opciju: ");
		}
	}

	DeleteList(rez);
	free(rez);
	DeleteList(l1);
	free(l1);
	DeleteList(l2);
	free(l2);

	system("pause");
	return 0;
}

int loadData(ListaP l1, ListaP l2) {
	if (l1 != NULL && l2 != NULL) {
		FILE *f = NULL;
		char string[BUFFER_SIZE];
		int d = 0; // Za odredivanje liste.
		f = fopen("niz.txt", "r");
		if (f == NULL) return -1;
		while (1) {
			if (d == 2) break;
			if (fgets(string, BUFFER_SIZE, f) != NULL) {
				if (d == 0) {
					bufferFormating(l1, string);
				}
				else {
					bufferFormating(l2, string);
				}
				d++;
			}
		}
		return 0;
	}
	return -1;
}

int bufferFormating(ListaP l, char *buffer) {
	if (l != NULL)
	{
		int br = 0;
		int count = 0;
		while (sscanf(buffer, "%d%n%*[^\n]", &br, &count) == 1) // ne citaj iza \n i \0
		{
			buffer += count;
			sortUnos(l, br);
		}
	}
	return -1;
}

int sortUnos(ListaP l, int br) {
	if (l != NULL)
	{
		ListaP novi = NULL;
		int ind = 0;
		while (l->next != NULL && l->next->el <= br)
		{
			if (l->next->el == br)
			{
				ind = 1;
				break;
			}
			l = l->next;
		}
		if (!ind) {
			novi = (ListaP)malloc(sizeof(Lista));
			novi->next = l->next;
			novi->el = br;
			l->next = novi;
		}
		return 0;
	}
	return -1;
}

int Ispis(ListaP l)
{
	if (l != NULL)
	{
		l = l->next;
		while (l != NULL)
		{
			printf(" %d", l->el);
			l = l->next;
		}
	}
	return -1;

}

ListaP Unija(ListaP l1, ListaP l2)
{
	if (l1 != NULL && l2 != NULL)
	{
		ListaP head = (ListaP)malloc(sizeof(Lista));
		l1 = l1->next;
		l2 = l2->next;

		head->next = NULL;

		while (l1 != NULL)
		{
			sortUnos(head, l1->el);
			l1 = l1->next;
		}
		while (l2 != NULL)
		{
			sortUnos(head, l2->el);
			l2 = l2->next;
		}

		return head;
	}
	return NULL;
}

ListaP Presjek(ListaP l1, ListaP l2)
{
	if (l1 != NULL && l2 != NULL)
	{
		ListaP head = (ListaP)malloc(sizeof(Lista));
		l1 = l1->next;
		l2 = l2->next;

		head->next = NULL;

		while (1) // SORTIRANI SU
		{
			if (l1 != NULL && l2 != NULL) {
				if (l1->el > l2->el)
				{
					l2 = l2->next;
				}
				else if (l1->el < l2->el)
				{
					l1 = l1->next;
				}
				else {
					sortUnos(head, l2->el);
					l2 = l2->next;
					l1 = l1->next;
				}
			}
			else {
				break;
			}
		}

		return head;
	}
	return NULL;
}

int DeleteList(ListaP l)
{
	if (l != NULL)
	{
		l = l->next;
		ListaP pom = NULL;
		while (l != NULL && l->next != NULL)
		{
			pom = l->next;
			l->next = l->next->next;
			free(pom);
		}
		if (l != NULL)
		{
			free(l);
		}
		return 0;
	}
	return -1;
}
