#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MALLOC_COUNT_CHECK (mallocs_until_fail == LLONG_MAX || mallocs_until_fail-- > 0)

#define malloc(n) (MALLOC_COUNT_CHECK ? malloc2110(n) : NULL)
#define calloc(n, s) (MALLOC_COUNT_CHECK ? calloc2110(n, s) : NULL)
#define realloc(n, s) (MALLOC_COUNT_CHECK ? realloc2110(n, s) : NULL)
#define free(n) free2110(n)

extern long long mallocs_until_fail;
extern long long bytes_malloced_until_fail;
void *malloc2110(size_t);
void *calloc2110(size_t, size_t);
void *realloc2110(void *, size_t);
void free2110(void *);
