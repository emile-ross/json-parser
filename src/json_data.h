#include "enums.h"

#define NULL_VALUE 0

typedef struct
{
	json_content_type content_type;
	json_data_type data_type;
} json_type;


typedef struct 
{
	union {
		char* string;
		int64_t integer;
		double ffloat;
		Bool boolean;
	} data;
	json_type type;
} json_value;

typedef struct json_content
{
	json_content_type type;
	json_value *array;
	json_value value;
	struct json_content *recursive_content;
	size_t recursive_content_count;
} json_content;


typedef struct
{
	char *parent_object;	/* currently unused */
	json_type type;
	char *key_value;	/* store the string associated with the value 
				   { "name": "John" } "name" being the key_value */
	json_content *content;
} json_data;
/* to access content we must do
 * json_data[].content.value.data.(type[string, integer, ffloat or boolean]) */


