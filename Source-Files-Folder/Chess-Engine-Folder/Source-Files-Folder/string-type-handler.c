
#include "../Header-Files-Folder/engine-include-file.h"

bool split_string_delim(char* stringArray[], const char string[], short length, const char delim[], short amount)
{
	if(amount < 1) return false;

	char stringCopy[length + 1]; strcpy(stringCopy, string);

	alloc_array_strings(stringArray, amount, length);

	char* stringToken = NULL;

	if((stringToken = strtok(stringCopy, delim)) == NULL)
	{
		free_array_strings(stringArray, amount); return false;
	}

	for(unsigned short index = 0; index < amount; index += 1)
	{
		strcpy(stringArray[index], stringToken);

		if((stringToken = strtok(NULL, delim)) == NULL) break;
	}
	return true;
}

bool merge_string_delim(char* string, char* stringArray[], short amount, const char delim[])
{
	if(amount < 1) return false;

	for(unsigned short index = 0; index < amount; index += 1)
	{
		strcat(string, stringArray[index]);

		if(index < (amount - 1)) strcat(string, delim);
	}
	return true;
}

void alloc_array_strings(char* stringArray[], short amount, short length)
{
	for(unsigned short index = 0; index < amount; index += 1)
	{
		stringArray[index] = create_char_string(length);
	}
}

void free_array_strings(char* stringArray[], short amount)
{
	for(unsigned short index = 0; index < amount; index += 1)
	{
		free(stringArray[index]);
	}
}

short string_symbol_index(const char string[], short length, char symbol)
{
	for(unsigned short index = 0; index < length; index += 1)
	{
		if(symbol == string[index]) return index;
	}
	return INDEX_NONE;
}

char* create_char_string(short length)
{
	char* string = malloc(sizeof(char) * (length + 1));
	memset(string, '\0', sizeof(char) * (length + 1));

	return string;
}

bool parse_token_fenstr(char* fenString, const char string[], const char token[])
{
  char strCpy[strlen(string) + 1]; strcpy(strCpy, string);

  char* strPoint;
  if(!(strPoint = strstr(strCpy, token))) return false;

  if(strtok(strPoint, "\"") == NULL) return false;

  char* strToken;
  if((strToken = strtok(NULL, "\"")) == NULL) return false;

  strcpy(fenString, strToken); return true;
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

bool parse_string_short(unsigned short* number, const char string[])
{
	unsigned short stringLength = strlen(string);

	if(stringLength < 1) return false;

	unsigned short dummyNumber = 0;

	for(unsigned short index = 0; index < stringLength; index += 1)
	{
		unsigned short value = pow(10, (stringLength - index - 1));

		signed short potentNumber = (string[index] - '0');

		if(!NUMBER_IN_BOUNDS(potentNumber, 0, 9)) return false;

		dummyNumber += (value * potentNumber);
	}
	*number = dummyNumber; return true;
}
