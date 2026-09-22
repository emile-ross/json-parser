#include "header.h"

void file_check(FILE *file_path, const char *filename)
{
	if (file_path == NULL)
	{
		fprintf(stderr,	"file %s not found\n", filename);
		exit(1);	/*file not found */
	}
}

void *smalloc(size_t size)
{
	void *ptr = NULL;
	if (size <= 0)
	{
		fprintf(stderr, "Invalid malloc() call with size %zu\n", size);
		exit(1);
	}

	ptr = malloc(size);	/* allocate memory */
	if (ptr == NULL)
	{
		fprintf(stderr, "malloc() fn failed to allocated memory of size %zu on the heap\n", size);
		exit(1);
	}
	return ptr;
}
