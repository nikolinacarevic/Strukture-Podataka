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

Position Insert(Position current, Position ne);
Position CreateNewEl(char* name);
Position FindElement(Position S);
int Pop(double* destination, Position S);


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
	case 2:
	{

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
		break;
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

int Pop(char* destination, Position S)
{
	Position first = S->child;


	if (!first)
	{
		perror("Perror!\n");
		return -1;
	}

	*destination = first->name;
	DeleteAfter(S);

	return EXIT_SUCCESS;
}

Position FindElement(Position S)
{
	return NULL;
}
