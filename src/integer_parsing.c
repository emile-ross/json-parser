#include "header.h"


void parse_integer(const char *str, int32_t *result)
{
	char *endptr;
	long value;

	value = strtol(str, &endptr, 10);

	if (endptr == str)
	{
		fprintf(stderr, "No valid integer found in \"%s\" string \n", str);
		return False;
	}

	if (value < INT32MIN || value > INT32MAX)
	{
		fprintf(stderr, "Integer is out of bounds (min: %ld) (max: %ld) input value: %ld\n", INT32MIN, INT32MAX, value);
		return False;
	}

	*result = (int32_t)value;

	return True;
}
