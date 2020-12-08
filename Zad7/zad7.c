/*
RACUNANJE
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 256

typedef struct _head* Pok;

typedef struct _head {
	char El;
	int br;
	Pok next;
} Head;

int LoadData(Pok, Pok);
char pop(Pok);
int AddToInFix(Pok, char *);
int ConvertToPost(Pok, Pok);
int Push(Pok, char);
int Ispis(Pok);
int Provjera(char, char);
int DeleteAll(Pok);
int Suma(Pok);
int PushTwo(Pok head, int el);
int popTwo(Pok head);
int IsSymbol(char);
int ManageOperation(char, int, int);

int main() {

	int opcija = 1;
	Pok InFix = NULL,
		PostFix = NULL;

	InFix = (Pok)malloc(sizeof(Head));
	InFix->next = NULL;

	PostFix = (Pok)malloc(sizeof(Head));
	PostFix->next = NULL;


	while (opcija) {
		printf("Odaberite opciju:\n"
			"1 - Ucitaj iz datoteke\n"
			"2 - Ispisi Infix\n"
			"3 - Ispisi postfix\n"
			"4 - Izracunaj\n"
			"0 - Kraj\n");
		printf("Unesite opciju: ");

		scanf("%d", &opcija);
		switch (opcija) {
		case 1: // Ucitavanje
		{
			/* BRISANJE PRIJE UCITAVANJA*/
			DeleteAll(PostFix);
			DeleteAll(InFix);
			LoadData(InFix, PostFix);
			break;
		}
		case 2: // ISPIS INFIX
		{
			printf("\nInFix izraz: ");
			Ispis(InFix);
			printf("\n");
			break;
		}
		case 3: {
			printf("\nPostFix izraz: ");
			Ispis(PostFix);
			printf("\n");
			break;

		}
		case 4: {
			// SUMA
			if (PostFix->next == NULL) {
				printf("\nNista nije uneseno.");
			}
			else {
				printf("\nSuma unesenog izraza je %d", Suma(PostFix));
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
	DeleteAll(PostFix);
	DeleteAll(InFix);
	free(PostFix);
	free(InFix);
	system("pause");
	return 0;
}
/* UNOS */
int LoadData(Pok InFix, Pok PostFix) {

	FILE *fp = NULL;
	char string[BUFFER];
	fp = fopen("izraz.txt", "r");
	if (fp == NULL) return -1;
	while (1)
	{
		if (fgets(string, BUFFER, fp) != NULL)
		{
			if (strlen(string) > 1)
			{
				AddToInFix(InFix, string);
			}
		}
		if (feof(fp)) break;
	}
	fclose(fp);

	ConvertToPost(InFix, PostFix);

	return 0;
}

int AddToInFix(Pok InFix, char *buffer)
{
	if (InFix != NULL)
	{
		int br = 0,
			offset = 0,
			i = 0;

		while (sscanf(buffer, "%d%n%*[^\n]", &br, &offset) == 1)
		{
			buffer += offset;
			InFix->next = (Pok)malloc(sizeof(Head));
			InFix = InFix->next;
			InFix->br = br;
			InFix->El = '\0';
			InFix->next = NULL;
			i = 0;
			while (buffer[i] != '\0' && !isdigit(buffer[i]))
			{
				if (IsSymbol(buffer[i]))
				{
					InFix->next = (Pok)malloc(sizeof(Head));
					InFix = InFix->next;
					InFix->El = buffer[i];
					InFix->next = NULL;
				}
				i++;
			}
			buffer += i;

		}
		return 0;
	}
	return -1;
}

int ConvertToPost(Pok InFix, Pok PostFix) {
	Pok stog = NULL;
	char znak = 'a', znak1 = 'a', c = 'a';
	int ind = 0;
	stog = (Pok)malloc(sizeof(Head));
	stog->next = NULL;

	while (InFix->next != NULL)
	{
		InFix = InFix->next;
		if (InFix->El == '\0')
		{
			// BROJEVI
			PostFix->next = (Pok)malloc(sizeof(Head));
			PostFix = PostFix->next;

			PostFix->El = '\0';
			PostFix->br = InFix->br;
			PostFix->next = NULL;
		}
		else {
			// PRIMJENA STOGA
			if (stog->next != NULL)
			{
				// NIJE PRAZAN

				while (stog->next != NULL && (ind = Provjera(InFix->El, stog->next->El)) != 0)
				{

					PostFix->next = (Pok)malloc(sizeof(Head));
					PostFix = PostFix->next;

					PostFix->El = pop(stog);
					PostFix->next = NULL;
				}

				if (InFix->El != ')')
				{
					Push(stog, InFix->El);
				}
				else {
					if (stog->next->El == '(')
					{
						pop(stog);
					}
				}

			}
			else {
				// DODAJ NA STOG JER JE PRAZAN
				Push(stog, InFix->El);
			}
		}
	}
	// ISPRAZNI STOG

	while (stog->next != NULL)
	{
		PostFix->next = (Pok)malloc(sizeof(Head));
		PostFix = PostFix->next;

		PostFix->El = pop(stog);
		PostFix->next = NULL;
	}
	/*OBRISI STOG HEAD*/
	free(stog);
	return 0;
}

/* STOG FUNKCIJE */
char pop(Pok head) {
	if (head == NULL) return '\0';
	Pok pom = head->next;
	if (pom == NULL) return '\0'; // STOG PRAZAN
	char vrj;
	head->next = head->next->next;
	vrj = pom->El;
	free(pom);
	return vrj;
}

int Push(Pok head, char el) {
	if (head == NULL) return -1;
	Pok new = NULL;
	new = (Pok)malloc(sizeof(Head));
	if (new == NULL) return -1;
	new->next = head->next;
	head->next = new;
	new->El = el;
	return 0;
}

/* ISPIS */
int Ispis(Pok Lista)
{

	while (Lista->next != NULL)
	{
		Lista = Lista->next;
		if (Lista->El == '\0')
		{
			printf("%d ", Lista->br);
		}
		else {
			printf("%c", Lista->El);
		}
	}
	return 0;
}
/* STOG OPERACIJE */
int Provjera(char znak1, char znak2)  // DOLAZI, STOG -> VRATI 0 ako mozes dodat na stog.
{
	if (znak1 == '(') return 0;
	else if (znak1 == ')' && znak2 == '(') return 0;
	else if (znak1 == ')') return 1;
	else if (znak2 == '(') return 0;
	else if (znak1 == znak2) return 1;
	else {
		switch (znak2)
		{
		case '+': {
		case '-':
			if (znak1 == '+' || znak1 == '-')
				return 1;
			else return 0;
			break;
		}
		default:
			return 1;
		}
	}

}

/* BRISANJE */

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

/* SUMA */
int Suma(Pok head) {
	int var = 0;
	Pok new = (Pok)malloc(sizeof(head));
	new->next = NULL;
	for (head = head->next; head != NULL; head = head->next)
	{
		if (head->El == '\0') // BROJ 
		{
			PushTwo(new, head->br);
		}
		else {
			// OPERACIJA
			var = ManageOperation(head->El, popTwo(new), popTwo(new));
			PushTwo(new, var);
		}
	}
	if (new->next != NULL)
	{
		var = new->next->br;
		DeleteAll(new);
	}
	return var;
}

int popTwo(Pok head) {
	if (head == NULL) return -1;
	Pok pom = head->next;
	if (pom == NULL) return -1; // STOG PRAZAN
	int vrj;
	head->next = head->next->next;
	vrj = pom->br;
	free(pom);
	return vrj;
}
int PushTwo(Pok head, int el) {
	if (head == NULL) return -1;
	Pok new = NULL;
	new = (Pok)malloc(sizeof(Head));
	if (new == NULL) return -1;
	new->next = head->next;
	head->next = new;
	new->br = el;
	return 0;
}

int ManageOperation(char operacija, int first, int second) {
	int rez = 0;
	switch (operacija) {
	case '+':
	{
		rez = first + second;
		break;
	}
	case '-':
	{
		rez = first - second;
		break;
	}
	case '*':
	{
		rez = first * second;
		break;
	}
	case '/':
	{
		rez = first / second;
		break;
	}
	}
	return rez;
}
int IsSymbol(char c)
{
	return (c >= 40 && c <= 47) ? 1 : 0;
}
