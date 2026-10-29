#include "header.h"

void floating_point_parsing(struct memory_layout_node *node, double *value, char *line, size_t *starting_index)
{
	const char *p = NULL;
	char *endptr = NULL;

	if (line == NULL || starting_index == NULL || value == NULL)
	{
		return;
	}

	/* iterate until we get something */
	for (i = 0; (  !(isdigit(line[i])) && line[i] != '-' && line[i] != '+'  ) ; i++)
	{
		p++;
	}

	if (*p == '\0') {
		sfree(node);
		exit(EXIT_FAILURE);
	i = (uint32_t)(skipped);
	while (line[skipped] != '\0' && i < max_float_length - 1)
	{
		if ((line[skipped] == ',') || 
				(line[skipped] == ']') ||
				 (line[skipped] == '}'))
		{
			break;
		}

		float_string[i] = line[i];

		skipped++;
		i++;
	}

	/* strtod */
	(*value) = strtod(float_string, &endptr);
	if (*endptr != '\0')
	{
		fprintf(stderr, "error: in floating_point_parsing() fn: invalid floating point integer\n");
		printf("\n\n'%s'\n", float_string);
		sfree(node);
		exit(EXIT_FAILURE);
	}
	return;
}
