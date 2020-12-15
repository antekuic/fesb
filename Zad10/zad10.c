#define _CRT_SECURE_NO_WARNINGS

/* ZAD - stablo proracuna */

#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 256

typedef struct _stablo* Pok;

typedef struct _stablo {

	char El;
	int Br;
	Pok L;
	Pok D;
	Pok Next;

} Stablo;

int LoadData(Pok);
int ParsirajLiniju(Pok, char *);
int IsSymbol(char);
int push(Pok, int);
int push_symbol(Pok, char);
Pok pop(Pok);
/**/
int MakeInfix(Pok);

int main() {

	Pok root = (Pok)malloc(sizeof(Stablo));

	if (root != NULL)
	{
		root->L = NULL;
		root->D = NULL;
		root->Next = NULL;

		if (LoadData(root) == 0)
		{
			printf("Izraz je uspjesno ucitan u stablo!\n");
		}
		else return 0;

		if (MakeInfix(root) == 0)
		{
			printf("Izraz upisa u datoteku infix.txt!\n");
		}
		else return 0;;


	}
	system("pause");
	return 0;
}

/*UCITAVANJE*/
int LoadData(Pok root)
{
	if (root == NULL) return -1;

	FILE *fp = NULL;
	char buffer[256];

	fp = fopen("izraz.txt", "r");

	if (fp == NULL) return -1;

	while (fgets(buffer, BUFFER_SIZE, fp) != NULL)
	{
		ParsirajLiniju(root, buffer);

	}

	fclose(fp);
	return 0;
}

int ParsirajLiniju(Pok root, char *buffer)
{
	if (buffer == NULL) return -1;
	if (root == NULL) return -1;

	int br = 0,
		count = 0,
		i = 0;

	while (sscanf(buffer, "%d%n%*[\n]%*[\0]", &br, &count) == 1)
	{
		buffer += count;

		push(root, br); // stavi broj na cvor
		i = 0;
		while (buffer[i] != '\0' && !isdigit(buffer[i]))
		{
			if (IsSymbol(buffer[i]))
			{
				push_symbol(root, buffer[i]);

			}
			i++;
		}
		buffer += i;
	}
	return 0;
}

/* ISPIS */
int MakeInfix(Pok root)
{
	if (root == NULL) return -1;
	FILE *fp = NULL;
	char buffer[BUFFER_SIZE] = { '\0' };
	fp = fopen("infix.txt", "w");
	if (fp == NULL) return -1;


	Ispis(root->Next, buffer);
	fprintf(fp, "%s\0", buffer);
	fclose(fp);
	return 0;
}

int Ispis(Pok root, char *buffer)
{
	if (root == NULL) return -1;
	sprintf(buffer, "%s (", buffer);
	Ispis(root->L, buffer);
	if (IsSymbol(root->El)) {
		sprintf(buffer, "%s %c", buffer, root->El);
	}
	else {
		sprintf(buffer, "%s %d", buffer, root->Br);
	}
	Ispis(root->D, buffer);
	sprintf(buffer, "%s )", buffer);
	return 0;
	

}

/* pops */
int push(Pok root, int el)
{
	if (root == NULL) return -1;
	Pok temp = (Pok)malloc(sizeof(Stablo));
	if (temp == NULL) return -1;
	
	temp->Next = root->Next;
	root->Next = temp;
	temp->Br = el;
	temp->El = '\0';

	temp->L = NULL;
	temp->D = NULL;
	return 0;
}

int push_symbol(Pok root, char el)
{
	if (root == NULL) return -1;
	Pok temp = (Pok)malloc(sizeof(Stablo));
	if (temp == NULL) return -1;

	temp->D = pop(root);
	temp->L = pop(root);
	temp->El = el;

	temp->Next = root->Next;
	root->Next = temp;
	
	return 0;
}

/*POP*/

Pok pop(Pok root)
{
	if (root == NULL || root->Next == NULL) return NULL;
	Pok temp = root->Next;
	root->Next = root->Next->Next; 
	temp->Next = NULL;
	return temp;
}

/* PROVJERE */
int IsSymbol(char c)
{
	return (c >= 40 && c <= 47) ? 1 : 0;
}
