//ALEXANDRU Ioana - 314CB
//Funcţii: inserare, redimensionare, căutare, ştergere

int inserare(TH *h, void *e, size_t s_e)
//0 - nu a putut fi adăugat; 1 - a fost adăugat; 2 - a înlocuit alt element
{
	int cod = h->fh(((TValoare*)e)->cheie, h->fsize(((TValoare*)e)->cheie), h->M), rez;
	TLG el;
	if (cod < 0)
		return 0;
    for(el = h->v[cod]; el != NULL; el = el->urm)
	{
		if(!h->fcmp(((TValoare*)el->info)->cheie, ((TValoare*)e)->cheie)) {
			elib_val((TValoare*)el->info, h->felib);
			el->info = e;
			return 2;
		}
	}

	rez = InsLG(h->v+cod, e, s_e);
	return rez;	
}

TH* redimensionare(TH *h, int *c)
{
	TH *newh = inithash(*c * 2, h->fh, h->fcmp, h->fafis, h->felib, h->fsize);
	if (!newh) {
		elib_hash(h);
		printf("Iniţializarea nu a reuşit!\n");
		return NULL;
	}
	int i, succes;
	TLG parcurge;
	for (i = 0; i < *c; i++) {
		parcurge = h->v[i];
		while (parcurge != NULL) {
			if (parcurge->info != NULL) {
				succes = inserare(newh, (TValoare*)(parcurge->info), sizeof(TValoare));
				if (!succes) {
					elib_hash(h);
					elib_hash(newh);
					printf("Inserarea nu a reuşit!\n");
					return NULL;
				}
			}
			parcurge = parcurge->urm;
		}
	}
	*c *= 2;
	TLG l, aux;
	for (i = 0; i < h->M; i++) {
		for (l = h->v[i]; l != NULL; l = l->urm) {
			aux = h->v[i];
			h->v[i] = h->v[i]->urm;
			free(aux);
		}
	}
	free(h->v);
	free(h);
	return newh;
}

int cautare(TH *h, void *cheie, FILE *fout)
{
	int cod = h->fh(cheie, h->fsize(cheie), h->M);
	TLG parcurge;
	parcurge = h->v[cod];
	while (parcurge != NULL) {
		if(h->fcmp(cheie, ((TValoare*)(parcurge->info))->cheie) == 0) {
			((TValoare*)(parcurge->info))->fafis(((TValoare*)(parcurge->info))->valoare, fout);
			fprintf(fout, "\n");
			return 1;
		}
		parcurge = parcurge->urm;
	}
	return 0;
}

int stergere(TH *h, void *cheie, FILE *fout)
{
	int cod = h->fh(cheie, h->fsize(cheie), h->M);
	TLG parcurge, aux;
	parcurge = h->v[cod];
	while (parcurge != NULL && parcurge->urm != NULL) {
		if(!h->fcmp(cheie, ((TValoare*)(parcurge->urm->info))->cheie)) {
			aux = parcurge->urm;
			parcurge->urm = parcurge->urm->urm;
			elib_val((TValoare*)(aux->info), h->felib);
			free(aux);
			return 1;
		}
		parcurge = parcurge->urm;
	}
	if (h->v[cod] != NULL) //primul element din listă
		if(!h->fcmp(cheie, ((TValoare*)(h->v[cod]->info))->cheie)) {
			aux = h->v[cod];
			h->v[cod] = h->v[cod]->urm;
			elib_val((TValoare*)(aux->info), h->felib);
			free(aux);
			return 1;
		}
	return 0;
}