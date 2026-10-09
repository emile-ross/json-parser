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
/* With size version */
Bool str_n_compare(const char *arg, const char *str, size_t size)
{
    size_t i = 0;

    while (i < size)
    {
        if (arg[i] != str[i])
            return False;

        if (arg[i] == '\0')
            return True;

        i++;
    }

    return True;
}

uint32_t key_match(Bool *fail, const char *key_value, uint32_t num_entries, json_data json_entry[])
{
	uint32_t i = 0;
	for (i = 0; i < num_entries; i++)
	{
		if (str_compare(key_value, json_entry[i].key_value))
		{
			*(fail) = False;
			return i;
		}
	}

	fprintf(stderr, "failed to find the value: %s\n", key_value);
	fprintf(stderr, "this value was never being looked up\n");
	
	*(fail) = True;
	return INT32MAX;
}
