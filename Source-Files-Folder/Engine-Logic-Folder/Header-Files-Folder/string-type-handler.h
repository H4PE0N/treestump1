
#ifndef STRING_TYPE_HANDLER_H
#define STRING_TYPE_HANDLER_H

bool split_string_delim(char* stringArray[], const char string[], short length, const char delim[], short amount);

void alloc_array_strings(char* stringArray[], short amount, short length);

void free_array_strings(char* stringArray[], short amount);

short string_symbol_index(const char string[], short length, char symbol);

bool merge_string_delim(char* string, char* stringArray[], short amount, const char delim[]);

char* create_char_string(short length);

bool parse_string_short(unsigned short* number, const char string[]);

bool parse_spaced_token(char* result, const char string[], const char token[]);

bool parse_token_quotes(char* result, const char string[], const char token[]);

#endif
