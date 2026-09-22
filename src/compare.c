#include "header.h"

Bool str_compare(const char *arg, const char *str)
{
	/* match arg to str */
	uint8_t i = 0;
	while (arg[i] != '\0' && str[i] != '\0')
	{
		if (arg[i] != str[i])
		{
			return False;
		}
		i++;
	}
	return True;
}

uint8_t key_match(Bool *success, const char *key_value, uint8_t num_entries, json_data json_entry[])
{
	uint8_t i = 0;
	for (i = 0; i < num_entries; i++)
	{
		if (str_compare(key_value, json_entry[i].key_value))
		{
			*(success) = True;
			return i;
		}
	}

	fprintf(stderr, "failed to find the value: %s\n", key_value);
	fprintf(stderr, "this value was never being looked up\n");
	
	*(success) = False;
	return 255;
}
