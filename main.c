#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	/* no type safety for the input since this will later be 
	 * implemented as a function
	 * for now this simply assumes the user has all power */

	char *file_path = argv[1];
	FILE *fp = fopen(file_path, "r");

	if (fp == NULL)
	{
		fprintf(stderr, "file not found \n");
		return 1;	/*file not found */
	}

	do {
		char line[512];
		uint16_t line_size = sizeof(line);

		if (fgets(line, line_size, fp) != NULL)
		{
			printf("%s\n", line);
		}
	} while (1);


	return 0;
}
