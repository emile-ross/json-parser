#include "header.h"

/* Handles recursive parsing for nested JSON arrays.
 * Parsing Algorithm:
 * '[' -> find the next comma -> ',' -> extract the value between commas or brackets
 * -> recognize the type -> add element to array variable with the detected type
 * -> loop until ']' is encountered
 * -> return the newly allocated array
 */
/* For now, I only parse 2 array elements. */
size_t json_array_parser(json_content *content, char *line, size_t c_pos)
{
	size_t i = c_pos + 1;
	json_value buffer;
	size_t total_values = 0;
	size_t str_size = 0;
	size_t ret_value;
	size_t recursion_counter = 0;
	Bool buffer_changed = False;
	Bool recursion = False;
	Bool reached_end = False; 

	/* variable declaration end */

	/* Only 2 for now. */
	content->array = smalloc(3 * sizeof(json_value));
	content->recursive_content = smalloc(3 * sizeof(json_content));	
	/* Only 2 for now */
	while (line[i] != '\0' && reached_end == False) 
	{
		switch (line[i]) 
		{
		case '[':
			ret_value = json_array_parser(&content->recursive_content[recursion_counter], line, i);
			i = ret_value;
			/* setting type to array to understand */
			content->array[total_values++].type.content_type = ARRAY;
			recursion_counter++;
			recursion = True;
			break;
		case ']':
			/* The last element could be any type, but for now I am only adding strings. */
			if (buffer_changed)
				content->array[total_values++] = buffer;
			i++;
			reached_end = True;
			content->array[total_values].type.content_type = UNKNOWN;
			/* The last element is set to UNKNOWN to mark the end of the array. */
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
			buffer.data.string = str_content_alloc(line, &i, &str_size);
			break;
		case ',':
			if (buffer_changed) {
				/* Flush buffer into content array and move to the next item. */
				content->array[total_values++] = buffer;
				buffer_changed = False;
			}
			break;
		default:	
			/* INTEGER */
			break;
		}
		if (reached_end) { reached_end = False; break; }
		if (recursion) { recursion = False; continue; }
		i++;
	}
	content->recursive_content_count = recursion_counter;
	return i;
}
