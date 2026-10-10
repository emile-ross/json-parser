#include "header.h"

void *smalloc(size_t size)
{
	void *ptr = NULL;
	if (size <= 0)
	{
		fprintf(stderr, "Invalid malloc() call with size %lu\n", size);
		/* TODO free all allocated memory & exit */
		exit(EXIT_FAILURE);
	}

	ptr = malloc(size);	/* allocate memory */
	if (ptr == NULL)
	{
		fprintf(stderr, "malloc() fn failed to allocated memory of size %lu on the heap\n", size);
		/* TODO free all allocated memory & exit */
		exit(EXIT_FAILURE);
	}
	return ptr;	/* return pointer to buffer */
}

void *srealloc(void *ptr, size_t size)
{
	if (size <= 0)
	{
		fprintf(stderr, "Invalid realloc() call with size %lu\n", size);
		/* TODO free all allocated memory & exit */
		exit(EXIT_FAILURE);
	}

	ptr = realloc(ptr, size);	/* allocate memory */

	if (ptr == NULL)
	{
		fprintf(stderr, "realloc() fn failed to allocated memory of size %lu on the heap\n", size);
		/* TODO free all allocated memory & exit */
		exit(EXIT_FAILURE);
	}
	return ptr;	/* return pointer to buffer */
}
