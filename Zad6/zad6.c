/*
STOG I RED

*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _head* Pok;

typedef struct _head {
	int El;
	Pok next;
} Head;

int RandBroj(int, int);
int Push(int, Pok);
int Pop(Pok);
int IspisStoga(Pok);
int IspisReda(Pok);
int DeleteAll(Pok);

int main() {
	int var = 0, opcija = 1;
	Pok Stog = NULL,
		Red = NULL, 
		Last = NULL; // ZA RED

	Stog = (Pok)(malloc(sizeof(Head)));
	Stog->next = NULL;

	Red = (Pok)(malloc(sizeof(Head)));
	Red->next = NULL;

	srand((unsigned)time(0));
	
	while (opcija) {
		printf("Odaberite opciju:\n"
			"0 - UGASI\n"
			"1 - UPIS U STOG\n"
			"2 - BRISANJE SA STOGA\n"
			"3 - ISPIS SA STOGA\n"
			"4 - UPIS U RED\n"
			"5 - BRISANJE S REDA\n"
			"6 - ISPIS REDA\n");
		printf("Unesite opciju: ");

		scanf("%d", &opcija);
		switch (opcija) {
			case 1: // UPIS STOG
			{
				var = RandBroj(100, 10);
				printf("\nU stog je upisan broj %d.\n", var);
				printf("Za ispis citavog stoga koristite opciju 3.");
				Push(var, Stog);
				break;
			}
			case 2: // BRISANJE SA STOGA
			{
				if ((var = Pop(Stog)) > 0) {
					if (var == 1) {
						printf("\nStog je prazan, nismo imali sto obrisati.");
					}
					else {
						printf("\nSa stoga je skinuta vrijednost %d.", var);
					}
				}
				break;
			}
			case 3: // ISPIS STOGA
			{
				if (IspisStoga(Stog)) {
					printf("\nStog je prazan.");
				}
				break;
			}
			case 4: // UPIS U RED
			{
				var = RandBroj(100, 10);
				printf("\nU red je upisan broj %d.\n", var);
				printf("Za ispis citavog reda koristite opciju 6.");

				if(Red->next == NULL) // UPIS U PRAZAN RED
				{	
					Push(var, Red);
					Last = Red->next;
				}
				else {
					Push(var, Last);
					Last = Last->next;
				}

				break;
			}
			case 5: // POP IZ REDA
			{
				if ((var = Pop(Red)) > 0) {
					if (var == 1) {
						printf("\nRed je prazan, nismo imali sto obrisati.");
					}
					else {
						printf("\nSa reda je skinuta vrijednost %d.", var);
					}
				}
				break;
			}
			case 6:
			{
				if (Red->next == NULL)
				{
					printf("\nRed je prazan.");
				}
				else {
					printf("\n\n\tRED\n");
					IspisReda(Red->next);
				}
				break;
			}
			default:
			{
				printf("\nSvi podaci izbrisani. Program ugasen!!!");
				break;
			}
		}
		printf("\n\n");
	}

	DeleteAll(Stog);
	DeleteAll(Red);
	free(Stog);
	free(Red);
	system("pause");
	return 0;
}

int RandBroj(int a, int b) {
	return (rand() % (a - b + 1) + b);
}

int Push(int el, Pok head) {
	if (head == NULL) return -1;
	Pok new = NULL;
	new = (Pok)malloc(sizeof(Head));
	if (new == NULL) return -1;
	new->next = head->next;
	head->next = new;
	new->El = el;
	return 0;
}

int Pop(Pok head) {
	int vrj = 0;
	if (head == NULL) return -1;
	Pok pom = head->next;
	if (pom == NULL) return 1; // STOG PRAZAN
	head->next = head->next->next;
	vrj = pom->El;
	free(pom);
	return vrj;
}

int IspisStoga(Pok head) {

	if (head == NULL || head->next == NULL) return 1;

	printf("\n\n\tSTOG\n");

	while (head->next != NULL) {
		head = head->next;
		printf("\n|\t%d\t|\n", head->El);
		printf("-----------------");
	}
	printf("\n\n");
	return 0;
}

int IspisReda(Pok head) {
	if (head->next == NULL) {
		printf("\n|\t%d\t|\n", head->El);
		printf("-----------------");
		return 1;
	}
	IspisReda(head->next);
	printf("\n|\t%d\t|\n", head->El);
	printf("-----------------");
	return 1;
}

int DeleteAll(Pok head) {
	Pok pom = NULL;
	while (head->next != NULL)
	{
		pom = head->next;
		head->next = head->next->next;
		free(pom);
	}
	return 0;
}
