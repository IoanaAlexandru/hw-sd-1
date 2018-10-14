//ALEXANDRU Ioana - 314CB
//Chei (întregi şi şiruri de caractere): funcţii de citire, comparare, afişare,
//eliberare, şi pentru aflarea dimensiunii

void* citeste_d(FILE *fin)
{
	void *cheie = (int*)malloc(sizeof(int));
	fscanf(fin, "%d", (int*)cheie);
	return cheie;
}

int cmp_d(void *p1, void *p2)
{
	return *((int*)p1) - *((int*)p2);
}

void afis_d(void *p, FILE *fout)
{
	fprintf(fout, "%d", *((int*)p));
}

void elib_d(void *p)
{
	free((int*)p);
}

size_t size_d(void *p)
{
	return sizeof(int);
}

void* citeste_s(FILE *fin)
{
	void *cheie = (char*)malloc(50 * sizeof(char));
	fscanf(fin, "%s", (char*)cheie);
	return cheie;
}

int cmp_s(void *p1, void *p2)
{
	return strcmp((char*)p1, (char*)p2);
}

void afis_s(void *p, FILE *fout)
{
	fprintf(fout, "%s", (char*)p);
}

void elib_s(void *p)
{
	free((char*)p);
}

size_t size_s(void *p)
{
	return strlen((char*)p);
}