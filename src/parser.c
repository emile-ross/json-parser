#include "header.h"

#define line_len 255

int json_parse(const char *file_path, uint16_t num_entries, json_data json_entry[])
{
	char *reject = 
	FILE *fp = fopen(file_path, "r");
	char *line = malloc(line_len + 1);	/* used for storing the line buffer in the file */
	uint16_t current_lookup = 0;
	uint16_t line_size = 0;
	Bool open_quote = False;
	Bool key_specified = False;
	uint16_t start_quote_index = 0;
	uint16_t i = 0;
	uint16_t j = 0;
	uint32_t str_size = 0;
	char *key_value = NULL;

	file_check(fp, file_path);	/* checks for fp being NULL */

	do {
		Bool success = False;
		open_quote = False;
		/* only valid since line is an array of chars */

		if (fgets(line, line_len, fp) == NULL)
		{
			/* end of file */
			break;
		}

		while (line[strcspn(line + i, "\"{}[]:;")] != '\0')
		{
			if (line[i] == ';' && !(open_quote))
			{
				break;
			}
			else if (line[i] == '"' && !(open_quote))
			{
				open_quote = True;
			}
			else if (line[i] == '"' && !(key_specified))

			i = strcspn(line + i, "\"{}[]:;");
		}

		/*
		for (i = 0; line[i] != '\0'; i++)
		{

			if (line[i] == '"')
			{
				if (open_quote)
				{
					str_size = (uint32_t)(i - start_quote_index - 1);
					key_value = malloc(str_size + 1);
					for (j = 0; j < str_size; j++)
					{
						copy bytes from line into the key_value buffer

						 reads from the quote start + 1 (skip quote) and then
						 * add the j iterator for looping through the string 
						key_value[j] = line[start_quote_index + j + 1];
					}
					key_value[str_size] = '\0';
					printf(key_value);

					key_match(&success, key_value, num_entries, json_entry);
				}
				else
				{
					start_quote_index = i;
					open_quote = True;
				}
			}
		}
		*/

		free(key_value);

	} while (num_entries > current_lookup);

	fclose(fp);

	return 0;
}

uint16_t key_match(Bool *success, const char *key_value, uint16_t num_entries, json_data json_entry[])
{
	uint16_t i = 0;
	for (i = 0; i < num_entries; i++)
	{
		if (str_compare(key_value, json_entry[i].key_value))
		{
			*(success) = True;
			return i;
		}
	}

	fprintf(stderr, "failed to find the value: %s\n", key_value);
	exit(1);
	
	*(success) = False;
	return 65535;
}
