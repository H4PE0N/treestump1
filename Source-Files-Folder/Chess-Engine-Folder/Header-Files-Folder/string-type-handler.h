
#ifndef STRING_TYPE_HANDLER_H
#define STRING_TYPE_HANDLER_H

bool split_string_delim(char*[], const char[], short, const char[], short);

void alloc_array_strings(char*[], short, short);

void free_array_strings(char*[], short);

short string_symbol_index(const char[], short, char);

bool merge_string_delim(char*, char*[], short, const char[]);

char* create_char_string(short);

#endif
