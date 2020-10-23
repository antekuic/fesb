#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _osoba* Pok;

typedef struct _osoba {
	char ime[30];
	char prezime[30];
	int dan, mj, god;
	Pok next;
} Osoba;

int OsobaPoc(Pok, char, char, int, int, int);
int OsobaKraj(Pok, char, char, int, int, int);
int Ispis(Pok);
int Brisanje(Pok, char);
Pok Trazi(Pok, char);

Pok ZadnjiClan(Pok);

int main()
{
	Osoba head;
	Pok c = NULL;
	
	char ime[30], prezime[30];
	int dan = 0, mj = 0, god = 0;

	//RESETIRANJE HEADA NA OBIČNO
	head.next = NULL;
	strcpy(head.ime, "");
	strcpy(head.prezime, "");
	head.dan = 0;
	head.mj = 0;
	head.god = 0;
	//
	printf("Unesite osobu za pocetak liste: ");
	scanf("%s %s %d %d %d", ime, prezime, &dan, &mj, &god);
	
	//
	if (!OsobaPoc(&head, ime, prezime, dan, mj, god))
	{
		printf("Osoba uspjesno dodana.");
	}
	else {
		printf("Dogodila se greska kod dodavanja.");
	}

	getchar(); // ZASTITA

	printf("\n");
	printf("Unesite osobu za kraj liste: ");

	scanf("%s %s %d %d %d", ime, prezime, &dan, &mj, &god);

	if (!OsobaKraj(&head, ime, prezime, dan, mj, god))
	{
		printf("Osoba uspjesno dodana.");
	}
	else {
		printf("Dogodila se greska kod dodavanja.");
	}

	getchar(); // ZASTITA
	printf("\n");

	printf("Unesite osobu za pocetak liste: ");
	scanf("%s %s %d %d %d", ime, prezime, &dan, &mj, &god);

	//
	if (!OsobaPoc(&head, ime, prezime, dan, mj, god))
	{
		printf("Osoba uspjesno dodana.");
	}
	else {
		printf("Dogodila se greska kod dodavanja.");
	}
	printf("\n");

	if (Ispis(head.next) == -1) {
		printf("Nema niti jednog clana.");
	}

	printf("\n");

	getchar(); // ZASTITA

	printf("Pretraga: ");
	scanf("%s", prezime);
	c = Trazi(head.next, prezime);
	if (c != NULL)
	{
		printf("%s %s %d/%d/%d", c->ime, c->prezime, c->dan, c->mj, c->god);
	}
	else
	{
		printf("Nije pronaden niti jedan takav clan.");
	}


	getchar(); // zastita
	
	printf("\n");

	printf("Brisanje: ");

	scanf("%s", prezime);

	if (Brisanje(&head, prezime) == -1)
	{
		printf("Dogodila se pogreska, nismo pronasli clan.");
	}

	printf("\n");

	if (Ispis(head.next) == -1) {
		printf("Nema niti jednog clana.");
	}
	getchar(); // ZASTITA
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

int OsobaPoc(Pok p, char ime[], char prezime[], int dan, int mj, int god) // 0 - tocno 1- warning -1= greska
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

			novi->dan = dan;
			novi->mj = mj;
			novi->god = god;
			return 0; // USPJESNO
		} return -1;
	}
	return -1; // GRESKA
}

int OsobaKraj(Pok p, char ime[], char prezime[], int dan, int mj, int god) // 0 - tocno 1- warning -1= greska
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

			novi->dan = dan;
			novi->mj = mj;
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

		// OVDJE JE P ADRESA CLANA KOJEG BRISEMO;
		// c adresa prethodnog clana;

		c->next = p->next;
		free(p);
		return 0;
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
			printf("%s %s %d/%d/%d\n", p->ime, p->prezime, p->dan, p->mj, p->god);
			p = p->next;
		}
		return 0;
	}
	return -1;
}