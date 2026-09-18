#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "json_data.h"


typedef enum
{
	False = 0,
	True = 1
} Bool;

int json_parse(const char *file_path);
