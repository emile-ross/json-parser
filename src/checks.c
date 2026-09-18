#include "header.h"

void file_check(FILE *file_path, const char *filename)
{
	if (file_path == NULL)
	{
		fprintf(stderr,	"file %s not found\n", filename);
		exit(1);	/*file not found */
	}
}
