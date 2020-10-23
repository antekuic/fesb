#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _osoba* Pok;

typedef struct _osoba {
	char ime[30];
	char prezime[30];
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
	//RESETIRANJE HEADA NA OBIČNO
	head.next = NULL;
	strcpy(head.ime, "");
	strcpy(head.prezime, "");
	head.god = 0;

	// -> UNOS PRVE OSOBE NA POCETAK
	if (!OsobaPoc(&head, "Jakov", "Melvan", 20))
	{
		printf("Osoba Jakov Melvan uspjesno dodana na pocetak.");
	}
	else {
		printf("Dogodila se greska kod dodavanja.");
	}

	printf("\n");

	// -> UNOS OSOBE NA KRAJ
	if (!OsobaKraj(&head, "Ante", "Kuic", 19))
	{
		printf("Osoba Ante Kuic uspjesno dodana na kraj.");
	}
	else {
		printf("Dogodila se greska kod dodavanja.");
	}

	printf("\n");

	// -> UNOS OSOBE NA POCETAK
	if (!OsobaPoc(&head, "Gojko", "Susak", 75))
	{
		printf("Osoba Gojko Susak uspjesno dodana na pocetak.");
	}
	else {
		printf("Dogodila se greska kod dodavanja.");
	}
	printf("\n");

	// -> ISPIS
	if (Ispis(head.next) == -1) {
		printf("Nema niti jednog clana.");
	}

	printf("\n");

	printf("Pretraga: ");
	// -> Trazenje po prezimenu
	if ((c = Trazi(head.next, "Kuic")) != NULL)
	{
		printf("%s %s %d", c->ime, c->prezime, c->god);
	}
	else
	{
		printf("Nije pronaden niti jedan takav clan.");
	}

	printf("\n");

	printf("Brisanje osobe prezimena Susak: ");

	if (Brisanje(&head, "Susak") == -1)
	{
		printf("Dogodila se pogreska, nismo pronasli clan.");
	}

	printf("\n");

	if (Ispis(head.next) == -1) {
		printf("Nema niti jednog clana.");
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
			printf("%s %s %d\n", p->ime, p->prezime, p->god);
			p = p->next;
		}
		return 0;
	}
	return -1;
}
