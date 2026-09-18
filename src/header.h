#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "json_data.h"

/* parse.c */
	int json_parse(const char *file_path, uint16_t num_entries, json_data json_entry[]);
	uint16_t key_match(Bool *success, const char *key_value, uint16_t num_entries, json_data json_entry[]);

/* compare.c */
	Bool str_compare(const char *arg, const char *str);

void file_check(FILE *file_path, const char *filename);
