#include "main.h"
/**
  * _strcmp - Compares two strings
  * @str1: First Operand
  * @str2: Second Operand
  * Return: 0, if the string 1 and string 2 are equal,
  * a negative value if string 1 is less than string 2,
  * a positive value if string 1 is greater than string 2
  */
int _strcmp(const char *str1, const char *str2)
{
	unsigned const char *us1 = (unsigned const char *)str1;
	unsigned const char *us2 = (unsigned const char *)str2;

	while (*us1 == *us2 && *us1 != '\0')
	{
		us1++;
		us2++;
	}
	return ((*us1 > *us2) - (*us1 < *us2));
}
