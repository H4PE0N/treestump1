
#ifndef STRING_TYPE_HANDLER_H
#define STRING_TYPE_HANDLER_H

bool split_string_delim(char*[], const char[], unsigned short, const char[], unsigned short);

void alloc_array_strings(char*[], unsigned short, unsigned short);

void free_array_strings(char*[], unsigned short);

signed short string_symbol_index(const char[], unsigned short, char);

#endif
