#include "header.h"


void print_context(char *line, const char c, const uint16_t context_size)
{
	int i = 0;
	int udrl = 0;

	while (i < context_size && line[i] != '\0')
	{
		if (line[i] == c)
		{
			udrl = i;
		}

		putchar(line[i]);
	}
	return;
}
