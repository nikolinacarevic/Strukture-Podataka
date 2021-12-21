#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Cvor* Stablo;
struct Cvor {
	int broj;
	Stablo lijevo;
	Stablo desno;
};

typedef struct _Cvor* Pozicija;
struct _Cvor {
	int broj;
	Pozicija next;
};

Stablo Insert(Stablo trenutni, Stablo NoviEl);
Stablo StvoriNoviElement(int x);
int Zamjeni(Stablo trenutni, int suma);
int Ispis(Stablo S);
int RandomUnos(Stablo B);
int IspisUDatoteku(Stablo B);
int IzStablaUListu(Stablo B, Pozicija Lista);
int UnosUListu(Pozicija P, int br);
Pozicija StvoriElementListe(Pozicija P, int br);

int main()
{
	int niz[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	time_t t;
	int i=0, odabir=0, br=0;
	Stablo B = NULL;
	int suma = 0;

	for (i = 0; i < 10; i++)
	{
		Stablo Element = StvoriNoviElement(niz[i]);
		B = Insert(B, Element);
	}

	srand((unsigned)time(&t));

	while (1)
	{
		printf("\nOdaberite:\n1-Unos novog elementa\n2-Zamjena//SUMA\n3-Random unos novog elementa\n4-Ispis u datoteku\n5-Kraj\n");
		if (!scanf("%d", &odabir)) printf("Greska!");
		else
		{
			switch (odabir)
			{
			case 1:
			{
				printf("Unesite novi element: ");
				if (!scanf("%d", &br)) printf("Pogreška kod unosa novog elementa!\n");
				else {
					Stablo Novi = StvoriNoviElement(br);
					B = Insert(B,Novi);
				}
				break;
			}
			case 2:
			{
				Zamjeni(B, suma);
				break;
			}
			case 3:
			{
				RandomUnos(B);
				break;
			}
			case 4:
			{
				IspisUDatoteku(B);
				break;
			}
			case 5:
			{
				return 0;
			}
			default:
			{
				printf("Pogreška u odabiru!\n");
				break;
			}
			}
		}
	}

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

int Zamjeni(Stablo trenutni, int suma)
{
	if (trenutni == NULL) return 0;
	suma = trenutni->broj;
	trenutni->broj = Zamjeni(trenutni->lijevo, suma) + Zamjeni(trenutni->desno, suma);

	return suma + trenutni->broj;
}

int Ispis(Stablo S)
{
	if (S == NULL) return 0;
	Ispis(S->lijevo);
	printf("%d ", S->broj);
	Ispis(S->desno);

	return 0;
}

int RandomUnos(Stablo B)
{
	Stablo Novi = NULL;
	int i=0, br=0;

	for (i = 0; i < 10; i++)
	{
		br = (rand() % (90 - 10 + 1)) + 10;
		Novi = StvoriNoviElement(br);
		B = Insert(B, Novi);
	}

	return 0;
}

int IspisUDatoteku(Stablo B)
{
	FILE* dat=NULL;
	Pozicija Lista = NULL;
	
	IzStablaUListu(B,Lista);

	dat = fopen("ispis.txt", "w");
	if (!dat)
	{
		perror("Pogreška kod otvaranja datoteke!\n");
		return 0;
	}

	while (Lista->next != NULL)
	{
		fprintf(dat, "%d ", Lista->broj);
		Lista = Lista->next;
	}

	fclose(dat);
	
	return 0;
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

Pozicija StvoriElementListe(Pozicija P, int br)
{
	Pozicija Novi = NULL;
	Novi = (Pozicija)malloc(sizeof(struct _Cvor));

	if (Novi == NULL)
	{
		perror("Greška!\n");
		return NULL;
	}
	Novi->broj = br;
	Novi->next = NULL;

	return Novi;
}