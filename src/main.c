#include "header.h"


int main(int argc, char *argv[])
{
	/* no type safety/memory safety for the input since this will 
	 * later be implemented as a function without user input
	 * for now this simply assumes the user has all power */

	const char *file_path = argv[1];	/* will segfault if missing args */
	int i = 0;
	int j = 0;
	size_t b = 0; 
	json_content contents[5] = {0};


	json_data country =
	{
		NULL,
		{ ARRAY, NULL_VALUE },
		"countries",
		NULL,
	};
	json_data cold =
	{
		NULL,
		{ VALUE, BOOL },
		"cold",
		NULL
	};
	json_data currency =
	{
		NULL,
		{ ARRAY, NULL_VALUE },
		"currencies",
		NULL
	};

	json_data calling_code =
	{
		NULL,
		{ VALUE, STRING },
		"calling code",
		NULL
	};

	json_data population =
	{
		NULL,
		{ VALUE, INTEGER },
		"population",
		NULL
	};
	

	json_data entries[5];

	calling_code.content = &contents[0];
	population.content = &contents[1];
	currency.content = &contents[2];
	country.content = &contents[3];
	cold.content = &contents[4];
	
	entries[0] = calling_code;
	entries[1] = population;
	entries[2] = currency;
	entries[3] = country;
	entries[4] = cold;

	json_parse(file_path, 5, entries);
	
	printf("main.c (debug): \n");

	if (argc < 2)
	{
		fprintf(stderr, "Missing arguments in command\n");
	}

	for (i = 0; i < 5; i++) {
		printf("KEY: %s\n", entries[i].key_value);
		
		switch (entries[i].type.content_type)
		{
			case VALUE:
			switch (entries[i].type.data_type)
			{ 
				case INTEGER:
					printf("TYPE: INTEGER \n");
					printf("VALUE: %ld\n", entries[i].content->value.data.integer);
					break;
				case STRING:
					printf("TYPE: STRING \n");
					printf("VALUE: %s\n", entries[i].content->value.data.string);
					break;
				case BOOL:
					printf("TYPE: BOOLEAN \n");
					printf("VALUE: %d\n", entries[i].content->value.data.boolean);
					break;
				case CHAR:
					break;
				case FLOAT:
					break;
			}
			break;
			case ARRAY:
				printf("TYPE: ARRAY\n");
				printf("Array List: \n");
				for (j = 0; entries[i].content->array[j].type.content_type != UNKNOWN
					&& entries[i].content->array[j].type.content_type != ARRAY; j++)
				{
					if (entries[i].content->array[j].type.content_type == VALUE && 
						entries[i].content->array[j].type.data_type == STRING)
					{
						printf("Array [%d]. value: %s\n", j, entries[i].content->array[j].data.string);
    					}
				}
				/* UNDERSTANDING THE RECURSION:
				*  Total recursive content: 2.
				*  recursive_content is an array.
				*  entries[i].content (our content) -> recursive_content (our recursive content).
				*  recursive_content_count is the number of recursive contents.
				*  For example, [[RECURSION], [RECURSION]] has 2 recursive contents.
				*
				*  We now have the recursive content array and its count, so we can iterate over them:
				*
				*  entries[i].content->recursive_content[b].array[j].data.string
				*  -> the string value at index j of recursive content b.
				* 
				*  NOTES FOR THE DEVELOPERS:
				*  Recursion can continue indefinitely, so handling it properly requires
				*  an interface function along with a recursive function that works with it.
				*/
				for (b = 0; entries[i].content->recursive_content && entries[i].content->recursive_content_count > b; b++) {
					for (j = 0;  entries[i].content->recursive_content[b].array[j].type.content_type != UNKNOWN; j++) {
						printf("Recursion Array [%d]. value: %s\n", j,
							entries[i].content->recursive_content[b].array[j].data.string);
					}
				}
				break;
			case UNKNOWN:
				break;
			case OBJECT:
				/* TODO handle objects */
				break;
		}
	}


	return 0;
}
