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

    printf("1. polinom : ");
	IspisPolinoma(&head1);

	printf("2. polinom : ");
	IspisPolinoma(&head2);

    ZbrajanjePolinoma(&head1, &head2, &Zbroj);
	printf("Zbroj polinoma : \n");
	IspisPolinoma(&Zbroj);
	
	MnozenjePolinoma(&head1, &head2, &Produkt);
	printf("Produkt polinoma : \n");
	IspisPolinoma(&Produkt);

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

int IspisPolinoma(Pozicija head)
{
	Pozicija temp = head->next;

	while (temp != NULL)
	{
		printf("%d x^%d ", temp->koeficijent, temp->eksponent);
		temp = temp->next;
	}

    printf("\n");

	return 0;
}

int ZbrajanjePolinoma(Pozicija head1, Pozicija head2, Pozicija Zbroj)
{
	Pozicija temp = head1->next;

	while (temp != NULL)
	{
		UnesiSortirano(Zbroj, temp);
		temp = temp->next;
	}

	temp = head2->next;

	while (temp != NULL)
	{
		UnesiSortirano(Zbroj, temp);
		temp = temp->next;
	}

	return 0;
}

int MnozenjePolinoma(Pozicija head1, Pozicija head2, Pozicija Produkt)
{
	Pozicija temp1 = head1->next;
	Pozicija temp2 = head2->next;

	while (temp1 != NULL)
	{
		while (temp2 != NULL)
		{
            Pozicija Novi;
			StvaranjeElementa(temp1->koeficijent * temp2->koeficijent, temp1->eksponent + temp2->eksponent, Novi);
			UnesiSortirano(Produkt, Novi);
			temp2 = temp2->next;
		}
		temp1 = temp1->next;
	}

	return 0;
}