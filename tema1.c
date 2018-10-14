//ALEXANDRU Ioana - 314CB
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#include "hash.h"
#include "chei.h"
#include "functii.h"

int main()
{
	FILE *fin = fopen("input.in", "r");
	FILE *fout = fopen("output.out", "w");
	if (!fin) {
		printf("Fişierul nu a putut fi deschis!\n");
		return -1;
	}

	char op[10], tip_cheie, tip_valoare[5];
	int nr_init_buckets, k = 0, c, nr_op, i, succes;
	TH *hash;
	void *cheie;
	void* (*citeste_cheie)(FILE*);
	TValoare *val;
	const float threshold = 0.75; float load_factor;

	fscanf(fin, "%s", op);
		
	if (!strcmp(op, "inithash")) {
		fscanf(fin, " %c%d", &tip_cheie, &nr_init_buckets);
		c = nr_init_buckets;
		if (tip_cheie == 'd') {
			hash = inithash(nr_init_buckets, hash_f, cmp_d, afis_d, elib_d, size_d);
			citeste_cheie = citeste_d;
		}
		else if (tip_cheie == 's') {
			hash = inithash(nr_init_buckets, hash_f, cmp_s, afis_s, elib_s, size_s);
			citeste_cheie = citeste_s;
		}
		else {
			printf("Tip_cheie necorespunzător!\n");
			return -1;
		}
		if (!hash) {
			printf("Iniţializarea nu a reuşit!\n");
			return -1;
		}
	}
	else {
		printf("Fişier input necorespunzător!\n");
		return -1;
	}

	fscanf(fin, "%d", &nr_op);

	for (i = 0; i < nr_op; i++) {
		fscanf(fin, "%s", op);
		if(!strcmp(op, "insert")) {
			cheie = citeste_cheie(fin);
			if (!cheie) {
				elib_hash(hash);
				printf("Eroare alocare cheie!\n");
				return -1;
			}
			fscanf(fin, "%s", tip_valoare);
			val = aloca_val(tip_valoare, fin, cheie);
			if (!val) {
				free(cheie);
				elib_hash(hash);
				return -1;
			}
			succes = inserare(hash, val, sizeof(TValoare));
			if (!succes) {
				elib_val(val, hash->felib);
				free(cheie);
				elib_hash(hash);
				printf("Inserarea nu a reuşit!\n");
				return -1;
			}
			if (succes == 1)
				k++;
			load_factor = (float)k / c;
			if (load_factor >= threshold) {
				hash = redimensionare(hash, &c);
				if (!hash) {
					printf("Redimensionarea nu a reuşit!\n");
					return -1;
				}
			}
		}
		else if (!strcmp(op, "print")) {
			afis_hash(hash, fout);
		}
		else if (!strcmp(op, "find")) {
			cheie = citeste_cheie(fin);
			if (!cheie) {
				elib_hash(hash);
				printf("Eroare alocare cheie!\n");
				return -1;
			}
			succes = cautare(hash, cheie, fout);
			if (!succes)
				fprintf(fout, "Nu exista\n");
			free(cheie);
		}
		else if (!strcmp(op, "delete")) {
			cheie = citeste_cheie(fin);
			if (!cheie) {
				elib_hash(hash);
				printf("Eroare alocare cheie!\n");
				return -1;
			}
			succes = stergere(hash, cheie, fout);
			if (succes)
				k--;
			free(cheie);
		}
	}
	elib_hash(hash);
	fclose(fin);
	fclose(fout);
	return 0;
}