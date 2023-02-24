#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define MEM_SIZE 1000

char* loadSource(FILE* f) {
	int c;
	uint32_t size = 0;
	fseek(f, 0, SEEK_END);
	size_t fsize = ftell(f);
	char* buff = malloc(sizeof *buff * fsize);
	if (buff == NULL) perror("malloc");
	rewind(f);
	
	while((c = fgetc(f)) != EOF) {
		if (c!='+'&&c!='-'&&c!='<'&&c!='>'&&c!=','&&c!='.'&&c!='['&&c!=']') continue;
		buff[size++] = (char)c;
	}
	char* src = malloc(sizeof *src * size);
	if (src == NULL) perror("malloc");
	strncpy(src, buff, size);
	free(buff);

	return src;
}


uint8_t memory[MEM_SIZE] = {0};
int index = 0;

int interpret(char* src, int charIndex, bool execute) {
	char nextChar = '\0';
	// start index in case of loop
	int startIndex = charIndex;
	do {
		nextChar = src[charIndex];
		     if (execute && nextChar == '+') memory[index]++;             // increment memory
		else if (execute && nextChar == '-') memory[index]--;             // decrement memory
		else if (execute && nextChar == '>') index++;                     // increment pointer
		else if (execute && nextChar == '<') index--;                     // decrement pointer
		else if (execute && nextChar == '.') printf("%c", memory[index]); // print
		else if (execute && nextChar == ',') {                            // read
			if (scanf("%c", &memory[index]) == 0) {
				printf("Error while reading\n");
			}
			printf("%c\n", memory[index]);
		}
		else if (nextChar == '[') {                                       // jump if zero
			charIndex = interpret(src, charIndex + 1, memory[index] != 0);
		}
		else if (nextChar == ']') {                                       // jump if not zero
			if (memory[index] == 0) {
				return charIndex;
			}
			else {
				charIndex = startIndex - 1;
			}
		}
		charIndex++;
	} while (nextChar != '\0');

	return 0;
}
 
int main(int argc, char** argv) {
	if (argc == 1) {
		printf("Usage: %s path/to/file\n", argv[0]);
		return 0;
	}
	FILE* f = fopen(argv[1], "r");
	char* src = loadSource(f);
	interpret(src, 0, true);
	free(src);
	fclose(f);
}