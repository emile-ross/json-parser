#include "header.h"


void print_context(char *line, const char c, const uint16_t context_size, char *message)
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
		if (j == udrl)
			printf("\033[1m^\0330");
		else
			putchar(' ');
	}

	putchar('\n');

	if (udrl != 0)
	{
		for (j = 0; j < udrl - 1; j++)
			putchar(' ');
	}

	printf("\x1b[1m %s \x1b[0m\n", message);

	return;
}
