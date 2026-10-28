#include "header.h"

#define i *(starting_index)

void floating_point_parsing(struct memory_layout_node *node, double *value, char *line, size_t *starting_index)
{
	/* no double precision floating point integer can be 
	 * larger than 16 characters (in base 10) */
	char float_string[17] = { 0 };


	while (line[i] != '\0')
	{
		if ((line[i] == ',') || 
				(line[i] == ']') ||
				 (line[i] == '}'))
		{
			break;
		}

		float_string[i] = line[i];

		i++;
	}

}
