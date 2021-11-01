#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

struct _Person;
typedef struct _Person* Position;
typedef struct _Person{
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthYear;
    Position next;
}Person;

int PrependList(Position head,char* name,char*surname,int birthYear);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfterM(Position position, Position newPerson);
Position FindLast(Position head);
int AppendList(Position head,char* name,char*surname,int birthYear);
Position FindBySurname(Position first, char* surname);
Position FindBefore(Position head, Position position);
int Delete(Position head, char* surname);

int InsertAfter(Position position, Position newPerson, char* surname);
int InsertBefore(Position position, Position newPerson, char* surname);
int SortList(Position p);
int PrintInFile(Position p);
int ReadFromFile(Position p);


int main(int argc, char** argv)
{
    int temp=1,optn, birthYear;
    char name[MAX_SIZE],surname[MAX_SIZE], sur[MAX_SIZE];
    Person Head = { .next = NULL, .name= {0}, .surname= {0}, .birthYear = 0 };
    Position q=NULL;

    Position p = &Head;

    while (temp)
    {
        printf("Choose option:\n1-prepend a new element\n2-print list\n3-append a new element\n4-find element by surname\n5-delete element\n6-insert after\n7-insert before\n8-sort list\n9-print list in file\n10-read list from file\n11-EXIT\n->");
        scanf("%d",&optn);

        switch (optn)
		{
			case 1:
			{
				printf("name: ");
				scanf("%s", name);
				printf("surname: ");
				scanf("%s", surname);
				printf("year of birth: ");
				scanf("%d",&birthYear);
				PrependList(p, name, surname, birthYear);
				break;
			}
			case 2:
			{
				PrintList(p->next);
				break;
			}
			case 3:
			{
				printf("name: ");
				scanf("%s", name);
				printf("surname: ");
				scanf("%s", surname);
				printf("year of birth: ");
				scanf("%d",&birthYear);
				AppendList(p, name, surname, birthYear);
				break;
			}
			case 4:
			{
				printf("surname: ");
                scanf("%s",surname);
                q= FindBySurname(p->next, surname);
				if (q)
					printf("%s %s %d\n", q->name, q->surname, q->birthYear);
				else printf("No person with this surname in the list.\n");
                break;
			}
			case 5:
			{
                printf("surname: ");
				scanf("%s", surname);
				Delete(p, surname);
                break;
			}
            case 6:
            {
                printf("surname of the person after whom you want to add a new person: ");
				scanf("%s", sur);
                printf("new person info(name surname birth_year): ");
                scanf(" %s %s %d",name,surname,&birthYear);
                Position new=CreatePerson(name,surname,&birthYear);
				InsertAfter(p,new,surname);
                break;
            }
            case 7:
            {
                printf("surname of the person before whom you want to add a new person: ");
				scanf("%s", sur);
                printf("new person info(name surname birth_year): ");
                scanf(" %s %s %d",name,surname,&birthYear);
                Position new=CreatePerson(name,surname,&birthYear);
				InsertBefore(p,new,surname);
                break;
            }
            case 8:
            {
                SortList(p);
                break;
            }
            case 9:
            {
                PrintInFile(p);
                break;
            }
            case 10:
            {
                ReadFromFile(p);
                break;
            }
            case 11:
            {
                temp=0;
                break;
            }
            default:
            {
                printf("Wrong input!\n");
                break;
            }
        }   
    }
    

    return EXIT_SUCCESS;
}

Position CreatePerson(char* name, char* surname, int birthYear)
{
    Position newPerson = NULL;

    newPerson=(Position)malloc(sizeof(Person));
    if(!newPerson)
    {
        perror("Can't allocate memory!\n");
        return -1;
    }
    strcpy(newPerson->name,name);
    strcpy(newPerson->surname,surname);
    newPerson->birthYear=birthYear;
    newPerson->next = NULL;

    return newPerson;
}

int PrependList(Position head,char* name,char*surname,int birthYear)
{
    Position NewPerson=NULL;
    
    NewPerson=CreatePerson(name,surname,birthYear);

    NewPerson->next = head->next;
    head->next=NewPerson;

    return EXIT_SUCCESS;
}

int PrintList(Position first)
{
    Position temp=first;
    while(first)
    {
        printf("Name: %s, surname: %s, birth year: %d\n", temp->name,temp->surname, temp-> birthYear);
        temp = temp->next;
    }
}

int InsertAfterM(Position position, Position newPerson)
{
    newPerson->next=position->next;
    position->next=newPerson;

    return 0;
}

Position FindLast(Position head)
{
    Position temp = head;

    while (temp->next)
    {
        temp=temp->next;
    }
    return EXIT_SUCCESS;
}

int AppendList(Position head,char* name,char*surname,int birthYear)
{
    Position newPerson = NULL;
    Position last = NULL;
    newPerson=CreatePerson(name,surname,birthYear);

    if(!newPerson)
    {
        perror("Can't allocate memory!\n");
        return -1;
    }
    InsertAfterM(head,newPerson);

    return EXIT_SUCCESS;
}

Position FindBySurname(Position first, char* surname)
{
    Position temp=first;
    while(temp)
    {
        if(strcmp(temp->surname,surname) == 0)
        {
        return temp;
        }
        temp=temp->next;
    }
    return NULL;
}

Position FindBefore(Position head, Position position)
{
	Position temp = head;
	while(temp->next != position)
	{
		temp = temp->next;
	}
	return temp;
}

int Delete(Position position, char* surname)
{
    Position temp=NULL;
    position=FindBefore(position,surname);

    if(position!=NULL)
    {
            temp=position->next;
            position->next=temp->next->next;
            free(temp);
    }
    else printf("Element does not exist.\n");
}

int InsertAfter(Position position, Position newPerson, char* surname)
{
    newPerson->next=position->next;
    position->next=newPerson;

    return 0;
}

int InsertBefore(Position position, Position newPerson, char* surname)
{
    position=FindBefore(position, surname);
    newPerson->next=position->next;
    position->next=newPerson;

    return 0;
}

int PrintInFile(Position p)
{
    char fname[MAX_SIZE];
    Position temp=NULL;
    FILE *f= NULL;

    printf("file name: ");
    scanf(" %s", &fname);

    f=fopen(fname, "w");

    if (!f)
    {
        printf("Error.\n");
        return EXIT_FAILURE;
    }

    while (p!=NULL)
    {
        fprintf(f, "%s %s %d\n", p->name, p->surname, p->birthYear);
        p=p->next;
    }

    fclose(f);

    return EXIT_SUCCESS;
}

int ReadFromFile(Position p)
{
    char fname[MAX_SIZE],buffer[MAX_SIZE], name[MAX_SIZE], surname[MAX_SIZE];
    Position temp=NULL, cpy=p;
    int input=0, birthYear=0;
    FILE *f=NULL;

    printf("file name: ");
    scanf(" %s", &fname);

    f=fopen(fname, "r");

    if (!f)
    {
        printf("Error.\n");
        return EXIT_FAILURE;
    }

	while (!feof(f))
	{
		if (fgets(buffer,MAX_SIZE,f))
		{
			if (sscanf(buffer, " %s %s %d", name, surname, &birthYear) == 3)
			{
				AppendList(p, name, surname, birthYear);
			}
		}
	}

    fclose(f);

    return EXIT_SUCCESS;
}
