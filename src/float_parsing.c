#include "header.h"

void floating_point_parsing(const char *line, size_t *starting_index, double *value)
{
	const char *p = NULL;
	char *endptr = NULL;

	if (line == NULL || starting_index == NULL || value == NULL)
	{
		return;
	}

	/* Skip any characters that are not part of a number */
	p = line + *starting_index;
	while (*p && (!isdigit((unsigned char)*p)) && 
			(*p != '+') &&
			(*p != '-'))
	{
		p++;
	}
	/* strtod */
	(*value) = strtod(p, &endptr);

	/* set index */
	(*starting_index) = (size_t)(endptr - line);

	printf("%f\n", (*value));
}
