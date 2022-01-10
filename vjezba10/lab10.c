#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#define MAX_LINE 1024

struct Cvor;
typedef struct Cvor* Pozicija;
struct _Cvor;
typedef struct _Cvor* Stablo;

typedef struct Cvor {
	char ime[MAX_LINE];
	Pozicija root;
	Pozicija next;
};

typedef struct _Cvor {
	char ime[MAX_LINE];
	int broj;
	Stablo lijevo;
	Stablo desno;
};

Stablo Insert(Stablo trenutni, Stablo NoviEl);
Stablo StvoriNoviElement(int x);
int IzStablaUListu(Stablo B, Pozicija Lista);
int Unos(Pozicija P, char* drzava, char* dat);
Pozicija StvoriElementListe(Pozicija P, char* ime);
int Pronadi(char* drzava, int brojStan, Pozicija P);
int ProcitajIzDat(Pozicija P);
int Ispis(Pozicija P);

int main()
{
	struct Cvor H = { .ime = " ", .root = NULL, .next = NULL };
	Pozicija P = &H;
	int odabir = 0;
	char drzava[MAX_LINE] = { 0 };
	Stablo S = NULL;

	ProcitajIzDat(P);
	Ispis(P->next);

	printf("Upisi ime drzave i broj stanovnika (ispisuju se gradovi s vecim brojem stanovnika od toga): ");
	scanf(" %s %d", drzava, &odabir);
	
	Pronadi(drzava, odabir, P);

	return 0;
}

Stablo Insert(Stablo trenutni, Stablo NoviEl)
{
	if (trenutni == NULL) return NoviEl;
	if (trenutni->broj < NoviEl->broj) trenutni->desno = Insert(trenutni->desno, NoviEl);
	else if (trenutni->broj > NoviEl->broj) trenutni->lijevo = Insert(trenutni->lijevo, NoviEl);
	else free(NoviEl);
	return trenutni;
}

Stablo StvoriNoviElement(int x)
{
	Stablo S;
	S = (Stablo)malloc(sizeof(struct Cvor));
	if (S == NULL) perror("Greska kod alociranja memorije.\n");
	else
	{
		S->broj = x;
		S->desno = NULL;
		S->lijevo = NULL;
		return S;
	}
	return NULL;

}

int IzStablaUListu(Stablo B, Pozicija Lista)
{
	if (B == NULL) return 0;
	IzStablaUListu(B->desno, Lista);
	UnosUListu(Lista, B->broj);
	IzStablaUListu(B->lijevo, Lista);

	return 0;
}

int Unos(Pozicija P, char *drzava, char*dat)
{
	Pozicija NoviElement = StvoriElementListe(P, br);
	NoviElement->next = P->next;
	P->next = NoviElement;

	return 0;
}

Pozicija StvoriElementListe(Pozicija P, char* ime)
{
	Pozicija Novi = NULL;
	Novi = (Pozicija)malloc(sizeof(struct _Cvor));

	if (Novi == NULL)
	{
		perror("Greška!\n");
		return NULL;
	}

	strcpy_s(Novi->ime, sizeof(Novi->ime), ime);
	Novi->next = NULL;

	return Novi;
}

int Pronadi(char* drzava, int brojStan, Pozicija P)
{

	return 0;
}

int ProcitajIzDat(Pozicija P)
{
	FILE* dat = NULL;
	char tIme[MAX_LINE] = { 0 };
	char NazivDat[MAX_LINE] = { 0 };

	dat = fopen("drzave.txt", "r");

	if (!dat)
	{
		printf("Pogreška pri otvaranju datoteke!\n");
		return -1;
	}

	while (dat != feof)
	{
		scanf("%s %s", tIme, NazivDat);
		Unos(P,tIme, NazivDat);
	}

	fclose(dat);

	return 0;
}

int Ispis(Pozicija P)
{

	return 0;
}