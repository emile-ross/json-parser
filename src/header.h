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
