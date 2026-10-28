CC = cc

filenames := arrays checks compare integer_parsing main memory parser strings booleans float_parsing

src_fpaths = $(addprefix src/, $(filenames))
SRCS = $(addsuffix .c, $(src_fpaths))
CFLAGS = -Wall -Wextra -Wconversion -Wpedantic -std=c89 -Wshadow -Wswitch-enum -g
TIME = $(shell date +%H:%M:%S)

BIN_NAME := parser

all: base
base:
	$(CC) $(SRCS) $(CFLAGS) -o $(BIN_NAME) -Werror

base-e:
	$(CC) $(SRCS) $(CFLAGS) -o $(BIN_NAME) 

mem:
	valgrind --leak-check=full --log-file=$(TIME)-file.log ./parser test.json

debug:
	valgrind --leak-check=full ./parser test.json >> out.txt

clean: 
	rm *.log
	rm *.txt
	rm $(BIN_NAME)
