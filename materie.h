//ALEXANDRU Ioana - 314CB
//Tipul TMaterie: definiţie, afişare, alocare, eliberare

#ifndef _MATERIE_H_
#define _MATERIE_H_

typedef struct
{
	char *materie;
	int ore_curs;
	int ore_lab;
	int credit;
	int teme;
} TMaterie;

#endif

void afisare_materie(void *m, FILE *out)
{
	TMaterie mat = *((TMaterie*)m);
	fprintf(out, "[Materie: %s, Ore_curs: %d, Ore_lab: %d, Credit: %d, Teme: %d]",
				mat.materie, mat.ore_curs, mat.ore_lab, mat.credit, mat.teme);
}

TMaterie* aloca_materie(FILE *fin)
{
	TMaterie *mat = malloc(sizeof(TMaterie));
	mat->materie = malloc(20 * sizeof(char));
	fscanf(fin, "%s %d %d %d %d",
		   mat->materie, &mat->ore_curs, &mat->ore_lab, &mat->credit, &mat->teme);
	return mat;
}

void elib_materie(void *m)
{
	TMaterie *mat = (TMaterie*)m;
	free(mat->materie);
	free(mat);
}