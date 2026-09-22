#include "header.h"

#define line_len 255

int json_parse(const char *file_path, uint8_t num_entries, json_data json_entry[])
{
	char *reject = "\"{}[]:;";
	FILE *fp = fopen(file_path, "r");
	char *line = malloc(line_len + 1);	/* used for storing the line buffer in the file */

	Bool open_quote = False;
	Bool key_specified = False;
	uint8_t start_quote_index = 0;

	uint16_t line_number = 0; 
	uint8_t i = 0;
	uint8_t j = 0;

	uint8_t str_size = 0;	/* TODO variable length ( based on strcspn() ) */
	char *key_value = NULL;

	uint8_t current_lookup = 0;	/* store the current entry being looked up
	if an entry is matched (found) the counter goes up */

	file_check(fp, file_path);	/* checks for fp being NULL */

	do {
		uint8_t current_entry = 0;
		Bool key_success = False;
		open_quote = False;
		i = 0;
		/* only valid since line is an array of chars */

		if (fgets(line, line_len, fp) == NULL)
		{
			/* end of file */
			break;
		}

		while (line[i] != '\0')
		{
			Bool end_line = False;
			if (line[i] == '\t' || line[i] == ' ')
			{
				i++;
				continue;
			}

			switch (line[i])
			{
			case ';':
				if (open_quote || start_quote_index)
				{
					fprintf(stderr, "Quotes cannot span across multiple lines\n");
					fprintf(stderr, "The following quote is never ended: %s\n", line + start_quote_index - 1);
					exit(1);
				}
				end_line = True;
				continue;

			case '=':	/* both characters are accepted */
			case ':':
				if (key_success)
					key_specified = True;
				break;
			case '"':
				if (!key_specified)
				{
					if (!open_quote)
					{
						open_quote = True;
						start_quote_index = i + 1;
						break;
					}

					open_quote = False;
					str_size = (uint8_t)strcspn(line + start_quote_index, "\"");

					for (j = 0; j < str_size; j++)
					{
						/* copy bytes from line into the key_value buffer
						 * reads from the quote start + 1 (skip quote) and then
						 * add the j iterator for looping through the string  */
						if (key_value == NULL)
						{
							key_value = malloc(str_size);
						}
						key_value[j] = line[start_quote_index + j];
					}

					printf("key value -> %s\n", key_value);
					key_value[str_size] = '\0';
					key_success = False;
					current_entry = key_match(&key_success, key_value, num_entries, json_entry);
					printf("entry : %d\n", current_entry);
					start_quote_index = 0;
					break;
				}
				/* OTHERWISE if  the key_specified boolean IS TRUE 
				 * this will fallthrough onto the default case 
				 * (since this means we are now checking for the result (assignement of a string) */
				__attribute__ ((fallthrough));

			default:
				/* full expression is only true if the start_quote_index */
				if ((!start_quote_index) && key_specified)
				{
					if (json_entry[current_lookup].data_type == STRING)
					{
						if (line[i] == '"')
						{
							start_quote_index = i + 1;
						}
					}
					else if (json_entry[current_lookup].data_type == INTEGER)
					{
						if (line[i] == '"')
						{
							fprintf(stderr, "unexpected symbol %c in integer type\n", line[i]);
							exit(1);
						}
					}
					else if (json_entry[current_lookup].data_type == FLOAT)
					{
						if (line[i] == '"')
						{
							fprintf(stderr, "unexpected symbol '%c' in floating type\n", line[i]);
							exit(1);
						}
					}
				}
			}

			/* valid cast since the line can't be larger */
			if (!end_line)
				i = (uint8_t)strcspn(line + i, reject);
			i++;
		}

		line_number++;
	} while (num_entries > current_lookup && line_number < 1024);

	free(key_value);
	free(line);
	fclose(fp);

	return 0;
}
