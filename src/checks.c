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
	ptr = malloc(size);	/* allocate memory */
	if (ptr == NULL)
	{
		fprintf(stderr, "malloc() fn failed to allocated memory of size %zu on the heap\n", size);
		exit(1);
	}
}
