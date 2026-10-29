#include "header.h"

void floating_point_parsing(struct memory_layout_node *node, double *value, char *line, size_t *starting_index)
{
	/* no double precision floating point integer can be 
	 * larger than 16 characters (in base 10) */
	#define max_float_length 18
	char float_string[max_float_length] = { 0 };	/* 18B because we account for sign (+/-) and NULL */
	char *endptr = NULL;
	uint32_t i = 0;
	uint32_t skipped = 0;

	if (value == NULL)
	{
		fprintf(stderr, "error: cannot write to NULL pointer (floating_point_parsing())\n");
		sfree(node);
	}

	/* iterate until we get something */
	for (i = 0; (  !(isdigit(line[i])) && line[i] != '-' && line[i] != '+'  ) ; i++)
	{
		skipped++;
	}

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
