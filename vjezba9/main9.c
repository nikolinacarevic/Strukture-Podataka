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

Stablo Insert(Stablo trenutni, Stablo NoviEl);
Stablo StvoriNoviElement(int x);
int Zamjeni(Stablo trenutni, int suma);
int Ispis(Stablo S);

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
		printf("\nOdaberite:\n1-Unos\n2-Zamjena\n3-Random\n4-Ispis u datoteku\n5-Kraj\n");
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
				
				break;
			}
			case 4:
			{
				
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