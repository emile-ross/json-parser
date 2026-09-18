CC = gcc

SRCS = main.c
FLAGS = -Wall -Wextra -Wconversion -Wpedantic -std=c89

all: base
base:
	$(CC) $(SRCS) $(FLAGS) -o parser
