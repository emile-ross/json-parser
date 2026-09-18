#include "enums.h"

typedef struct
{
	char *parent_object;
	json_data_type data_type;
	char *key_value;
	void *content;
} json_data;
