#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<ctype.h>
#define MAX_SIZE 1024

typedef struct Cvor* Position;
typedef struct Cvor {
	char* name;
	Position sibling;
	Position child;
};

typedef struct Stog* StPozicija;
typedef struct Stog {
	Position direktorij;
	StPozicija next;
};

Position Insert(Position current, Position ne);
Position CreateNewEl(char* name);
Position FindElement(Position S);
int Pop(StPozicija head, Position current);
int Push(StPozicija head, StPozicija new);


int main()
{
	int odabir=0;
	char naziv[MAX_SIZE] = { 0 };

	Position ME;
	ME = (Position)malloc(sizeof( struct Cvor));
	ME->name = "C:";
	ME->sibling = NULL;
	ME->child = NULL;

	Position current = ME;

	printf("Odaberite:\n1-md\n2-cd dir\n3-cd..\n4-dir\n5-izlaz\n");
	if (!scanf("%d", &odabir)) printf("Pogresan unos!\n");

	while (1)
	{
		switch (odabir)
		{
		case 1:
		{
			printf("Unesi naziv novog direktorija: ");
			scanf("%s", naziv);
			Position NoviElement(naziv);
			current->child = Insert(current, NoviElement);
			break;
		}
		case 2: //cd dir
		{

			break;
		}
		case 3:
		{
			current = Pop(stog, current);
			break;
		}
		case 4:
		{
			printf("%s: \n", current->name);
			Ispisi(current);
			break;
		}
		case 5:
		{
			return 0;
		}
		default:
		{
			printf("Pogresan odabir! Pokusaj ponovno.\n");
			break;
		}
		}
	}

	return 0;
}

Position Insert(Position current, Position ne)
{
	if (!current)
		return ne;

	if (strcmp(current->name, ne->name) < 0)
		current->sibling = insert(current->sibling, ne);

	else if (strcmp(current->name, ne->name) > 0)
	{
		ne->sibling = current;
		return ne;
	}
	return current;
}

Position CreateNewEl(char* name)
{
	Position ne = NULL;
	ne = (Position)malloc(sizeof(struct Cvor));

	if (!ne)
	{
		perror("Can't allocate memory!");
		return NULL;
	}
	strcpy(ne->name, name);

	ne->sibling = NULL;
	ne->child = NULL;

	return ne;
}

int Pop(StPozicija head, Position current)
{
	StPozicija first = head->next;
	Position temp = NULL;

	if (!first)
	{
		perror("Nema roditelja!\n");
		return current;
	}
	temp = first->direktorij;
	head->next = first->next;
	free(first);
	
	return 0;
}

int Push(StPozicija head, StPozicija new)
{
	new->next = head->next;
	head->next = new;

	return 0;
}

Position FindElement(Position S)
{
	return NULL;
}
