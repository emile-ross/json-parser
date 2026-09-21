#include "header.h"


int main(int argc, char *argv[])
{
	/* no type safety/memory safety for the input since this will 
	 * later be implemented as a function without user input
	 * for now this simply assumes the user has all power */

	const char *file_path = argv[1];	/* will segfault if missing args */

	json_data program_name =
	{
		NULL,
		STRING,
		"program-name",
		NULL
	};
	json_data indenting =
	{
		NULL,
		INTEGER,
		"indenting",
		NULL
	};

	json_data entries[2] = { 0 };

	entries[0] = indenting;
	entries[1] = program_name;

	json_parse(file_path, 2, entries);

	if (argc < 2)
	{
		fprintf(stderr, "Missing arguments in command\n");
	}

	return 0;
}

