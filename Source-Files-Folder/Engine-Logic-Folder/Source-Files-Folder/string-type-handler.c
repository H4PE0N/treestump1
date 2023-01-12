
#include "../Header-Files-Folder/englog-include-file.h"

bool split_string_delim(char* stringArray[], const char string[], int length, const char delim[], int amount)
{
	if(amount < 1) return false;

	alloc_array_strings(stringArray, amount, length);

	char stringCopy[length + 1]; strcpy(stringCopy, string);

	if(!split_string_delim_t(stringArray, stringCopy, delim, amount))
	{
		free_array_strings(stringArray, amount); return false;
	}
	return true;
}

bool split_string_delim_t(char* stringArray[], char* stringCopy, const char delim[], int amount)
{
	char* stringToken = NULL;
	
	if((stringToken = strtok(stringCopy, delim)) == NULL) return false;

	strcpy(stringArray[0], stringToken);

	for(int index = 1; index < amount; index += 1)
	{
		if((stringToken = strtok(NULL, delim)) == NULL) return false;

		strcpy(stringArray[index], stringToken);
	}
	return true;
}

bool merge_string_delim(char* string, char* stringArray[], int amount, const char delim[])
{
	if(amount < 1) return false;

	for(int index = 0; index < amount; index += 1)
	{
		strcat(string, stringArray[index]);

		if(index < (amount - 1)) strcat(string, delim);
	}
	return true;
}

void alloc_array_strings(char* stringArray[], int amount, int length)
{
	for(int index = 0; index < amount; index += 1)
	{
		stringArray[index] = create_char_string(length);
	}
}

void free_array_strings(char* stringArray[], int amount)
{
	for(int index = 0; index < amount; index += 1)
	{
		free(stringArray[index]);
	}
}

int string_symbol_index(const char string[], int length, char symbol)
{
	for(int index = 0; index < length; index += 1)
	{
		if(symbol == string[index]) return index;
	}
	return INDEX_NONE;
}

char* create_char_string(int length)
{
	char* string = malloc(sizeof(char) * (length + 1));

	memset(string, '\0', sizeof(char) * (length + 1));

	return string;
}

bool parse_token_quotes(char* result, const char string[], const char token[])
{
  char strCpy[strlen(string) + 1]; strcpy(strCpy, string);

  char* strPoint;
  if(!(strPoint = strstr(strCpy, token))) return false;

  if(strtok(strPoint, "\"") == NULL) return false;

  char* strToken;
  if((strToken = strtok(NULL, "\"")) == NULL) return false;

  strcpy(result, strToken); return true;
}

bool parse_spaced_token(char* result, const char string[], const char token[])
{
  char strCopy[strlen(string) + 1]; strcpy(strCopy, string);

  char* strPoint;
  if(!(strPoint = strstr(strCopy, token))) return false;

  if(strtok(strPoint, " ") == NULL) return false;

  char* strToken;
  if((strToken = strtok(NULL, " ")) == NULL) return false;

  strcpy(result, strToken); return true;
}
