#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX_LINE 1024

struct Element;
typedef struct Element* Pozicija;

struct Element {
	int koeficijent;
	int eksponent;
	Pozicija next;
};

int UnosIzDatoteke(Pozicija head1, Pozicija head2, char* imeDat);
Pozicija StvoriNoviElement(int koeficijent, int eksponent);
int UnesiSortirano(Pozicija head, Pozicija NoviEl);
int IspisPolinoma(Pozicija head);
int ZbrajanjePolinoma(Pozicija head1, Pozicija head2, Pozicija Zbroj);
int MnozenjePolinoma(Pozicija head1, Pozicija head2, Pozicija Produkt);

int main()
{
	struct Element p1, p2, zbroj, produkt;
	char imeDat[50];

	printf("Unesi ime datoteke: ");
	if (!scanf(" %s", imeDat)) { printf("Pogresan unos\n"); return 0; }
	UnosIzDatoteke(&p1, &p2, imeDat);

	ZbrajanjePolinoma(&p1, &p2, &zbroj);
	MnozenjePolinoma(&p1, &p2, &produkt);

	printf("Prvi polinom: ");
	IspisPolinoma(&p1);
	printf("\n");

	printf("Drugi polinom: ");
	IspisPolinoma(&p2);
	printf("\n");

	printf("Zbroj: ");
	IspisPolinoma(&zbroj);
	printf("\n");

	printf("Produkt: ");
	IspisPolinoma(&produkt);
	printf("\n");

	return 0;
}

int UnosIzDatoteke(Pozicija head1, Pozicija head2, char* imeDat)
{
	FILE* dat;
	char buffer[MAX_LINE];
	int n,koef,eksponent;
	char* buffer2 = NULL;

	dat = fopen(imeDat, "r");
	if (!dat) { printf("Greska kod otvaranja dat\n"); return -1; }

	fgets(buffer, MAX_LINE, dat);
	while (strlen(buffer) > 0)
	{
		if (sscanf(buffer2, " %d %d %n", &koef, &eksponent, &n) == 2)
		{
			Pozicija Novi = StvoriNoviElement(koef, eksponent);
			UnesiSortirano(head1, Novi);
		}
		buffer2 = buffer2 + n;
	}

	fgets(buffer, MAX_LINE, dat);
	while (strlen(buffer) > 0)
	{
		if (sscanf(buffer2, " %d %d %n", &koef, &eksponent, &n) == 2) // %n = koliko smo bitova procitali
		{
			Pozicija Novi = StvoriNoviElement(koef, eksponent);
			UnesiSortirano(head1, Novi);
		}
		buffer2 = buffer2 + n;
	}

	fclose(dat);

	return 0;
}

int UnesiSortirano(Pozicija head, Pozicija Novi)
{
	while (head->next != NULL && (head->next->eksponent) > Novi->eksponent)
		head = head->next;
	
	if (head->next != NULL && (head->next->eksponent) == Novi->eksponent)
	{
		head->next->koeficijent = head->next->koeficijent + Novi->koeficijent;
		if (head->next->koeficijent == 0)
		{
			Pozicija temp = NULL;
			temp = head->next;
			head->next = temp->next;
			free(temp);
		}
	}
	
	return 0;
}

Pozicija StvoriNoviElement(int koeficijent, int eksponent)
{
	Pozicija Novi = NULL;

	Novi = (Pozicija)malloc(sizeof(struct Element));
	Novi->eksponent = eksponent;
	Novi->koeficijent = koeficijent;

	return Novi;
}

int IspisPolinoma(Pozicija head)
{
	while (head != NULL)
	{
		printf("%dx^(%d)", head->koeficijent, head->eksponent);
		if (head->next != NULL)
			printf(" + ");
		head = head->next;
	}
	printf("\n");

	return 0;
}

int ZbrajanjePolinoma(Pozicija head1, Pozicija head2, Pozicija Zbroj)
{
	Pozicija temp;

	while (head1 != NULL && head2 != NULL) 
	{
		if (head1->eksponent == head2->eksponent) 
		{
			Pozicija Novi = StvoriNoviElement(head1->koeficijent + head2->koeficijent, head1->eksponent);
			UnesiSortirano(head1, Novi);
			head1 = head1->next; 
			head2 = head2->next;
		}
		else if (head1->eksponent > head2->eksponent) 
		{
			Pozicija Novi = StvoriNoviElement(head1->koeficijent, head1->eksponent);
			UnesiSortirano(Zbroj, Novi);
			head1 = head1->next;
		}
		else 
		{
			Pozicija Novi = StvoriNoviElement(head2->koeficijent, head2->eksponent);
			UnesiSortirano(Zbroj, Novi);
			head2 = head2->next;
		}
	}

	if (head1 != NULL) temp = head1;
	else temp = head2;

	while (temp != NULL) 
	{
		Pozicija Novi = StvoriNoviElement(temp->koeficijent, temp->eksponent);
		UnesiSortirano(Zbroj, Novi);
		temp = temp->next;
	}

	return 0;
}

int MnozenjePolinoma(Pozicija head1, Pozicija head2, Pozicija Produkt)
{
	Pozicija temp = head2;
	Pozicija element = NULL;

	while (head1 != NULL)
	{
		head2 = temp;
		while (head2 != NULL)
		{
			Pozicija Novi = StvoriNoviElement(head1->koeficijent * head2->koeficijent, head1->eksponent + head2->eksponent);
			UnesiSortirano(Produkt, Novi);
			head2 = head2->next;
		}
		head1 = head1->next;
	}

	return 0;
}