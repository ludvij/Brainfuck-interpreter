CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11 -O3
INTERPRET = bf
TRANSPILER = bf2c

all: $(INTERPRET) $(TRANSPILER)

$(INTERPRET): bf.c
	$(CC) $(FLAGS) -o $@ $^

$(TRANSPILER): bf2c.c
	$(CC) $(FLAGS) -o $@ $^
