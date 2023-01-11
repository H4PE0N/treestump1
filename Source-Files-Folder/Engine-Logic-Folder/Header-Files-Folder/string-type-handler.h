
#ifndef STRING_TYPE_HANDLER_H
#define STRING_TYPE_HANDLER_H

bool split_string_delim(char* stringArray[], const char string[], int length, const char delim[], int amount);

void alloc_array_strings(char* stringArray[], int amount, int length);

void free_array_strings(char* stringArray[], int amount);

int string_symbol_index(const char string[], int length, char symbol);

bool merge_string_delim(char* string, char* stringArray[], int amount, const char delim[]);

char* create_char_string(int length);

bool parse_spaced_token(char* result, const char string[], const char token[]);

bool parse_token_quotes(char* result, const char string[], const char token[]);

#endif
