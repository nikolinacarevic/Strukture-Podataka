#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE 128

typedef struct _student
{
    char ime[MAX_LINE];
    char prezime[MAX_LINE];
    double bodovi;
} student;

int ProcitajBrojRedaka(char* nazivDatoteke);
student* AlocirajMemorijuIProcitajStudente(int brojStudenata, char* nazivDatoteke);
double NajveciBrojBodova(student* studenti, int broj);


int main()
{
    student* Studenti = NULL;
    char nazivDatoteke[MAX_LINE] = { 0 };
    int brojStudenata = 0;
    double maxBrojBodova = 0.0;
    double relativniBodovi = 0.0;

    printf("Unesi naziv datoteke u kojoj se nalazi popis studenata: ");
    if(!scanf(" %s", nazivDatoteke)) printf("Pogresan unos\n");

    brojStudenata = ProcitajBrojRedaka(nazivDatoteke);
    Studenti = AlocirajMemorijuIProcitajStudente(brojStudenata, nazivDatoteke);
    maxBrojBodova = NajveciBrojBodova(Studenti, brojStudenata);

    for (int i = 0; i < brojStudenata; i++)
        printf("%s %s Apsolutni bodovi:%lf/30 Relativni bodovi:%lf\n", Studenti[i].ime, Studenti[i].prezime, Studenti[i].bodovi, (Studenti[i].bodovi / maxBrojBodova) * 100);

	return 0;
}

int ProcitajBrojRedaka(char* nazivDatoteke)
{
    FILE* dat = NULL;
    char buffer[MAX_LINE] = { 0 };
    int brojRedaka = 0;
    
    dat = fopen(nazivDatoteke, "r");

    if (!dat)
    {
        printf("Greska kod otvaranja datoteke!\n");
        return 0;
    }

    while (!feof(dat))
    {
        fgets(buffer, MAX_LINE, dat);
        brojRedaka++;
    }


    fclose(dat);

    return brojRedaka;
}

student* AlocirajMemorijuIProcitajStudente(int brojStudenata, char* nazivDatoteke)
{
    FILE* dat=NULL;
    int i=0;
    student* Studenti = NULL;

    dat = fopen(nazivDatoteke, "r");
    if (!dat)
    {
        printf("Greska kod otvaranja datoteke.\n");
        return 0;
    }

    Studenti = (student*)malloc(sizeof(student));

    while (!feof(dat))
    {
        if(!fscanf(dat, "%s %s %lf", Studenti[i].ime, Studenti[i].prezime, &Studenti[i].bodovi)) printf("Greska kod ucitavanja\n");
        i++;
    }
    
    return Studenti;
}

double NajveciBrojBodova(student* studenti, int broj)
{
    double max = studenti[0].bodovi;

    for (int i = 1; i < broj; i++)
        if (studenti[i].bodovi > max) max = studenti[i].bodovi;

    return max;
}