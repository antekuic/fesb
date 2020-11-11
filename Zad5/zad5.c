#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* ZADATAK 5
Presjek i unija

MAINHEAD -> RED -> RED -> RED
	     |	    |	   |
	Elementi Elementi Elementi

LookUP Tablica: Adrese head-a od elementa.
*/

#define BUFFER_SIZE 256
#define MAX_LIST 10

typedef struct _Element* ListaP;
typedef struct _head* HeadP;

typedef struct _head {

	HeadP next_array;
	ListaP elements;

} Head;

typedef struct _Element {

	int el;
	ListaP next;

} Lista;

int loadData(HeadP, ListaP[]);
int bufferFormating(ListaP, char *);
int sortUnos(ListaP, int);
int Ispis(ListaP);
int DeleteList(ListaP);
int DeleteAll(HeadP);
ListaP Unija(ListaP, ListaP); // VRACA ADRESU UNIJE
ListaP Presjek(ListaP, ListaP); // VRACA ADRESU PRESJEK

int main() {
	HeadP main_head = (HeadP)(malloc(sizeof(Head)));
	ListaP rez = NULL; // REZULTAT OPERACIJE
	ListaP lookup[MAX_LIST] = { NULL }; // LOOKUP TABLICA
	main_head->next_array = NULL;
	main_head->elements = NULL;
	
	int opcija = 0, first = 0, second = 0;
	
	// UCITAVANJE LISTI IZ DATOTEKE;
	if (!loadData(main_head, lookup)) {
		printf("Ucitane liste: \n");
		for (int i = 0; i < MAX_LIST; i++)
		{
			if (lookup[i] != NULL)
			{
				printf("L%d: ", i + 1);
				Ispis(lookup[i]);
				printf("\n");
			}
			else break;
		}
		
		printf("\n0: UNIJA | 1: PRESJEK | 3: GASENJE PROGRAMA:\nUnesite opciju(opcija id_prviclan id_drugiclan): ");

		while (opcija != -1)
		{
			scanf(" %d %d %d", &opcija, &first, &second);
			if ((opcija == 0 || opcija == 1) && ((first <= 0 || second <= 0) || lookup[first-1] == NULL || lookup[second-1] == NULL)) {
				printf("\nUnijeli ste neispravne clanove. Ponovite.");
			}
			else {
				switch (opcija) {
				case 0:
					if (rez != NULL)
					{
						DeleteList(rez);
					}
					rez = Unija(lookup[first - 1], lookup[second - 1]);
					printf("L%d U L%d: ", first, second);
					Ispis(rez);
					printf("\n");
					break;
				case 1:
					if (rez != NULL)
					{
						DeleteList(rez);
					}
					rez = Presjek(lookup[first - 1], lookup[second - 1]);
					printf("L%d PRESJEK L%d: ", first, second);
					Ispis(rez);
					printf("\n");
					break;
				default:
					opcija = -1;
					printf("\nProgram gotov. Sva memorija ociscena.");
					break;
				}
			}
			if (opcija != -1) {
				printf("\nUnesite opciju: ");
			}
		}
	}

	if (rez != NULL) {
		DeleteList(rez);
		free(rez);
	}
	DeleteAll(main_head);
	free(main_head);
	system("pause");
	return 0;
}

int loadData(HeadP main_head, ListaP lookup[]) {
	if (main_head != NULL) {
		FILE *f = NULL;
		HeadP pom = NULL;
		char string[BUFFER_SIZE];
		int d = 0; // Za odredivanje liste.
		f = fopen("niz.txt", "r");
		if (f == NULL) return -1;
		while (1) {
			if (d == MAX_LIST) break;
			if (fgets(string, BUFFER_SIZE, f) != NULL) {
				if (strlen(string) > 1)
				{
					pom = main_head->next_array;
					main_head->next_array = (HeadP)malloc(sizeof(Head));
					main_head->next_array->next_array = pom;
					main_head->next_array->elements = (ListaP)malloc(sizeof(Lista));
					lookup[d] = main_head->next_array->elements;
					main_head->next_array->elements->next = NULL;
					bufferFormating(main_head->next_array->elements, string);
					d++;
				}
				if (feof(f)) break;
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

int DeleteAll(HeadP head)
{
	if (head != NULL)
	{
		head = head->next_array;
		HeadP pom = NULL;
		while (head != NULL && head->next_array != NULL)
		{
			pom = head->next_array;
			head->next_array = head->next_array->next_array;
			DeleteList(pom->elements);
			free(pom);
		}
		if (head != NULL)
		{
			free(head);
		}
		return 0;
	}
	return -1;
}
