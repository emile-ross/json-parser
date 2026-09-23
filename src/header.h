#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "json_data.h"

/* parse.c */
	int json_parse(const char *file_path, uint8_t num_entries, json_data json_entry[]);

/* compare.c */
	Bool str_compare(const char *arg, const char *str);
	uint8_t key_match(Bool *success, const char *key_value, uint8_t num_entries, json_data json_entry[]);

/* checks.c */
	void *smalloc(size_t size);
	void file_check(FILE *file_path, const char *filename);

/* integers */
	void parse_integer(const char *str, int32_t *result);


#define INT16MAX (32767)
#define INT16MIN (-32767)
#define UINT16MAX (65535)

#define INT32MAX (2147483647)
#define INT32MIN (-2147483647)
#define UINT32MAX (4294967295)
