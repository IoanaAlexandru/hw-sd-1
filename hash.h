//ALEXANDRU Ioana - 314CB
//Tabela Hash: definiţie, iniţializare, alocare, eliberare

typedef unsigned int (*TFHash)(const void *data, size_t len, size_t range);
typedef int (*TFCmp)(void*, void*);
typedef size_t (*TFSize)(void *);

typedef struct
{
	size_t M;
	TFHash fh;
	TLG *v;
	TFCmp fcmp;
	TFAfis fafis;
	TFElib felib;
	TFSize fsize;
} TH;

unsigned int hash_f(const void *data, size_t len, size_t range)
{
	unsigned int hash = 0u;
	size_t idx = 0;
	size_t cof = 1;
	size_t rate = 2;
	const char *d = (const char*)data;
	for(; idx < len; ++idx) {
		hash += d[idx] * cof;
		cof *= rate;
	}
	return hash % range;
}

TH* inithash(size_t M, TFHash fh, TFCmp fcmp, TFAfis fafis, TFElib felib, TFSize fsize)
{
	TH *h = (TH*)calloc(sizeof(TH),1);
	if (!h) 
	{	
		printf("Eroare alocare hash!\n");
		return NULL;
	}
	h->v = (TLG*)calloc(M, sizeof(TLG));
	if(!h->v)
	{
		printf("Eroare alocare vector de pointeri TLG în hash!\n");
		free(h);
		return NULL;
	}
	h->M = M;
	h->fh = fh;
	h->fcmp = fcmp;
	h->fafis = fafis;
	h->felib = felib;
	h->fsize = fsize;
	return h;
}

void elib_hash(TH *h)
{
	int i;
	TLG aux;
	for (i = 0; i < h->M; i++) {
		while (h->v[i] != NULL) {
			aux = h->v[i];
			if (!aux)
				return;
			h->v[i] = aux->urm;
			elib_val((TValoare*)aux->info, h->felib);
			free(aux);
		}
	}
	free(h->v);
	free(h);
	h = NULL;
}

void afis_hash(TH *hash, FILE *fout)
{
	TLG l;
	int i;
	for (i = 0; i < hash->M; i++) {
		fprintf(fout, "[%d] :", i);
		for (l = hash->v[i]; l != NULL; l = l->urm) {
			fprintf(fout, " (");
			hash->fafis(((TValoare*)l->info)->cheie, fout);
			fprintf(fout, " -> ");
			((TValoare*)l->info)->fafis(((TValoare*)l->info)->valoare, fout);
			fprintf(fout, ")");
		}
		fprintf(fout, "\n");
	}
}