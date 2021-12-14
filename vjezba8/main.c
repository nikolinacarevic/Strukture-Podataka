#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Cvor* Stablo;
struct Cvor {
	int broj;
	Stablo lijevo;
	Stablo desno;
};

Stablo UnosNovogElementa(Stablo trenutni, Stablo NoviEl);
Stablo StvoriNoviElement(int x);
int BrisiElement(Stablo S, int x);
Stablo NajmanjiLijevo(Stablo trenutni);
Stablo PronadiElement(Stablo S, int x);
int Zamjeni(Stablo P1, Stablo P2);
int IspisStabla(Stablo S);
int Inorder(Stablo S);
int Preorder(Stablo S);
int Postorder(Stablo S);
int LevelOrder(Stablo S);

int main()
{
	int odabir, br;

	Stablo B = NULL;

	while (1)
	{
		printf("\nOdaberite sto zelite raditi s binarnim stablom:\n1-Unos novog elementa\n2-Ispis stabla\n3-Brisanje odredenog elementa\n4-Pronalazak odredenog elementa\n5-Kraj\n");
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
					B = UnosNovogElementa(B, Novi);
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

Stablo UnosNovogElementa(Stablo trenutni, Stablo NoviEl)
{
	if (trenutni == NULL) return NoviEl;
	if (trenutni->broj < NoviEl->broj) trenutni->desno = UnosNovogElementa(trenutni->desno, NoviEl);
	else if (trenutni->broj > NoviEl->broj) trenutni->lijevo = UnosNovogElementa(trenutni->lijevo, NoviEl);
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

int IspisStabla(Stablo S)
{
	int odabir;
	printf("\nOdaberite nacin ispisa: \n1-Inorder\n2-Preorder\n3-Postorder\n4-Level Order\n");
	if (!scanf("%d", &odabir)) printf("Pogresan unos.\n");
	else
	{
		int i = 1;
		while(i)
		{
			switch (odabir)
			{
			case 1:
			{
				Inorder(S); i = 0;
				break;
			}
			case 2:
			{
				Preorder(S); i = 0;
				break;
			}
			case 3:
			{
				Postorder(S); i = 0;
				break;
			}
			case 4:
			{
				LevelOrder(S); i = 0;
				break;
			}
			default:
			{
				printf("Krivi odabir. Pokusaj ponovno.\n");
				i = 1;
				break;
			}
			}
		}
	}
	return 0;
}

int Inorder(Stablo S)
{
	if (S == NULL) return 0;
	Inorder(S->lijevo);
	printf("%d ", S->broj);
	Inorder(S->desno);
	return 0;
}

int Preorder(Stablo S)
{
	printf("%d ", S->broj);
	Inorder(S->lijevo);
	Inorder(S->desno);
	return 0;
}

int Postorder(Stablo S)
{
	Inorder(S->lijevo);
	Inorder(S->desno);
	printf("%d ", S->broj);
	return 0;
}

int LevelOrder(Stablo S)
{


	return 0;
}

int BrisiElement(Stablo S, int x)
{
	Stablo element1 = PronadiElement(S, x);
	Stablo element2 = NajmanjiLijevo(element1);
	Zamjeni(element1, element2);
	free(element2);
	while (element1->lijevo != NULL)
	{
		element2 = NajmanjiLijevo(element1->lijevo);
		Zamjeni(element1->lijevo, element2);
		element1 = element1->lijevo;
	}
	return 0;

}


int Zamjeni(Stablo P1, Stablo P2)
{
	Stablo temp = P1;
	P1 = P2;
	P2 = temp;
	return 0;
}

Stablo NajmanjiLijevo(Stablo trenutni)
{
	while (trenutni->lijevo != NULL) trenutni = trenutni->lijevo;
	return trenutni;
}

Stablo PronadiElement(Stablo S, int x)
{
	if (S == NULL) printf("Element nije pronaden.");
	if (x == S->broj) return S;
	else if (x > S->broj) S = PronadiElement(S->desno, x);
	else S = PronadiElement(S->lijevo, x);
	return S;
}