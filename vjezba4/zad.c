#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX_LINE (1024)

struct Element;
typedef struct Element* Pozicija;
typedef struct Element {
	int koeficijent;
	int eksponent;
	Pozicija next;
};

int UnosIzDatoteke(Pozicija head1, Pozicija head2, char* imeDat);
int UnosUListu(Pozicija head, char* buffer);
int StvaranjeElementa(int koeficijent, int eksponent, Pozicija P);
int UnesiSortirano(Pozicija head, Pozicija NoviEl);
int IspisPolinoma(Pozicija head);
int ZbrajanjePolinoma(Pozicija head1, Pozicija head2, Pozicija Zbroj);
int MnozenjePolinoma(Pozicija head1, Pozicija head2, Pozicija Produkt);


int main()
{
	struct Element head1 = { .koeficijent = 0, .eksponent = 0, .next = NULL };
	struct Element head2 = { .koeficijent = 0, .eksponent = 0, .next = NULL };
	struct Element Zbroj = { .koeficijent = 0, .eksponent = 0, .next = NULL };
	struct Element Produkt = { .koeficijent = 0, .eksponent = 0, .next = NULL };

	char imeDat[MAX_LINE];

	printf("Unesi naziv datoteke: ");
	scanf(" %s", imeDat);

	UnosIzDatoteke(&head1, &head2, imeDat);

	return 0;
}

int UnosIzDatoteke(Pozicija head1, Pozicija head2, char* imeDat)
{
	FILE* dat = NULL;
	char buffer[MAX_LINE] = { 0 };

	dat = fopen(imeDat, "r");

	if (!dat)
	{
		printf("Pogreška pri otvaranju datoteke!\n");
		return -1;
	}

	fgets(buffer, MAX_LINE, dat);
	UnosUListu(head1, buffer);

	fgets(buffer, MAX_LINE, dat);
	UnosUListu(head2, buffer);

	fclose(dat);

	return 0;
}

int UnosUListu(Pozicija head, char* buffer)
{
	int koeficijent = 0, eksponent = 0, brojBtova = 0;
	Pozicija NoviElement = NULL;

	while (strlen(buffer) > 0)
	{
		sscanf(buffer, " %d %d %n", &koeficijent, &eksponent, &brojBtova);
		StvaranjeElementa(koeficijent, eksponent, NoviElement);
		UnesiSortirano(head, NoviElement);
		buffer += brojBtova;
	}
	
	return 0;
}

int StvaranjeElementa(int koeficijent, int eksponent, Pozicija P)
{
	P = (Pozicija)malloc(sizeof(struct Element));
	if (!P)
	{
		printf("Neuspješna alokacija memorije!\n");
		return -1;
	}
	P->koeficijent = koeficijent;
	P->eksponent = eksponent;

	return 0;
}

int UnesiSortirano(Pozicija head, Pozicija NoviEl)
{
	Pozicija temp = head;

	while (temp->next != NULL && temp->next->eksponent < NoviEl->eksponent)
	{
		temp = temp->next;
	}

	if (temp->next == NULL || temp->next->eksponent != NoviEl->eksponent)
	{
		NoviEl->next = temp->next;
		temp->next = NoviEl;
	}
	else
	{
		int ZbrojKoef = temp->next->koeficijent + NoviEl->koeficijent;
		temp->next->koeficijent = ZbrojKoef;
	}

	free(temp);

	return 0;
}