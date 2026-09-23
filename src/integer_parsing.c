#include "header.h"


void parse_integer(const char *str, int32_t *value)
{
	char *endptr;
	long value;

	value = strtol(str, &endptr, 10);
	*result = (int32_t)value;
}
