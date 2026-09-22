#include "header.h"

#define line_len 255

int json_parse(const char *file_path, uint8_t num_entries, json_data json_entry[])
{
	char *reject = "\"{}[]:;";
	FILE *fp = fopen(file_path, "r");
	char *line = smalloc(line_len + 1);	/* used for storing the line buffer in the file */

	Bool open_quote = False;
	Bool key_specified = False;
	uint8_t start_quote_index = 0;

	uint16_t line_number = 0; 
	uint8_t i = 0;

	uint8_t str_size = 0;
	char *key_value = NULL;
	char *content = NULL;

	uint8_t num_lookups = 0;	/* counts the number of entries looked up exits when everything is done */
	uint8_t current_entry = 0;	/* store the current entry being looked up
	if an entry is matched (found) the counter goes up */

	file_check(fp, file_path);	/* checks for fp being NULL */

	do {
		Bool key_success = False;
		open_quote = False;
		i = 0;
		key_value = NULL;
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
				if (!(i > start_quote_index + str_size))
				{
					fprintf(stderr, "Quotes cannot span across multiple lines\n");
					fprintf(stderr, "The following quote is never ended: %s\n", line + start_quote_index - 1);
					exit(1);
				}
				end_line = True;
				i++;
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

					str_size = (uint8_t)strcspn(line + start_quote_index, "\"");

					if (key_value != NULL)
					{
						free(key_value);
					}

					key_value = smalloc(str_size + 1);

					/* copy bytes from line into the key_value buffer 
					 * memcpy() will only copy 'str_size' bytes into the key_value buffer */
					memcpy(key_value, line + start_quote_index, str_size);
					key_value[str_size] = '\0';
					printf("key value -> %s\n", key_value);	/* prints the key_value as a test */

					key_success = False;
					current_entry = key_match(&key_success, key_value, num_entries, json_entry);

					printf("entry : %d\n", current_entry);

					start_quote_index = 0;
					open_quote = False;
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
					if (json_entry[current_entry].data_type == STRING)
					{
						if (line[i] == '"')
						{
							start_quote_index = i + 1;
						}
					}
					else if (json_entry[current_entry].data_type == INTEGER)
					{
						if (line[i] == '"')
						{
							fprintf(stderr, "unexpected symbol %c in integer type\n", line[i]);
							exit(1);
						}
						if (content != NULL)
						{
							free(content);
						}
						str_size = 1 + (uint8_t)strcspn(line + i, "dDiI;");
						content = smalloc(str_size);
						memcpy(content, line + i, str_size);
						printf("content %s\n", content);
					}
					else if (json_entry[current_entry].data_type == FLOAT)
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
			{
				/* jumps to the next characters (ignore whitespace) */
				i += (uint8_t)strcspn(line + i, reject);
			}
			else
				break;
			i++;
		}

		line_number++;
	} while (num_entries > num_lookups && line_number < 1024);

	if (key_value != NULL)
	{
		free(key_value);
	}
	free(line);
	fclose(fp);

	return 0;
}
