#define _CRT_SECURE_NO_WARNINGS

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
	Pok prev; // PRIPREMA ZA BRZI SORT
} Osoba;

// DODAVANJEO
int OsobaPoc(Pok, char*, char*, int);
int OsobaKraj(Pok, char*, char*, int);
int UnosIza(Pok, char *); // Dodavanje iza.
int UnosPrije(Pok, char *);
// ISPISIVANJE
int Ispis(Pok);
// BRISANJE
int Brisanje(Pok, char*);
// PRETRAGE
Pok Trazi(Pok, char*); // adresa tog clana.
Pok ZadnjiClan(Pok);
Pok TraziPret(Pok, char *);
// ALGORITAM ZA SORTIRANJE
int Sort(Pok);
Pok Exchange(Pok, Pok, int *);
//DATOTEKA
int UpisDatoteka(Pok);
int UcitavanjeDatoteka(Pok, char *);

int main()
{
	Osoba head;
	Pok c = NULL;
	char optionValue;
	char name[MAX_STRING], prezime[MAX_STRING];
	int god = 0;
	int ind = 0;
	int a = 0;
	//RESETIRANJE HEADA NA OBIČNO
	head.next = NULL;
	head.prev = NULL;
	strcpy(head.ime, "");
	strcpy(head.prezime, "");
	head.god = 0;

	printf("Opcije: p - unos na pocetak\nk - unos na kraj\ni - ispis clanova\nf - pretraga po prezimenu\nb - brisanje po prezimenu\ne- izlazak iz programa \n");
	printf("a - unos iza odredenog clana\nz - unos prije odredenog clana\ns- Za sortiranje po prezimenu\nr-Za citanje iz datoteke\nw - za upisivanje u datoteku.\nUnesite opciju: ");

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
		case 'a': { // UNOS IZA ODREDENOG CLANA
			printf("\n");
			printf("Unesite prezime clana iza kojeg zelite dodat novog clana\n( napomena: Ukoliko taj clan ne postoji dodat ce se na kraj ): ");
			scanf("%s", prezime);
			getchar(); // ZASTITA
			// -> Trazenje po prezimenu
			if ((a = UnosIza(&head, prezime)) == 0) {
				printf("Clan uspjesno dodan iza %s.", prezime);
			}
			else if (a) {
				printf("Nismo pronasli tog clana, osoba je dodana na kraj.");
			}
			else {
				printf("Dogodila se pogreska!");
			}
			printf("\n\n");
			printf("Unesite komandu: ");
			ind = 0;

			break;
		}
		case 'z': { // UNOS IZA ODREDENOG CLANA
			printf("\n");
			printf("Unesite prezime clana prije kojeg zelite dodat novog clana\n( napomena: Ukoliko taj clan ne postoji dodat ce se na kraj ): ");
			scanf("%s", prezime);
			getchar(); // ZASTITA
			// -> Trazenje po prezimenu
			if ((a = UnosPrije(&head, prezime)) == 0) {
				printf("Clan uspjesno dodan prije %s.", prezime);
			}
			else {
				printf("Dogodila se pogreska!");
			}
			printf("\n\n");
			printf("Unesite komandu: ");
			ind = 0;

			break;
		}
		case 's': {
			getchar();
			if (!Sort(&head)) {
				if (Ispis(head.next) == -1) {
					printf("Nema niti jednog clana.");
				}
			}
			else {
				printf("Dogodila se greska prilikom sortiranja.");
			}
			printf("\n\n");
			printf("Unesite komandu: ");
			ind = 0;
			break;
		}
		case 'w': {
			getchar();
			printf("\n");
			if (UpisDatoteka(head.next) == -1) {
				printf("Dogodila se greska.");
			}
			else {
				printf("Kreirana datoteka studnet-upis.txt.");
			}
			printf("\n\n");
			printf("Unesite komandu: ");
			ind = 0;
			break;
		}
		case 'r': {
			getchar();
			printf("\n");
			printf("Unesite ime datoteke iz koje zelite ucitati: (.txt) "); // DODAJE SE POSTOJECEM FOLDERU
			scanf("%s", prezime);
			getchar(); // ZASTITA
			if (UcitavanjeDatoteka(&head, prezime) == -1) {
				printf("Dogodila se greska.");
			}
			else {
				printf("Podatci ucitani iz datoteteke %s.", prezime);
			}
			printf("\n\n");
			printf("Unesite komandu: ");
			ind = 0;
			break;
		}
		default: { ind = 1;  printf("\nIzlazak iz programa!\n");



			break; };
		}
		printf("\n");
	}



	free(c);
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

