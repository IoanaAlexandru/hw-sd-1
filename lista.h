//ALEXANDRU Ioana - 314CB
//Lista Generică şi conţinutul ei: definiţie, afişare, alocare, eliberare

#include "materie.h"
#include "student.h"

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef struct celulag
{
  void *info;
  struct celulag *urm;
} TCelulaG, *TLG, **ALG;

#endif

typedef void (*TFAfis)(void *valoare, FILE *file);
typedef void (*TFElib)(void *p);

typedef struct
{
	void *valoare, *cheie;
	TFAfis fafis;
	TFElib felib;
} TValoare;

int InsLG(ALG aL, void* ae, size_t d) //inserare celulă în listă
{
	TLG aux = malloc(sizeof(TCelulaG));
	if(!aux)
		return 0;
	aux->info = ae;
	aux->urm = NULL;
	TLG p = *aL, ultim = NULL;
	while (p != NULL) {
		ultim = p;
		p = p->urm;
	}
	if (ultim)
		ultim->urm = aux;
	else
		*aL = aux;
	return 1;
}

TValoare* aloca_val(char tip_valoare[5], FILE *fin, void *cheie)
{
	TValoare *val = malloc(sizeof(TValoare));
	if (!val) {
		printf("Alocarea valorii nu a reuşit!");
		return NULL;
	}
	if (!strcmp(tip_valoare, "stud")) {
		TStudent *stud = aloca_student(fin);
		if (!stud) {
			printf("Alocarea valorii student nu a reuşit!");
			return NULL;
		}
		val->valoare = stud;
		val->cheie = cheie;
		val->fafis = afisare_student;
		val->felib = elib_student;
	}
	else if (!strcmp(tip_valoare, "mat")) {
		TMaterie *mat = aloca_materie(fin);
		if (!mat) {
			printf("Alocarea valorii materie nu a reuşit!");
			return NULL;
		}
		val->valoare = mat;
		val->cheie = cheie;
		val->fafis = afisare_materie;
		val->felib = elib_materie;
	}
	else {
		printf("Tip_valoare necorespunzător!\n");
		return NULL;
	}
	return val;
}

void elib_val (TValoare *val, TFElib felib_cheie)
{
	felib_cheie(val->cheie);
	val->felib(val->valoare);
	free(val);
}