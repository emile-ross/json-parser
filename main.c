#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum
{
	False = 0,
	True = 1
} Bool;

int main(int argc, char *argv[])
{
	/* no type safety/memory safety for the input since this will 
	 * later be implemented as a function without user input
	 * for now this simply assumes the user has all power */

	char *file_path = argv[1];	/* will segfault if missing args */
	FILE *fp = fopen(file_path, "r");
	char line[256] = {0};	/* used for storing the line buffer in the file */

	if (argc < 2)
	{
		fprintf(stderr, "Missing arguments in command\n");
	}

	if (fp == NULL)
	{
		fprintf(stderr, "file not found \n");
		return 1;	/*file not found */
	}

	do {
		uint16_t line_size = sizeof(line);

		if (fgets(line, line_size, fp) != NULL)
		{
			printf("%s\n", line);
		}
	} while (1);


	return 0;
}
