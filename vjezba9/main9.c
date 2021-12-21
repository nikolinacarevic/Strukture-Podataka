#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct Cvor* Stablo;
struct Cvor {
	int broj;
	Stablo lijevo;
	Stablo desno;
};

Stablo Insert(Stablo trenutni, Stablo NoviEl);
Stablo StvoriNoviElement(int x);

int main()
{

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