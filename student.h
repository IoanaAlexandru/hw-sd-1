//ALEXANDRU Ioana - 314CB
//Tipul TStudent: definiţie, afişare, alocare, eliberare

#ifndef _STUDENT_H_
#define _STUDENT_H_

typedef struct
{
	char *nume;
	float medie;
	char grupa[6]; // 324CB + NULL
	int varsta;
} TStudent;

#endif


void afisare_student(void *s, FILE *out)
{
	TStudent stud = *((TStudent*)s);
	fprintf(out, "[Nume: %s, Grupa: %s, Medie: %.2f, Varsta: %d]",
				stud.nume, stud.grupa, stud.medie, stud.varsta);
}

TStudent* aloca_student(FILE *fin)
{
	TStudent *stud = malloc(sizeof(TStudent));
	stud->nume = malloc(20 * sizeof(char));
	fscanf(fin, "%s %f %s %d",
		   stud->nume, &stud->medie, stud->grupa, &stud->varsta);
	return stud;
}

void elib_student(void *s)
{
	TStudent *stud = (TStudent*)s;
	free(stud->nume);
	free(stud);
}