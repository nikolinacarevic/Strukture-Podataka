#define _CRT_SECURE_NO_WARNINGS
#include "peti.h"
#include <stdio.h>

Position CreateStackElement(double number)
{
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(StackElement));
	if (!newElement)
	{
		perror("Can't allocate memory!\n");
		return NULL;
	}

	newElement->number = number;
	newElement->next = NULL;

	return newElement;
}
int InsertAfter(Position position, Position newElement)
{
	newElement->next = position->next;
	position->next = newElement;
	return 0;
}

int Push(Position head, double number)
{
	Position newElement = NULL;

	newElement = CreateStackElement(number);
	if (!newElement)
	{
		return -1;
	}
	InsertAfter(head, newElement);

	return 0;

}

int DeleteAfter(Position position)
{
	Position temp = position->next;

	if (!temp)
	{
		return 0;
	}
	position->next = temp->next;
	free(temp);

	return 0;
}
int Pop(double* destination, Position head)
{
	Position first = head->next;


	if (!first)
	{
		perror("Postfix not valid! Please check your file!\n");
		return -1;
	}

	*destination = first->number;
	DeleteAfter(head);

	return 0;
}
int PerformOperation(Position head, char operation)
{
	double operand2 = 0;
	double operand1 = 0;
	int status1 = 0;
	int status2 = 0;
	double result = 0;
	status2 = Pop(&operand2, head);
	if (status2 != 0)
	{
		return -1;
	}

	status1 = Pop(&operand1, head);
	if (status1 != 0)
	{
		return -2;
	}

	switch (operation)
	{
	case '+':
	{
		result = operand1 + operand2;
		break;
	}
	case '-':
	{
		result = operand1 - operand2;
		break;
	}
	case '*':
	{
		result = operand1 * operand2;
		break;
	}
	case '/':
	{
		if (operand2 == 0)
		{
			printf("Cannot divide with zero!\n");
			return -3;
		}

		result = operand1 / operand2;
		break;
	}
	default:
		printf("This opperation is not supported yet!\n");
		return -4;

	}
	Push(head, result);
	return 0;
}

int CalculatePostfixFile(double* destination, char* fileName)
{
	FILE* file = NULL;
	int fileLength = 0;
	char* buffer = NULL;
	char* currentBuffer = NULL;
	int numBytes = 0;
	double number = 0.0;
	int operation = 0;
	int status = 0;
	StackElement head;
	file = fopen(fileName, "rb");
	if (!file)
	{
		perror("Can't open file!\n");
		return -1;
	}

	fseek(file, 0, SEEK_END);
	fileLength = ftell(file);

	buffer = (char*)calloc(fileLength + 1, sizeof(char));
	if (!buffer)
	{
		perror("Can't allocate memory!\n");
		return -1;
	}

	rewind(file);
	fread(buffer, sizeof(char), fileLength, file);
	printf("|%s|\n", buffer);
	fclose(file);
	currentBuffer = buffer;

	while (strlen(currentBuffer) > 0)
	{
		sscanf(currentBuffer, " %lf %n", &number, &numBytes);

		if (status == 1)
		{
			Push(&head, number);
			currentBuffer += numBytes;
		}
		else
		{
			status = sscanf(currentBuffer, " %c &n", &operation, &numBytes);
			status = PerformOperation(&head, operation);
			if (status != 0)
			{
				free(buffer);
				while (head.next != NULL)
				{
					DeleteAfter(&head);
				}
				return -1;
			}
			currentBuffer += numBytes;

		}
	}
	free(buffer);

	return 0;
}