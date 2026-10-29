#include "header.h"

void floating_point_parsing(struct memory_layout_node *node, const char *line, size_t *starting_index, double *value)
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

	if (*p == '\0')
	{
		sfree(node);
		exit(EXIT_FAILURE);
	}

	/* strtod */
	(*value) = strtod(p, &endptr);

	if (endptr == p)
	{
		fprintf(stderr, "error: in floating_point_parsing() fn: invalid floating point integer\n");
		/* print the ending of the line */
		printf("\n\n'%s'\n", line + *starting_index);
		sfree(node);
		exit(EXIT_FAILURE);
	}
	/* set index */
	(*starting_index) = (size_t)(endptr - line);

	printf("%f\n", (*value));
	return;
}
