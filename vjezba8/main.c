#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Cvor* Stablo;
typedef struct Cvor {
	int broj;
	Stablo lijevo;
	Stablo desno;
};

int UnosNovogElementa(Stablo S, Stablo NoviEl);
Stablo StvoriNoviElement(int x);
int BrisiElement(Stablo S, int x);
int PronadiElement(Stablo S, int x);
int IspisStabla(Stablo S);
Stablo Inorder();
Stablo Preorder();
Stablo Postorder();
Stablo LevelOrder();

int main()
{
	int odabir,br;

	Stablo B = NULL;

	while (1)
	{
		printf("Odaberite sto zelite raditi s binarnim stablom:\n1-Unos novog elementa\n2-Ispis stabla\n3-Brisanje odredenog elementa\n4-Pronalazak odredenog elementa\n5-Kraj\n");
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
					UnosNovogElementa(B, Novi);
				}
				break;
			}
			case 2:
			{
				IspisStabla(B);
				break;
			}
			case 3:
			{
				printf("Unesite broj koji zelite izbrisati iz stabla: ");
				if (!scanf("%d", &br)) printf("Greška kod unosa elementa za brisanje!\n");
				else BrisiElement(B, br);
				break;
			}
			case 4:
			{
				printf("Unesite trazeni element: ");
				if (!scanf("%d", &br)) printf("Greška kod unosa elementa za trazenje!\n");
				else PronadiElement(B, br);
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

int UnosNovogElementa(Stablo S, Stablo NoviEl)
{
	if (S == NULL) {
		S = NoviEl; return 0;
	}
	Stablo temp;
	temp = S;
	while(temp)
	{
		if (NoviEl->broj > temp->broj) temp = temp->desno;
		else if (NoviEl->broj < temp->broj) temp = temp->lijevo;
		else { printf("Element vec postoji!\n"); return 0; }
	}
	temp->broj = NoviEl->broj;
	temp->desno = NULL;
	temp->lijevo = NULL;

	return 0;
}

Stablo StvoriNoviElement(int x)
{
	Stablo S;
	S = (Stablo)malloc(sizeof(struct Cvor));
	S->broj = x;
	S->desno = NULL;
	S->lijevo = NULL;
	return S;
}