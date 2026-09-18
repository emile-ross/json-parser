#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "json_data.h"


typedef enum
{
	False = 0,
	True = 1
} Bool;

int json_parse(const char *file_path, uint16_t num_entries, json_data json_entry[]);
Bool str_compare(const char *arg, const char *str);
uint16_t key_match(const char *key_value, uint16_t num_entries, json_data json_entry[]);

void file_check(FILE *file_path, const char *filename);
