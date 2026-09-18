CC = gcc

filenames := main parser
src_fpaths = $(addprefix src/, $(filenames))
SRCS = $(addsuffix .c, $(src_fpaths))
FLAGS = -Wall -Wextra -Wconversion -Wpedantic -std=c89

all: base
base:
	$(CC) $(SRCS) $(FLAGS) -o parser -Werror
