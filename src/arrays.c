#include "header.h"

/* Handles recursive parsing for nested JSON arrays.
 * Parsing Algorithm:
 * '[' -> find the next comma -> ',' -> extract the value between commas or brackets
 * -> recognize the type -> add element to array variable with the detected type
 * -> loop until ']' is encountered
 * -> return the newly allocated array
 */
/* For now, I only parse 2 array elements. */
size_t json_array_parser(struct memory_layout_node *node, json_content *content, char *line, size_t c_pos)
{
	size_t i = c_pos + 1;
	json_value buffer;
	size_t total_values = 0;
	size_t str_size = 0;
	size_t ret_value;
	size_t array_capacity = STARTING_ALLOCATION;
	size_t recursion_counter = 0;
	size_t recursion_capacity = STARTING_ALLOCATION;
	Bool buffer_changed = False;
	Bool recursion = False;
	Bool reached_end = False; 

	/* variable declaration end */

	/* Only 2 for now. */
	content->array = smalloc(node, STARTING_ALLOCATION * sizeof(json_value));
	content->recursive_content = smalloc(node, STARTING_ALLOCATION * sizeof(json_content));	
	/* Only 2 for now */
	while (line[i] != '\0' && reached_end == False) 
	{
		
		if (total_values + 2 > array_capacity) {
			array_capacity *= 2;
			content->array = srealloc(node, content->array, array_capacity * sizeof(json_value));
		}

		switch (line[i]) 
		{
		case '[':
			if (recursion_counter >= recursion_capacity) {
				recursion_capacity *= 2;
				content->recursive_content = srealloc(node, content->recursive_content, recursion_capacity * sizeof(json_content));	
			}
			ret_value = json_array_parser(node, &content->recursive_content[recursion_counter], line, i);
			i = ret_value;
			/* setting type to array to understand */
			content->array[total_values++].type.content_type = ARRAY;
			recursion_counter++;
			recursion = True;
			break;
		case ']':
			if (buffer_changed)
				content->array[total_values++] = buffer;
			i++;
			reached_end = True;
			content->array[total_values].type.content_type = UNKNOWN;
			break;
		case '{':
			/* OBJECT */ 
			break;
		case '}':
			/* OBJECT */
			break;
		case '"':
			/* STRING */ 
			buffer.type.data_type = STRING;
			buffer.type.content_type = VALUE;
			buffer_changed = True;
			i++;
			buffer.data.string = str_content_alloc(node, line, &i, &str_size);
			break;
		case ',':
			if (buffer_changed) {
				/* Flush buffer into content array and move to the next item. */
				content->array[total_values++] = buffer;
				buffer_changed = False;
			}
			break;
		default:
			if (isdigit(line[i])) { 
				i += parse_integer(line + i, &buffer.data.integer);
				buffer.type.data_type = INTEGER;
				buffer.type.content_type = VALUE;
				buffer_changed = True;
				i--;
				break;
			}
		}
		if (reached_end) { reached_end = False; break; }
		if (recursion) { recursion = False; continue; }
		i++;
	}
	content->recursive_content_count = recursion_counter;
	return i;
}
