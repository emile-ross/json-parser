CC = gcc

filenames := main parser checks compare
src_fpaths = $(addprefix src/, $(filenames))
SRCS = $(addsuffix .c, $(src_fpaths))
FLAGS = -Wall -Wextra -Wconversion -Wpedantic -std=c89 -Wshadow -Wswitch-enum

all: base
base:
	$(CC) $(SRCS) $(FLAGS) -o parser -Werror

base-e:
	$(CC) $(SRCS) $(FLAGS) -o parser
