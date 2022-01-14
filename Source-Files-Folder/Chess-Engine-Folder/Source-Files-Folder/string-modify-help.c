
#include "../Header-Files-Folder/engine-include-file.h"

bool split_string_delim(char* stringArray[], char string[], unsigned short length, char delim[], unsigned short amount)
{
	// The amount must be more or equal to 1
	if(amount < 1) return false;

	// Duplicates the string to a pointer, so that it can be split using strtok
	char stringCopy[length];
	strcpy(stringCopy, string);

	// Create memory for the strings in the array

	for(unsigned short index = 0; index < amount; index += 1)
	{
		stringArray[index] = malloc(sizeof(char) * (length + 1));

		memset(stringArray[index], '\0', (length + 1));
	}

	// Tries to split the string once
	char* stringToken = NULL;

	if((stringToken = strtok(stringCopy, delim)) == NULL)
	{
		// If the string can't be split using the delim
		// This means that there is not 'delim' char

		for(unsigned short index = 0; index < amount; index += 1)
		{
			free(stringArray[index]);
			// frees the memory of each string
		}

		return false;
	}


	// Copies the split string into the first spot in the array
	strcpy(stringArray[0], stringToken);

	// Tries to split 'amount' strings from the rest of the string
	for(unsigned short index = 1; index < amount; index += 1)
	{
		if((stringToken = strtok(NULL, delim)) == NULL)
		{
			// If the string can't be split 'amount' times
			// This is not a large problem, so we can just continue
			break;
		}

		strcpy(stringArray[index], stringToken);
	}

	return true;
}

void free_array_strings(char* stringArray[], unsigned short amount)
{
	for(unsigned short index = 0; index < amount; index += 1)
	{
		free(stringArray[index]);
	}
}

int string_symbol_index(char string[], unsigned short length, char symbol)
{
	for(unsigned short index = 0; index < length; index += 1)
	{
		if(symbol == string[index]) return index;
	}

	return INDEX_NONE;
}