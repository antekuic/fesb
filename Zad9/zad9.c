/* Napisati program koji omogućava rad s binarnim stablom pretraživanja. Treba
omogućiti unošenje novog elementa u stablo, ispis elemenata, brisanje i pronalaženje
nekog elementa
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct _stablo* Pok;

typedef struct _stablo {
	
	int El;
	Pok L;
	Pok D;

} Stablo;

Pok Dodaj(Pok, int);
Pok Trazi(Pok, int);
Pok Brisanje(Pok, int);
Pok TraziMax(Pok);
int Ispisivanje(Pok, int);
int OcistiStablo(Pok);

int main() {

	int opcija = 1,
		var = 0;

	Pok root = (Pok)malloc(sizeof(Stablo));
	
	if (root != NULL) {
		root->L = NULL;
		root->D = NULL;
		while (opcija)
		{
			printf("\n1-Unos u stablo\n2-Brisanje\n3-Ispis\n4-Pronadi");
			printf("\nUnesite komandu: ");
			scanf(" %d", &opcija);
			switch (opcija)
			{
				case 1:
				{
					// UNOS
					printf("\nUnesite vrijednost koju zelite dodat u stablo:");
					scanf(" %d", &var);
					if ((root->D = Dodaj(root->D, var)) == NULL)
					{
						printf("\nDogodila se pogreska!.");
					}
					else {
						printf("\nElement %d uspjesno dodan u stablo.", var);
					}
					break;
				}
				case 2:
				{
					// BRISANJE
					scanf(" %d", &var);
					if ((root->D = Brisanje(root->D, var)) == NULL)
					{
						printf("\nDogodila se pogreska!.");
					}
					else {
						printf("\nElement %d uspjesno izbrisan iz stabla.", var);
					}
					break;
				}
				case 3: {
					// ISPIS
					Ispisivanje(root->D, 0);
					break;
				}
				case 4: {
					// PRONADI
					printf("\nUnesite vrijednost koju zelite traziti u stablu:");
					scanf(" %d", &var);
					if (Trazi(root->D, var) == NULL)
					{
						printf("Taj element ne postoji u stablu.\n");
					}
					else {
						printf("Pronasli smo element.\n");

					}
					break;
				}
				default:
				{
					opcija = 0;
					break;
				}
			}
		}
	}

	OcistiStablo(root->D);
	return 0;
}
/* DODAVANJE >*/
Pok Dodaj(Pok root, int el)
{
	if (root == NULL)
	{
		root = (Pok)malloc(sizeof(Stablo));
		root->El = el;
		root->L = NULL;
		root->D = NULL;
	}
	else {
		if (el < root->El)
		{
			root->L = Dodaj(root->L, el);
		}
		else if(el > root->El) {
			root->D = Dodaj(root->D, el);
		}
	}
	return root;
}
/* TRAZENJE */
Pok Trazi(Pok root, int el)
{
	if (root != NULL) {
		if (el == root->El) return root;
		if (el < root->El)
		{
			return Trazi(root->L, el);
		}
		else {
			return Trazi(root->D, el);
		}
	}
	return root;
}

/*BRISANJE*/
Pok Brisanje(Pok root, int el) // ELEMENT KOJEG TRIBA OBRISAT
{
	if (root == NULL) return root;

	if (root->El > el)
		root->L = Brisanje(root->L, el);
	else if (root->El < el)
		root->D = Brisanje(root->D, el);

	else {

		if (root->L == NULL)
		{
			Pok temp = root->D;
			free(root);
			return temp;
		}
		else if (root->D == NULL)
		{
			Pok temp = root->L;
			free(root);
			return temp;
		}
		else {
			// IMAMO DVA DJETETA
			Pok temp = TraziMax(root->L);
			root->El = temp->El;
			root->L = Brisanje(root->L, temp->El);
		}
	}
	return root;
}

/*TRAZI MAX*/

Pok TraziMax(Pok root)
{
	while (root->D != NULL)
	{
		root = root->D;
	}

	return root;
}

/*ISPISIVANJE*/

int Ispisivanje(Pok root, int razmak)
{
	if (root == NULL)
		return 0;

	razmak += 10;

	Ispisivanje(root->D, razmak);

	printf("\n");
	for (int i = 10; i < razmak; i++)
			printf(" ");

	printf("%d\n", root->El);

	Ispisivanje(root->L, razmak);
	return 0;
}

/* BRISI SVE */

int OcistiStablo(Pok root)
{
	if (root == NULL)
		return 0;
	OcistiStablo(root->L);
	OcistiStablo(root->D);
	free(root);
	return 0;
}
