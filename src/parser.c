#include "header.h"

void file_check(FILE *file_path, const char *filename);

int json_parse(const char *file_path, uint16_t num_entries, json_data (*json_entry)[])
{
	FILE *fp = fopen(file_path, "r");
	char line[256] = {0};	/* used for storing the line buffer in the file */
	file_check(fp, file_path);	/* checks for fp being NULL */

	do {
		uint16_t line_size = sizeof(line);
		Bool open_quote = False;
		uint8_t start_quote_index = 0;
		uint16_t i = 0;
		uint16_t j = 0;
		uint32_t str_size = 0;
		char *key_value = NULL;

		if (fgets(line, line_size, fp) == NULL)
		{
			/* end of file */
			break;
		}

		for (; i < line_size; i++)
		{
			if (line[i] == '"')
			{
				if (!(open_quote))
				{
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
					/* TODO compare key_value to valid key lookup */
				}
			}
		}

	} while (1);


	return 0;
}

/*
typedef struct
{
	char *parent_object;
	json_data_type data_type;
	char *key_value;
	void *content;
} json_data;
*/
