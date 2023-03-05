#include "strings.h"

// Allocates new string identical to given string
char *strcopy(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    char *new_str = malloc(strlen(str) + 1);
    if (new_str == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strcpy(new_str, str);
    return new_str;
}

// Concatenates string 'append' to string 'base'
char *strconcat(const char *base, const char *append) {
    if (base == NULL || append == NULL) {
        return NULL;
    }
    size_t base_len = strlen(base);
    size_t append_len = strlen(append);
    char *new_str = malloc(base_len + append_len + 1);
    if (new_str == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strcpy(new_str, base);
    strcat(new_str, append);
    return new_str;
}

// Tokenizes/splits given 'str' based on string 'token'
char **strtokenize(const char *str, const char *token) {
    char *token_ptr;
    char **tokens = NULL;
    int num_tokens = 0;
    while ((token_ptr = strstr(str, token)) != NULL) {
        // Allocate memory for a new token
        tokens = realloc(tokens, sizeof(char *) * (num_tokens + 1));
        if (tokens == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        // Copy the token to the new memory block
        size_t token_len = token_ptr - str;
        tokens[num_tokens] = malloc(token_len + 1);
        if (tokens[num_tokens] == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        strncpy(tokens[num_tokens], str, token_len);
        tokens[num_tokens][token_len] = '\0';
        // Update the string pointer and token count
        str = token_ptr + strlen(token);
        num_tokens++;
    }
    // Add the last token (or the entire string if no token found)
    size_t str_len = strlen(str);
    tokens = realloc(tokens, sizeof(char *) * (num_tokens + 1));
    if (tokens == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    tokens[num_tokens] = malloc(str_len + 1);
    if (tokens[num_tokens] == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strcpy(tokens[num_tokens], str);
    num_tokens++;
    // Add a NULL terminator to the end of the token array
    tokens = realloc(tokens, sizeof(char *) * (num_tokens + 1));
    if (tokens == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    tokens[num_tokens] = NULL;
    return tokens;
}

// Replaces 'what' with 'with' in given string and returns a new string
char *strreplace(char *str, const char *what, const char *with) {
    char *result = NULL;
    char *insert_ptr = NULL;
    char *tmp_str = str;
    int what_len = strlen(what);
    int with_len = strlen(with);
    int result_len = 0;
    // Count the number of replacements to determine the size of the result string
    int num_replacements = 0;
    while ((insert_ptr = strstr(tmp_str, what)) != NULL) {
        tmp_str = insert_ptr + what_len;
        num_replacements++;
    }
    // Allocate memory for the result string
    result_len = strlen(str) - (what_len * num_replacements) + (with_len * num_replacements);
    result = malloc(result_len + 1);
    if (result == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    // Copy the input string to the result string, with replacements
    tmp_str = str;
    char *result_ptr = result;
    while ((insert_ptr = strstr(tmp_str, what)) != NULL) {
        // Copy the substring before the match to the result string
        size_t copy_len = insert_ptr - tmp_str;
        strncpy(result_ptr, tmp_str, copy_len);
        result_ptr += copy_len;
        // Append the replacement string to the result string
        strncpy(result_ptr, with, with_len);
        result_ptr += with_len;
        // Update the string pointer
        tmp_str = insert_ptr + what_len;
    }
    // Append the rest of the string to the result string
    strcpy(result_ptr, tmp_str);
    return result;
}

// Allocates new string and formats (%...) with arguments
char *strformat(const char *str, ...) {
    char *result = NULL;
    va_list args;
    va_start(args, str);
    // Determine the length of the formatted string
    int length = vsnprintf(NULL, 0, str, args);
    va_end(args);
    // Allocate memory for the result string
    result = malloc(length + 1);
    if (result == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    // Format the string with the arguments and copy it to the result string
    va_start(args, str);
    vsnprintf(result, length + 1, str, args);
    va_end(args);
    return result;
}

// Allocates new string and caps its length
char *strsub(const char *str, size_t start, size_t end) {
    size_t len = strlen(str);
    if (end > len) {
        end = len;
    }
    if (start > end) {
        perror("Start index bigger than end index");
        exit(EXIT_FAILURE);
    }
    size_t sublen = end - start;
    char *substr = malloc(sublen + 1);
    if (substr == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strncpy(substr, str + start, sublen);
    substr[sublen] = '\0';
    return substr;
}

// Allocates new string and inserts given string at given index
char *strinsert(const char *str, size_t index, const char *insertstr) {
    size_t len = strlen(str);
    size_t insertlen = strlen(insertstr);
    char *newstr = malloc(len + insertlen + 1);
    if (newstr == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strncpy(newstr, str, index);
    strncpy(newstr + index, insertstr, insertlen);
    strncpy(newstr + index + insertlen, str + index, len - index);
    newstr[len + insertlen] = '\0';
    return newstr;
}

// Allocates new string and inserts given char at given index
char *strinsertch(const char *str, size_t index, char insertch) {
    size_t len = strlen(str);
    char *newstr = malloc(len + 2);
    if (newstr == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strncpy(newstr, str, index);
    newstr[index] = insertch;
    strncpy(newstr + index + 1, str + index, len - index);
    newstr[len + 1] = '\0';
    return newstr;
}

char *strdel(const char *str, size_t start, size_t end) {
    size_t str_len = strlen(str);
    if (end > str_len) {
        end = str_len;
    }
    if (start >= end) {
        // char *empty = malloc(1);
        // empty[0] = '\0';
        // return empty;
        perror("Start index is bigger than end index");
        exit(EXIT_FAILURE);
    }
    char *left = strsub(str, 0, start);
    char *right = strsub(str, end, str_len);
    size_t left_len = strlen(left);
    size_t right_len = strlen(right);
    char *result = malloc(left_len + right_len + 1);
    if (result == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strcpy(result, left);
    strcat(result, right);
    free(left);
    free(right);
    return result;
}