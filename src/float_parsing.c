#include "header.h"

void floating_point_parsing(struct memory_layout_node *node, double *value, char *line, size_t *starting_index)
{
	/* no double precision floating point integer can be 
	 * larger than 16 characters (in base 10) */
	char float_string[18] = { 0 };	/* 18B because we account for sign (+/-) and NULL */
	uint8_t i = 0;




	while (line[*starting_index] != '\0')
	{
		if ((line[*starting_index] == ',') || 
				(line[*starting_index] == ']') ||
				 (line[*starting_index] == '}'))
		{
			break;
		}

		float_string[i] = line[i];

		*starting_index++;
		i++;
	}

	/* strtod */

	/* error checks*/

	/* assignment to *value */

}
