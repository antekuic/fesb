/*Napisati program koji pomoću vezanih listi (stabala) predstavlja strukturu direktorija.
Omogućiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Točnije program treba preko menija simulirati
korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz*/


/*
prev -> pokazuje na direktorij viseg nivoa
nextDir-> pokazuje na sljedeci direktoriji u istom nivou
FirstSub->pokazuje na direktorij nizeg nivoa
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_STRING 32

typedef struct _Direktoriji* Pok;

typedef struct _Direktoriji {
	char naziv[NAME_STRING];
	Pok NextDir; // BRAT
	Pok FirstSub; // DJETE
	Pok PrevDir; // PRETHODNI DIREKTORIJ ( UNUTAR DJECE NEMA Prev )
} Direktoriji;

int MakeDir(Pok, char *);
Pok FindDir(Pok, char *);
int Ispis(Pok);
int Ispis(Pok);
int DeleteAll(Pok);

int main() {
	Pok root = NULL;
	Pok currentDir = NULL;
	Pok temp = NULL;
	int opcija = 1;
	char name[NAME_STRING] = { '\0' };
	char path[256] = { '\0' };

	root = (Pok)malloc(sizeof(Direktoriji));
	root->NextDir = NULL;
	root->FirstSub = NULL;
	root->PrevDir = NULL;
	strcpy(root->naziv, "root\0");
	if (root != NULL)
	{
		currentDir = root;
		strcat(path, "root:\\");
		while (opcija != 5)
		{
			printf("\n\n\nTrenutna putanja: %s\n", path);
			printf("\nUnesite komandu: ");
			scanf(" %d", &opcija);
			switch (opcija)
			{
			case 1:
			{
				// MAKE DIR
				printf("\nUnesite naziv direktorija kojeg zelite dodat: ");
				scanf("%s", name);
				if (MakeDir(currentDir, name) == 0)
				{
					printf("Datoteka dodana: %s%s", path, name);
				}
				break;
			}
			case 2:
			{
				// CHANGE DIR

				printf("\nUnesite naziv direktorija na kojeg zelite pokazat: ");
				scanf("%s", name);
				if ((temp = FindDir(currentDir, name)) != NULL)
				{
					printf("Datoteka pronadena. Trenutna putanja: %s%s", path, name);
					currentDir = temp;
					strcat(path, temp->naziv);
					strcat(path, "\\");
				}
				else {
					printf("Datoteka nije pronadena.");
				}
				break;
			}
			case 3: {
				// VRATI SE NAZAD
				if (currentDir->PrevDir == NULL)
				{
					printf("Nalazite se u root-u!");
				}
				else {
					path[strlen(path) - strlen(currentDir->naziv) - 1] = '\0';
					currentDir = currentDir->PrevDir;
				}
				break;
			}
			case 4: {
				// ISPISI SVE UNUTAR DIR
				printf("\n");
				printf("%s\n", currentDir->naziv);
				printf("-");
				Ispis(currentDir->FirstSub);
				break;
			}
			default:
			{
				opcija = 5;
				break;
			}
			}
		}
	}

	DeleteAll(root);
	
	return 0;
}

/*IZRADA DIREKTORIJA*/
int MakeDir(Pok root, char naziv[NAME_STRING]) { // ROOT OZNACAVA NADDIREKTORIJ I DODAJEMO DIREKTORIJ U PODDIREKTORIJ
	if (root != NULL) {
		Pok new = (Pok)malloc(sizeof(Direktoriji));

		if (new != NULL)
		{
			new->FirstSub = NULL;
			// DODAJ NA VRH
			new->PrevDir = root;
			new->NextDir = root->FirstSub;

			root->FirstSub = new;

			strcpy(new->naziv, naziv);
			return 0;
		}
	}
	return -1;
}

/* TRAZENJE */
Pok FindDir(Pok root, char naziv[NAME_STRING]) { // ROOT OZNACAVA NADDIREKTORIJ I TRAZIMO UNUTAR TOGA
	if (root != NULL) {
		root = root->FirstSub;
		if (root != NULL)
		{
			while (root != NULL && strcmp(root->naziv, naziv) != 0)
			{
				root = root->NextDir;
			}

			return root;
		}
	}
	return NULL;
}

/* ISPIS */
int Ispis(Pok root)
{
	if (root != NULL)
	{
		printf("%s", root->naziv);

		if (root->FirstSub != NULL)
		{
			printf("\\");
		}
		printf("\n");
		printf("-");
		Ispis(root->NextDir);
	}
	return -1;
}

/*BRISANJE*/
int DeleteAll(Pok root) {

	if (root != NULL)
	{
		DeleteAll(root->FirstSub);
		DeleteAll(root->NextDir);
		free(root);

	}
	return -1;
}
