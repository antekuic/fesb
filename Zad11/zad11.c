#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 32
#define BUFFER_SIZE 256
#define TABLE_SIZE 11

typedef struct _lista* Pok;
typedef struct _lista {
	char ime[STRING_SIZE],
		prezime[STRING_SIZE];

	int mat_broj;
	Pok next;
};

Pok* StvoriTablicu();
int LoadData(Pok *);
int ParsirajIUcitaj(Pok *, char *);
int hash(char *);
int UnosSort(Pok, Pok);
int TablicaIspis(Pok *);
int Ispis(Pok);
int MatBroj(Pok*, char *);
int DeleteAll(Pok *);
int Delete(Pok);

int main()
{
	Pok* studenti = StvoriTablicu(); // HASH TABLICA
	char prezime[STRING_SIZE];
	if (studenti == NULL) return 0;

	if(LoadData(studenti) == -1) return 0;
	printf("\nUNESENI PODATCI: \n");
	TablicaIspis(studenti);
	printf("Unesite prezime ciji maticni broj zelite vidit('esc' za prekid): ");
	while (scanf(" %s", prezime))
	{
		if (!strcmp(prezime, "esc")) break;
		printf("Maticni broj studenta %s: %d\n", prezime, MatBroj(studenti, prezime));
		printf("Unesite prezime ciji maticni broj zelite vidit('esc' za prekid): ");
	}

	DeleteAll(studenti);
	system("pause");
	return 0;
}

/*DEFAULT*/

Pok* StvoriTablicu() {
	Pok* temp = (Pok*)malloc(sizeof(Pok)*TABLE_SIZE); // ARRAY POKAZIVACA
	if (temp == NULL) return NULL;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		// KREIRAJ HEADOVE
		temp[i] = (Pok)malloc(sizeof(struct _lista));
		temp[i]->next = NULL;
	}

	return temp;
}

/*UCITAVANJE*/
int LoadData(Pok* root)
{
	if (root == NULL) return -1;

	FILE *fp = NULL;
	char buffer[BUFFER_SIZE];

	fp = fopen("studenti.txt", "r");
	if (fp == NULL) return -1;

	while (fgets(buffer, BUFFER_SIZE, fp) != NULL)
	{
		ParsirajIUcitaj(root, buffer);
	}

	return 0;
}

int ParsirajIUcitaj(Pok *root, char *buffer)
{
	if (root == NULL || buffer == NULL) return -1;
	// FORMATIRANA
	int i = -1;
	Pok temp = (Pok)malloc(sizeof(struct _lista));
	if(temp == NULL) return 0;
	sscanf(buffer, "%d %s %s", &(temp->mat_broj), temp->ime, temp->prezime);
	char temp2[32];
	sprintf(temp2, "%s", temp->prezime);
	i = hash(temp2);
	if (i == -1) return -1;
	UnosSort(root[i], temp);

	return 0;
}

/* HASHING */

int hash(char *prezime)
{
	if (prezime == NULL) return -1; // break programa
	if (strlen(prezime) < 5) {
		sprintf(prezime, "%s%s",prezime, prezime);
		return hash(prezime);
	}
	int sum = 0;
	for (int i = 0; i < 5; i++)
	{
		sum += (int)prezime[i];
	}

	return sum % TABLE_SIZE;
}

/* VEZANE LISTE */

int UnosSort(Pok root, Pok temp)
{
	if (root == NULL || temp == NULL) return -1;

	while (root->next != NULL && root->next->next != NULL) {
		if (strcmp(root->next->prezime, temp->prezime) > 0 || (!strcmp(root->next->prezime, temp->prezime) && strcmp(root->next->ime, temp->ime) > 0))
			break;
		root = root->next;
	}

	temp->next = root->next;
	root->next = temp;

	return 0;
}
int Ispis(Pok root)
{
	while (root != NULL)
	{
		printf("%d %s %s\n", root->mat_broj, root->ime, root->prezime);
		root = root->next;
	}
	return 0;
}
int Delete(Pok root)
{
	if (root == NULL) return -1;

	while (root != NULL && root->next != NULL)
	{
		Pok temp = root->next;
		root = root->next->next;
		free(temp);
	}
	return 0;
}

/* ISPIS */
int TablicaIspis(Pok *root)
{
	if (root == NULL) return -1;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (root[i]->next == NULL) {
			continue;
		}
		printf("%d:\n", i);
		Ispis(root[i]->next);
		printf("\n");
	}
}

/*PRETRAZIVANJE*/
int MatBroj(Pok *root, char *prezime)
{
	if (prezime == NULL) return -1;
	char temp[STRING_SIZE];
	int i = -1;
	strcpy(temp, prezime);
	if ((i = hash(temp)) == -1) return -1;

	return MatLista(root[i], prezime);
}

int MatLista(Pok root, char *prezime)
{
	if (root == NULL) return -1;
	root = root->next;
	while (root != NULL && strcmp(root->prezime, prezime) != 0)
	{
		root = root->next;
	}

	return (root == NULL) ? -1 : root->mat_broj;
}

/*DELETE*/

int DeleteAll(Pok *root)
{
	if (root == NULL) return -1;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		Delete(root[i]);
	}

	return 0;
}
