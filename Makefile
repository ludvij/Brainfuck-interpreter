CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11 -O3
EXE = bf.exe

all: $(EXE)

$(EXE): bf.c
	$(CC) $(FLAGS) -o $(EXE) $^