Pok TraziPret(Pok p, char prezime[]) // adresa head clana
{
	if (p != NULL)
	{
		while (p->next != NULL && strcmp(p->next->prezime, prezime) != 0)
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
			if (p->next != NULL) {
				p->next->prev = novi;
			}

			p->next = novi;
			novi->prev = p;

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

			novi->next = c->next;
			c->next = novi;
			novi->prev = c;


			strcpy(novi->ime, ime);
			strcpy(novi->prezime, prezime);

			novi->god = god;

			return 0; // USPJESNO
		} return -1;
	}
	return -1; // GRESKA
}

int UnosIza(Pok p, char sur[]) { // adresa heada

	if (p != NULL) {
		char ime[30], prezime[30];
		int god = 0;
		Pok c = NULL;
		printf("Unesite ime prezime god novog clana: ");
		scanf("%s %s %d", ime, prezime, &god);
		getchar(); // zastita
		if ((c = Trazi(p->next, sur)) != NULL) {
			Pok novi = NULL;
			novi = (Pok)malloc(sizeof(Osoba));
			if (novi != NULL)
			{
				strcpy(novi->ime, ime);
				strcpy(novi->prezime, prezime);
				novi->god = god;

				novi->next = c->next;
				c->next = novi;
				novi->prev = c;
				if (novi->next != NULL) {
					novi->next->prev = novi;
				}
				return 0;
			}
			else return -1;

		}
		else {
			if (!OsobaKraj(p, ime, prezime, god)) return 1; // WARNING DODAN JE NA KRAJ
			else return -1;
		}

	}
	return -1;
}

int UnosPrije(Pok p, char sur[]) { // adresa heada

	if (p != NULL) {
		Pok c = NULL;
		char ime[30], prezime[30];
		int god = 0;
		printf("Unesite ime prezime god novog clana: ");
		scanf("%s %s %d", ime, prezime, &god);
		getchar(); // zastita
		if ((c = TraziPret(p, sur)) != NULL) {
			Pok novi = NULL;
			novi = (Pok)malloc(sizeof(Osoba));
			if (novi != NULL)
			{
				strcpy(novi->ime, ime);
				strcpy(novi->prezime, prezime);
				novi->god = god;

				novi->next = c->next;
				c->next = novi;
				novi->prev = c;
				if (novi->next != NULL) {
					novi->next->prev = novi;
				}
				return 0;
			}
			else return -1;

		}
		else {
			if (!OsobaKraj(p, ime, prezime, god)) return 1; // WARNING DODAN JE NA KRAJ
			else return -1;
		}

	}
	return -1;
}
// BRISANJE

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
			p->next->prev = c;
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
			printf("%s %s %d (%p %p %p)\n", p->ime, p->prezime, p->god, p->prev, p, p->next);
			p = p->next;
		}
		return 0;
	}
	return -1;
}
int Sort(Pok p) { // ADRESA HEAD CLANA

	if (p != NULL) {
		if (p->next != NULL)
		{
			int swapt = 0;
			Pok temp = p;
			p = p->next;
			do {
				swapt = 0;
				while (p->next != NULL) {
					p = Exchange(p, p->next, &swapt);
				}
				p = temp->next;
			} while (swapt);
			return 0;
		}

		return -1;
	} return -1;

}

Pok Exchange(Pok p1, Pok p2, int *c) // razmjeni dvi adrese  i vrati onu koja je visa(next)
{
	if (p1 != NULL && p2 != NULL)
	{
		Pok temp = NULL;
		if (strcmp(p1->prezime, p2->prezime) > 0) {
			p1->prev->next = p2;
			p2->prev = p1->prev;

			p1->prev = p2;
			temp = p2->next;
			p2->next = p1;
			p1->next = temp;
			if (temp != NULL)
			{
				temp->prev = p1;
			}
			*(c) = 1;
			return p1; // VRATI P1
		}
		else return p2;
	}
	else return p2;
}

// RAD S DATOTEKAMA

int UpisDatoteka(Pok p) // prvi element 
{
	if (p != NULL)
	{
		FILE *f = NULL;
		f = fopen("student-upis.txt", "w");
		if (f != NULL) {
			while (p != NULL) {
				fprintf(f, "%s %s %d\n", p->ime, p->prezime, p->god);
				p = p->next;
			}
			fclose(f);
			return 0;
		}
		return -1;
	}
	return -1;
}

int UcitavanjeDatoteka(Pok p, char naziv[]) // adresa heada
{
	if (p != NULL)
	{
		FILE *f = NULL;
		char ime[30], prezime[30];
		int god = 0;
		f = fopen(naziv, "r");
		if (f != NULL) {
			while (!feof(f)) {
				fscanf(f, "%s %s %d", ime, prezime, &god);
				if (OsobaKraj(p, ime, prezime, god) != 0) {
					break;
				}
			}
			fclose(f);
			return 0;
		}
		return -1;
	}
	return -1;
}
