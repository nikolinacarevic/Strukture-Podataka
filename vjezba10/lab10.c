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
int UnosUListu(Pozicija P, int br);
Pozicija StvoriElementListe(Pozicija P, int br);
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

int UnosUListu(Pozicija P, int br)
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

Pozicija StvoriElementListe(Pozicija P, int br)
{

	return 0;
}

int Pronadi(char* drzava, int brojStan, Pozicija P)
{

	return 0;
}

int ProcitajIzDat(Pozicija P)
{

	return 0;
}

int Ispis(Pozicija P)
{

	return 0;
}