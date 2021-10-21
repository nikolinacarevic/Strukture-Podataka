#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (128)
#define MAX_LINE (1024)

typedef struct _student
{
    char ime[MAX_SIZE];
    char prezime [MAX_SIZE];
    double bodovi;
} student;

int ProcitajBrojRedaka (char *nazivDat);

student* AlocirajMemorijuIProcitajStudente(int brojStudenata, char* nazivDat);

int main() 
{
    int brStudenata = 0;
    char datoteka[1024];
    student *studenti = NULL;
    int j = 0;
    int i = 0;
    double maxBrBodova = 0;
    double relativniBodovi = 0;

    printf("Upisi ime datoteke: ");
    scanf(" %s", &datoteka);

    brStudenata = ProcitajBrRedakaIzDatoteke(datoteka);
    if (brStudenata != -1)
    {
        printf("Broj studenata: %d\n", brStudenata);
    }

    studenti = AlocirajMemorijuProcitajStudente(brStudenata, datoteka);
    if (studenti != NULL)
    {
        maxBrBodova = studenti[0].bodovi;
        while (i < brStudenata)
        {
            if (studenti[i].bodovi > maxBrBodova)
            {
                maxBrBodova = studenti[i].bodovi;
            }
            i++;
        }
        while (j < brStudenata)
        {
            relativniBodovi = (studenti[j].bodovi / maxBrBodova) * 100;
            printf("\nIme: %s  Prezime: %s  Apsolutni bodovi: %lf  Relativni bodovi: %lf", studenti[j].ime, studenti[j].prezime, studenti[j].bodovi, relativniBodovi);
            j++;
        }
    }

    return 0;
}

int ProcitajBrojRedaka(char* nazivDat) 
{
    int brojac = 0; 
    FILE* dat=NULL; 
    char buffer[MAX_LINE] = {0};

    dat=fopen(nazivDat, "r");

    if (!dat) 
    { 
        printf("Greska");
        return -1;
    }

    while (!feof(dat))
    {
        fgets (buffer, MAX_LINE, dat);
        brojac++;
    }

    fclose(dat);

    return brojac;
}

student* AlocirajMemorijuIProcitajStudente(int brojStudenata, char* nazivDat)
{
    int brojac=0;
    FILE* dat=NULL; 
    student* studenti=NULL;

    studenti=(student*)malloc(brojStudenata*sizeof(student));

    dat=fopen(nazivDat,"r");

    if (!dat) 
    { 
        printf("Greska alociranja");
        free(studenti);
        return NULL;
    }
    
    while (!feof(dat))
    {
        fscanf(dat," %s %s %lf", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);
        brojac++;
    }

    fclose(dat);

    return studenti;

}