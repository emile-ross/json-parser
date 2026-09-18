#include "header.h"

typedef struct
{
	char *parent_object;
	json_data_type data_type;
	char *key_value;
	size_t content_size;
	void *content;
} json_data;
