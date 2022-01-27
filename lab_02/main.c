#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE 128

struct _Cvor;
typedef struct _Cvor* Pozicija;
struct _Cvor{
	char ime[MAX_LINE];
	char prezime[MAX_LINE];
	int godinaRodenja;
	Pozicija next;
}Osoba;

int UnosNaKraj(Pozicija Head, Pozicija Novi);
int UnosNaPocetak(Pozicija Head, Pozicija Novi);
int IzbrisiElementListe(Pozicija Head, Pozicija ElementZaBrisanje);
int IspisiListu(Pozicija Head);
Pozicija TraziPrethodniElement(Pozicija Head, Pozicija P);
Pozicija TraziPoPrezimenu(char * Prezime, Pozicija Head);
Pozicija StvoriNovuOsobu(char *ime, char* prezime, int god);

int main()
{
	struct _Cvor Head = { .next = NULL,.ime = {0},.prezime = {0},.godinaRodenja = 0 };
	int odabir=0, godina=0, flag=1;
	char ime[MAX_LINE], prezime[MAX_LINE];
	Pozicija P = &Head;

	while (flag)
	{
		printf("Odaberite:\n1-UNOS NOVOG ELEMENTA NA POČETAK\n2-UNOS NOVOG ELEMENTA NA KRAJ\n3-ISPIS LISTE\n4-TRAZI OSOBU PO PREZIMENU\n5-IZBRISI ODREDENI ELEMENT\n0-IZLAZ\n");
		if (!scanf("%d", &odabir)) printf("greska\n");

		switch (odabir)
		{
		case 1:
		{
			printf("Unesi ime, prezime i godinu rodenja nove osobe (IME_PREZIME_GOD): ");
			if (!scanf(" %s %s %d", ime, prezime, &godina)) printf("greska\n");
			Pozicija Novi = StvoriNovuOsobu(ime, prezime, godina);
			UnosNaPocetak(&Head, Novi);
			break;
		}
		case 2:
		{
			printf("Unesi ime, prezime i godinu rodenja nove osobe (IME_PREZIME_GOD): ");
			if (!scanf(" %s %s %d", ime, prezime, &godina)) printf("greska\n");
			Pozicija Novi = StvoriNovuOsobu(ime, prezime, godina);
			UnosNaKraj(&Head, Novi);
			break;
		}
		case 3:
		{
			IspisiListu(&Head);
			break;
		}
		case 4:
		{
			printf("Unesi trazeno prezime: ");
			if (!scanf(" %s", prezime)) printf("greska\n");
			Pozicija Trazeni = TraziPoPrezimenu(prezime, &Head);
			printf("Podatci otrazenoj osobi:\n %s %s %d\n", Trazeni->ime, Trazeni->prezime, Trazeni->godinaRodenja);
			break;
		}
		case 5:
		{
			printf("Unesi prezime osobe za brisanje: ");
			if (!scanf(" %s", prezime)) printf("greska\n");
			Pozicija Trazeni = TraziPoPrezimenu(prezime, &Head);
			IzbrisiElementListe(&Head, Trazeni);
			break;
		}
		case 0:
		{
			flag = -1;
			break;
		}
		default:
		{
			printf("Krivi odabir, pokusaj ponovno\n");
			break;
		}
		}
	}
	return 0;
}

int UnosNaPocetak(Pozicija Head, Pozicija Novi)
{
	Novi->next = Head->next;
	Head->next = Novi;

	return 0;
}

int UnosNaKraj(Pozicija Head, Pozicija Novi)
{
	while (Head->next != NULL)
	{
		Head = Head->next;
	}
	Novi->next = Head->next;
	Head->next = Novi;

	return 0;
}

Pozicija TraziPoPrezimenu(char* Prezime, Pozicija Head)
{
	while (Head!=NULL && strcmp(Head->prezime, Prezime)!=0)
		Head = Head->next;

	if (Head == NULL)
	{
		printf("Element nije pronaden\n"); return 0;
	}

	return Head;
}

Pozicija StvoriNovuOsobu(char* ime, char* prezime, int god)
{
	Pozicija Novi=NULL;

	Novi = (Pozicija)malloc(sizeof(Osoba));
	if (!Novi)
	{
		printf("Memorija se ne moze alocirati\n");
		return 0;
	}

	strcpy(Novi->ime, ime);
	strcpy(Novi->prezime, prezime);
	Novi->godinaRodenja = god;

	return Novi;
}

Pozicija TraziPrethodniElement(Pozicija Head, Pozicija P)
{
	while (Head!= NULL && Head->next != P)
		Head = Head->next;

	if (Head == NULL)
	{
		printf("Element nije pronaden\n");
		return 0;
	}

	return Head;
}

int IzbrisiElementListe(Pozicija Head, Pozicija ElementZaBrisanje)
{
	Pozicija P = TraziPrethodniElement(Head, ElementZaBrisanje);
	if (P == NULL)
	{
		printf("Element nije obrisan\n");
		return 0;
	}

	P->next = ElementZaBrisanje->next;
	free(ElementZaBrisanje);

	return 0;
}

int IspisiListu(Pozicija Head)
{
	Head = Head->next;

	while (Head != NULL)
	{
		printf("%s %s %d\n", Head->ime, Head->prezime, Head->godinaRodenja);
		Head = Head->next;
	}

	return 0;
}