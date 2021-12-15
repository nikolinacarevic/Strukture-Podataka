#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<ctype.h>

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
	int i = 1;
	Position ME;
	ME = (Position)malloc(sizeof( struct Cvor));
	ME->name = "C:";
	ME->sibling = NULL;
	ME->child = NULL;

	Position current = ME;

	char* ulaz, buffer;
	ulaz = (char*)malloc(sizeof(char));
	scanf("%[\n]s", ulaz);

	while (i)
	{
		if (strcmp(ulaz, "md") == 0) {

		}
		else if (strcmp(ulaz, "cd dir") == 0)
		else if (strcmp(ulaz, "cd..") == 0)
		else if (strcmp(ulaz, "dir") == 0)
		else if (strcmp(ulaz, "exit") == 0) i = 0;
		else
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
