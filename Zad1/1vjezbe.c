#include <stdio.h>
#include <string.h>
/* DATOTEKA NEMA NA VRHU ISPISAN BROJ STUDENATA */
typedef struct _student* StudPok;

typedef struct _student {
	char ime[20];
	char prezime[20];
	int broj_bodova;
	StudPok next;
} Student;

StudPok DodajStudenta(StudPok, char*, int*, int *); // SLIJEDNO DODAVANJE 
int Ispis(StudPok);

int main()
{
	StudPok p = NULL;
	StudPok poc = NULL; // pocetna varijabla liste
	FILE *fp = NULL;
	int indikator = -1; // indikator varijabla
	int br_studenata = 0;
	char buffer[256]; // BUFFER ZA FGETS
	strcpy(buffer, "");
	

	fp = fopen("studenti.txt", "r");
	if (fp == NULL)
	{
		printf("Nema te datoteke.");
		return 0; // prekid programa.
	}

	// VRTI DATOTEKU, dodaje clanove, broji studente(broj redaka).
	while (!feof(fp))
	{
		if (fgets(buffer, 256, fp) != NULL)
		{
			p = DodajStudenta(p, buffer, &br_studenata, &indikator);
			if (p == NULL) {

					printf("DOGODILA SE GRESKA.");
					return 0;

			}
			if (!indikator)
			{
				poc = p; // potrebno za ispis.
			}
		}
	}

	printf("Ukupno: %d studenata.\n", br_studenata);
	// FUNKCIJA ZA ISPIS 
	if (!Ispis(poc)) {
		printf("Nema studenata!");
	}

	return 0;
}


StudPok DodajStudenta(StudPok c, char* buffer, int* br, int *ind) { // c ADRESA PRETHODNOG, buffer (linija u datoteci), br, indikator
	StudPok novi;
	novi = (StudPok)malloc(sizeof(Student));
	if (novi == NULL) // GRESKA PRI MALLOKACIJI
	{
		return NULL;
	}
	// PROVJERA JELI OVO PRVO DODAVANJE U VEZANE LISTE.
	if (c == NULL)
	{
		c = novi;
		sscanf(buffer, "%s %s %d", novi->ime, novi->prezime, &novi->broj_bodova);
		novi->next = NULL;
		*(ind) = 0;
	}
	else {
		c->next = novi;
		sscanf(buffer, "%s %s %d", novi->ime, novi->prezime, &novi->broj_bodova);
		novi->next = NULL;
		*(ind) = 1;
	}
	*(br) += 1;
	return novi;
}

int Ispis(StudPok c)
{
	if (c == NULL)
	{
		return 0;
	}

	while (c != NULL)
	{
		printf("%s %s | Broj Bodova: %d | Relativni broj bodova: %.2f%", c->ime, c->prezime, c->broj_bodova, (double)(c->broj_bodova) / 50*100);
		printf("\n");
		c = c->next;
	}
	return 1;
}
