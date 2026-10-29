#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>

#include "json_data.h"	/* all structs & types used for parsing (json_value, json_content, ...) */
#include "macros.h" /* all macros (integer bounds) */

/* memory layout */
	struct memory_layout_node
	{
		void *ptr;
		Bool allocated;
		struct memory_layout_node *next_node;
	};

/* src/parse.c */
	int json_parse(struct memory_layout_node *node, const char *file_path, uint32_t num_entries, json_data json_entry[]);
	/* json_parse expects an array of data composed of structs of json_data type (see src/json_data.h ) */

/* src/compare.c */
	Bool str_compare(const char *arg, const char *str);
	uint32_t key_match(Bool *fail, const char *key_value, uint32_t num_entries, json_data json_entry[]);
	Bool str_n_compare(const char *arg, const char *str, size_t size);

/* src/memory.c */
	void *srealloc(struct memory_layout_node *node, void *ptr, size_t size);
	void *smalloc(struct memory_layout_node *node,size_t size);


/* src/booleans.c */
	Bool parse_bool(Bool *fail, char *line);

/* src/checks.c */
	void file_check(FILE *file_path, const char *filename);
	/* conversions */
	int32_t to_int32(int64_t input);
	uint32_t to_uint32(uint64_t input);

/* src/integer_parsing.c */
	uint8_t parse_integer(const char *str, int64_t *result);

/* src/float_parsing.c */
	void floating_point_parsing(struct memory_layout_node *node, const char *line, size_t *starting_index, double *value);

/* src/buffers.c */
	char *str_content_alloc(struct memory_layout_node *node, char *line, size_t *starting_index, size_t *size);

/* src/arrays.c */
	size_t json_array_parser(struct memory_layout_node *node, json_content *content, char *line, size_t c_pos);

/* handling memory */
	struct memory_layout_node *get_last_node(struct memory_layout_node *node);
	void sfree(struct memory_layout_node *node);

void print_context(char *line, const char c, const uint16_t context_size, char *message);

