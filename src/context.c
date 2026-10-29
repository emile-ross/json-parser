#include "header.h"


void print_context(char *line, const char c, const uint16_t context_size)
{
	uint32_t i = 0;
	uint32_t j = 0;
	uint32_t udrl = 0;

	while (i < context_size && line[i] != '\0')
	{
		if (line[i] == c)
		{
			udrl = i;
		}

		putchar(line[i]);
		i++;
	}

	putchar('\n');

	for (j = 0; j < i; j++)
	{
		putchar(' ');
		if (j == udrl)
			putchar(line[i]);
	}

	putchar('\n');

	return;
}
