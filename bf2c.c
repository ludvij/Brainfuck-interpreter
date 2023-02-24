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


int transpile(char* src, char* filename) {
	FILE* out = fopen(filename, "w");
	fprintf(out, "#include <stdlib.h>\n");
	fprintf(out, "#include <stdio.h>\n");
	fprintf(out, "int main(void) {\n");
	fprintf(out, "unsigned char* p = malloc(sizeof *p * 1000), *t = p;\n");
	for (int charIndex = 0; src[charIndex] != '\0'; charIndex++) {
		switch (src[charIndex])
		{
		case '+': fprintf(out, "++*p;\n");            break; 
		case '-': fprintf(out, "--*p;\n");            break;
		case '>': fprintf(out, "++p;\n");             break;
		case '<': fprintf(out, "--p;\n");             break;
		case '.': fprintf(out, "putchar(*p);\n");     break;
		case ',': fprintf(out, "p[0] = getchar();\n");break;
		case '[': fprintf(out, "while(*p) {\n");      break;
		case ']': fprintf(out, "}\n");                break;
		}
	} 
	fprintf(out, "free(t);\n");
	fprintf(out, "}");
	fclose(out);
	
	return 0;
}
 
int main(int argc, char** argv) {
	if (argc == 1) {
		printf("Usage: %s path/to/file\n", argv[0]);
		return 0;
	}
	FILE* f = fopen(argv[1], "r");
	char* src = loadSource(f);

	transpile(src, argc > 2 ? argv[2] : strcat(argv[1], ".c"));

	free(src);
	fclose(f);
}