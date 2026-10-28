#include "header.h"

#define i *(starting_index)

void floating_point_parsing(struct memory_layout_node *node, char *line, size_t *starting_index)
{
	size_t i = *(starting_index);


	while (line[i] != '\0')
	{
		i++;
	}

}
