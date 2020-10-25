#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 30

typedef struct _osoba* Pok;

typedef struct _osoba {
	char ime[MAX_STRING];
	char prezime[MAX_STRING];
	int god;
	Pok next;
} Osoba;

int OsobaPoc(Pok, char*, char*, int);
int OsobaKraj(Pok, char*, char*, int);
int Ispis(Pok);
int Brisanje(Pok, char*);
Pok Trazi(Pok, char*);
Pok ZadnjiClan(Pok);

int main()
{
	Osoba head;
	Pok c = NULL;
	char optionValue;
	char name[MAX_STRING], prezime[MAX_STRING];
	int god = 0;
	int ind = 0;
	//RESETIRANJE HEADA NA OBIČNO
	head.next = NULL;
	strcpy(head.ime, "");
	strcpy(head.prezime, "");
	head.god = 0;

	printf("Opcije: p - unos na pocetak\nk - unos na kraj\ni - ispis clanova\ne- izlazak iz programa \nUnesite opciju: ");

	while ((optionValue = getchar()) && !ind)
	{
		
		switch (optionValue)
		{
			case 'p':
			{
				printf("\n");
				printf("Unesite osobu za dodat na pocetak (ime prezime godine): ");
				scanf("%s %s %d", name, prezime, &god);
				getchar(); // zbog \n
				printf("\n");
				if (!OsobaPoc(&head, name, prezime, god))
				{
					printf("Osoba %s %s ( %d ) uspjesno dodana na pocetak.", name, prezime, god);
				}
				else {
					printf("Dogodila se greska kod dodavanja.");
				}
				printf("\n\n");
				printf("Unesite komandu: ");
				ind = 0;
				break;
			}
			case 'k': {
				printf("\n");
				printf("Unesite za dodat na kraj liste (ime prezime godine): ");
				scanf("%s %s %d", name, prezime, &god);
				getchar(); // zbog \n
				printf("\n");
				if (!OsobaKraj(&head, name, prezime, god))
				{
					printf("Osoba %s %s ( %d ) uspjesno dodana na kraj.", name, prezime, god);
				}
				else {
					printf("Dogodila se greska kod dodavanja.");
				}
				printf("\n\n");
				printf("Unesite komandu: ");
				ind = 0;
				break;
			}

			case 'i': {
				printf("\n");
				getchar(); // ZASTITA
				printf("ISPIS CLANOVA: \n");
				if (Ispis(head.next) == -1) {
					printf("Nema niti jednog clana.");
				}
				printf("\n\n");
				printf("Unesite komandu: ");
				ind = 0;

				break;

			}
			case 'f': {
				printf("\n");
				
				printf("Pretraga ( prezime ): "); 
				scanf("%s", prezime);
				getchar(); // ZASTITA
				// -> Trazenje po prezimenu
				if ((c = Trazi(head.next, prezime)) != NULL)
				{
					printf("%s %s %d", c->ime, c->prezime, c->god);
				}
				else
				{
					printf("Nije pronaden niti jedan takav clan.");
				}
				printf("\n\n");
				printf("Unesite komandu: ");
				ind = 0;

				break;

			}
			case 'b': {
				printf("\n");

				printf("Brisanje ( prezime ): ");
				scanf("%s", prezime);
				getchar(); // ZASTITA
				// -> Trazenje po prezimenu
				if (Brisanje(&head, prezime) == (-1 || 1))
				{
					printf("Dogodila se pogreska, nismo pronasli clan.");
				}
				else {
					printf("Uspjesno obrisana osoba prezimena %s", prezime);
				}

				printf("\n\n");
				printf("Unesite komandu: ");
				ind = 0;

				break;
			}
			default: { ind = 1;  printf("\nIzlazak iz programa!\n");  break; };
			}
		printf("\n");
	}

	getchar();
	return 0;
}

// TRAZENJA

Pok ZadnjiClan(Pok p) // adresa heada
{
	if (p != NULL)
	{
		while (p->next != NULL)
		{
			p = p->next;
		}

		return p;
	}
	return NULL;
}

Pok Trazi(Pok p, char prezime[]) // adresa prvog clana
{
	if (p != NULL)
	{
		while (p != NULL && strcmp(p->prezime, prezime) != 0)
		{
			p = p->next;
		}

		return p;
	}
	return NULL;
}

// DODAVANJA

int OsobaPoc(Pok p, char ime[], char prezime[], int god) // 0 - tocno 1- warning -1= greska
{
	if (p != NULL)
	{
		Pok novi = NULL;
		novi = (Pok)malloc(sizeof(Osoba));

		if (novi != NULL)
		{
			novi->next = p->next;
			p->next = novi;

			strcpy(novi->ime, ime);
			strcpy(novi->prezime, prezime);

			novi->god = god;
			return 0; // USPJESNO
		} return -1;
	}
	return -1; // GRESKA
}

int OsobaKraj(Pok p, char ime[], char prezime[], int god) // 0 - tocno 1- warning -1= greska
{
	if (p != NULL)
	{
		Pok novi = NULL;
		novi = (Pok)malloc(sizeof(Osoba));

		if (novi != NULL)
		{
			Pok c = ZadnjiClan(p); // adresa zadnjeg clana.

			c->next = novi;
			novi->next = NULL;

			strcpy(novi->ime, ime);
			strcpy(novi->prezime, prezime);

			novi->god = god;

			return 0; // USPJESNO
		} return -1;
	}
	return -1; // GRESKA
}

int Brisanje(Pok p, char prezime[]) // ADRESA HEADA
{
	if (p != NULL)
	{
		Pok c = NULL; // pomocni pokazivac
		while (p != NULL && strcmp(p->prezime, prezime) != 0)
		{
			c = p;
			p = p->next;
		}
		if (p != NULL) {
			// OVDJE JE P ADRESA CLANA KOJEG BRISEMO;
			// c adresa prethodnog clana;

			c->next = p->next;
			free(p);
			return 0;
		}
		return 1;
	}
	return -1;
}

// ISPIS
int Ispis(Pok p) // ADRESA PRVOG CLANA
{
	if (p != NULL)
	{
		while (p != NULL)
		{
			printf("%s %s %d\n", p->ime, p->prezime, p->god);
			p = p->next;
		}
		return 0;
	}
	return -1;
}
