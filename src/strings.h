#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

// Allocates new string identical to given string
char *strcopy(const char *str);

// Allocates new string which concatonates string 'append' and 'base'
char *strconcat(const char *base, const char *append);

// Tokenizes/splits given 'str' based on string 'token'
char **strtokenize(const char *str, const char *token);

// Allocates new string and replaces 'what' with 'with' in given string
char *strreplace(char *str, const char *what, const char *with);

// Allocates new string and formats (%...) with arguments
char *strformat(const char *str, ...);

// Allocates new string and caps its length
char *strsub(const char *str, size_t start, size_t end);

// Allocates new string and inserts given string at given index
char *strinsert(const char *str, size_t index, const char *insertstr);

// Allocates new string and inserts given char at given index
char *strinsertch(const char *str, size_t index, char insertch);

// Allocates new string and removes chars within given span (inverse of strsub)
char *strdel(const char *str, size_t start, size_t end);