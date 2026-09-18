#include "header.h"

int json_parse(const char *file_path, uint16_t num_entries, json_data json_entry[])
{
	FILE *fp = fopen(file_path, "r");
	char line[256] = {0};	/* used for storing the line buffer in the file */
	uint16_t current_lookup = 0;
	uint16_t line_size = 0;
	Bool open_quote = False;
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
		line_size = sizeof(line);

		if (fgets(line, line_size, fp) == NULL)
		{
			/* end of file */
			break;
		}

		for (i = 0; i < line_size; i++)
		{
			if (line[i] == '"')
			{
				if (!(open_quote))
				{
					start_quote_index = i;
					open_quote = True;
				}
				else
				{
					str_size = start_quote_index - i;
					key_value = malloc(str_size);
					for (j = start_quote_index; j < i; j++)
					{
						/* copy bytes from line into the key_value buffer */
						key_value[i] = line[j];
					}

					key_match(&success, key_value, num_entries, json_entry);
				}
			}
		}

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
		if (str_compare(key_value, json_entry->key_value))
		{
			*(success) = False;
			return i;
		}
	}

	fprintf(stderr, "failed to find the value: %s\n", key_value);
	exit(1);
	
	*(success) = False;
	return 65535;
}
