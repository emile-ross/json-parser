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
