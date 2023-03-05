#include <stdio.h>
#include "../src/strings.h"

int testcopy() {
	char *string = "Hello World!";
	char *copy = strcopy(string);

	// Different pointers
	if (string == copy) {
		return 1;
	}

	// Strings are not the same
	if (strcmp(string, copy)) {
		return 2;
	}

	free(copy);

	return 0;
}

int testconcat() {
	char *base = "Hello";
	char *append = " World!";
	char *expected = "Hello World!";

	char *result = strconcat(base, append);

	// Strings are not the same
	if (strcmp(result, expected)) {
		return 2;
	}

	free(result);

	return 0;
}

int testtokenize() {
	char *string = "Hello, World,!,,extra";

	char **result = strtokenize(string, ",");

	if (strcmp(result[0], "Hello")) {
		return 1;
	}

	if (strcmp(result[1], " World")) {
		return 2;
	}

	if (strcmp(result[2], "!")) {
		return 3;
	}

	if (strcmp(result[3], "")) {
		return 4;
	}

	if (strcmp(result[4], "extra")) {
		return 5;
	}

	if (result[5] != NULL) {
		return 6;
	}

	free(result);

	return 0;
}

int testreplace() {
	char *string = "Good-bye World!";

	char *stage1 = strreplace(string, "-", "");
	char *stage2 = strreplace(stage1, "bye", "");
	char *stage3 = strreplace(stage2, "good", "Hello");
	char *stage4 = strreplace(stage3, "Good", "Hello");
	
	if (strcmp(stage1, "Goodbye World!")) {
		return 1;
	}

	free(stage1);

	if (strcmp(stage2, "Good World!")) {
		return 2;
	}

	free(stage2);

	if (strcmp(stage3, "Good World!")) {
		return 3;
	}

	free(stage3);

	if (strcmp(stage4, "Hello World!")) {
		return 4;
	}

	free(stage4);

	return 0;
}

int testformat() {
	char *string = "Hello %s you are %i years old.";
	char *name = "Til";
	int age = 18;

	char *result = strformat(string, name, age);

	if (strcmp(result, "Hello Til you are 18 years old.")) {
		return 1;
	}

	free(result);

	return 0;
}

int testsub() {
	char *string = "xxHello World!x";
	char *stage1 = strsub(string, 2, strlen(string));
	char *stage2 = strsub(stage1, 0, strlen(stage1) - 1);

	if (strcmp(stage1, "Hello World!x")) {
		return 1;
	}

	free(stage1);

	if (strcmp(stage2, "Hello World!")) {
		return 2;
	}

	free(stage2);

	return 0;
}

int testinsert() {
	char *string = "Helloorld!";
	char *result = strinsert(string, 5, " W");

	if (strcmp(result, "Hello World!")) {
		return 1;
	}

	free(result);

	return 0;
}

int testinsertch() {
	char *string = "HelloWorld!";
	char *result = strinsertch(string, 5, ' ');

	if (strcmp(result, "Hello World!")) {
		return 1;
	}

	free(result);

	return 0;
}

int testdel() {
	char *string = "HelloTHERE World!";
	char *result = strdel(string, 5, 10);

	if (strcmp(result, "Hello World!")) {
		return 1;
	}

	free(result);

	return 0;
}

void printresult(int result) {
	printf("%s", result ? "\033[31;1mFAILED" : "\033[32;1mPASSED");
	printf("\033[0m");
	if (result) {
		printf(" (%i)", result);
	}
	printf("\n");
}

int main(int argc, char **argv) {
	printf("Running tests\n");

	int result;

	printf("strcopy.. ");
	result = testcopy();
	printresult(result);

	printf("strconcat.. ");
	result = testconcat();
	printresult(result);

	printf("strtokenize.. ");
	result = testtokenize();
	printresult(result);

	printf("strreplace.. ");
	result = testreplace();
	printresult(result);

	printf("strformat.. ");
	result = testformat();
	printresult(result);

	printf("strsub.. ");
	result = testsub();
	printresult(result);

	printf("strinsert.. ");
	result = testinsert();
	printresult(result);

	printf("strinsertch.. ");
	result = testinsertch();
	printresult(result);

	printf("strdel.. ");
	result = testdel();
	printresult(result);

	printf("Tests done.\n");
}