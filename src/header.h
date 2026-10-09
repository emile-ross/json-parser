#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "json_data.h"	/* all structs & types used for parsing (json_value, json_content, ...) */
#include "macros.h" /* all macros (integer bounds) */

/* src/parse.c */
	int json_parse(const char *file_path, uint32_t num_entries, json_data json_entry[]);
	/* json_parse expects an array of data composed of structs of json_data type (see src/json_data.h ) */

/* src/compare.c */
	Bool str_compare(const char *arg, const char *str);
	uint32_t key_match(Bool *fail, const char *key_value, uint32_t num_entries, json_data json_entry[]);
	Bool str_n_compare(const char *arg, const char *str, size_t size);

/* src/memory.c */
	void *srealloc(void *ptr, size_t size);
	void *smalloc(size_t size);


/* src/booleans.c */
	Bool parse_bool(Bool *fail, char *line);

/* src/checks.c */
	void file_check(FILE *file_path, const char *filename);
	/* conversions */
	int32_t to_int32(int64_t input);
	uint32_t to_uint32(uint64_t input);

/* src/integer_parsing.c */
	uint8_t parse_integer(const char *str, int64_t *result);

/* src/buffers.c */
	char *str_content_alloc(char *line, size_t *starting_index, size_t *size);

/* src/arrays.c */
	size_t json_array_parser(json_content *content, char *line, size_t c_pos);
