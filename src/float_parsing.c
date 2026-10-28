#include "header.h"

void floating_point_parsing(struct memory_layout_node *node, double *value, char *line, size_t *starting_index)
{
	/* no double precision floating point integer can be 
	 * larger than 16 characters (in base 10) */
	#define max_float_length 18
	char float_string[max_float_length] = { 0 };	/* 18B because we account for sign (+/-) and NULL */
	uint8_t i = 0;

	if (value == NULL)
	{
		fprintf(stderr, "error: cannot write to NULL pointer (floating_point_parsing())\n");
		sfree(node);
	}

	/* TODO iterate until we get something (like digit or sign)*/

	while (line[*starting_index] != '\0' && i < max_float_length - 1)
	{
		if ((line[*starting_index] == ',') || 
				(line[*starting_index] == ']') ||
				 (line[*starting_index] == '}'))
		{
			break;
		}

		float_string[i] = line[i];

		(*starting_index)++;
		i++;
	}

	/* strtod */
	(*value) = strtod(float_string, &endptr, 10);
	if (*endptr != NULL)
	{
		fprintf(stderr, "error: in floating_point_parsing() fn: invalid floating point integer\n");
		sfree(node);
		exit(EXIT_FAILURE);
	}
	return;
}
