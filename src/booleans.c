#include "header.h"

/* *content = parse_bool(&fail, line + i);*/
Bool parse_bool(Bool *fail, char *line)
{
       *fail = False;
	  
       if (str_n_compare(line, "true", 4) &&
           (line[4] == '\0' ||
            isspace((unsigned char)line[4]) ||
            line[4] == ',' ||
            line[4] == '}' ||
            line[4] == ']'))
       {
           return True;
       }
	  
       if (str_n_compare(line, "false", 5) &&
           (line[5] == '\0' ||
            isspace((unsigned char)line[5]) ||
             line[5] == ',' ||
            line[5] == '}' ||
            line[5] == ']'))
       {
           return False;
       }
	  
       *fail = True;
       return False;
}
