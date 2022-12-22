#include "main.h"
/**
  * is_delim - Handles string if conatins delimiter(s)
  * @c: Each string character
  * @delim: Delimiter(s)
  * Return: 0 if delimiter(s) cannot be found, 1 if delimiter(s) can be found
  */
unsigned int is_delim(char c, const char *delim)
{
	while (*delim != '\0')
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}
/**
  * _strtok - Breaks a string into tokens using delimiter(s)
  * @str: Given string
  * @delim: Delimiter(s)
  * Return: Pointer to the next token, or  NULL  if  there are no more tokens
  */
char *_strtok(char *str, const char *delim)
{
	static char *backup_string;
	char *ret = NULL;

	if (!str)
	{
		str = backup_string;
	}
	if (!str)
	{
		return (NULL);
	}
	while (1)
	{
		if (is_delim(*str, delim))
		{
			str++;
			continue;
		}
		if (*str == '\0')
			return (NULL);
		break;
	}
	ret = str;

	while (1)
	{
		if (*str  == '\0')
		{
			backup_string = str;
			return (ret);
		}
		if (is_delim(*str, delim))
		{
			*str = '\0';
			backup_string = str + 1;
			return (ret);
		}
		str++;
	}
}
