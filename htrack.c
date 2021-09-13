#include "htrack.h"

static size_t heapsiz = 0, heaplim = 0;

size_t htrack_siz()
{
	return heapsiz;
}

size_t htrack_limit()
{
	return heaplim;
}

size_t htrack_setlimit(size_t n)
{
	assert(heapsiz <= n);
	return (heaplim = n);
}

size_t htrack_allocsiz(void *ptr)
{
	return ((size_t *)ptr)[-1];
}

void *htrack_malloc(size_t n)
{
	size_t *ptr;
	assert(n);
	n += sizeof(size_t);
	if (heaplim > 0) assert(heapsiz + n <= heaplim);
	ptr = (size_t *)malloc(n);
	heapsiz += n;
	ptr[0] = n;
	return &ptr[1];
}

void *htrack_calloc(size_t num, size_t n)
{
	size_t *ptr, psiz;
	assert(n && num);
	psiz = (num * n) + sizeof(size_t);
	if (heaplim > 0) assert(heapsiz + psiz <= heaplim);
	ptr = (size_t *)calloc(1, psiz);
	ptr[0] = psiz;
	return &ptr[1];
}

void *htrack_realloc(void *ptr, size_t n)
{
	size_t *ret, m = htrack_allocsiz(ptr);
	n += sizeof(size_t);
	if (heaplim > 0) assert(heapsiz + (-m + n) <= heaplim);
	ret = (size_t *)realloc((size_t *)ptr-1, n);
	assert(ret != NULL);
	heapsiz += (-m + n);
	ret[0] = n;
	return &ret[1];
}

void htrack_free(void *ptr)
{
	size_t n = ((size_t *)ptr)[-1];
	if (heaplim > 0) assert(heapsiz - n >= heaplim);
	heapsiz -= n;
	free((size_t *)ptr-1);
}
