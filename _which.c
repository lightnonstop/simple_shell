#include "main.h"
/**
  * get_path - Fetches the path
  * @token: Token from string
  * @arr: Array for path
  * @file: File name
  * @filelen: Length of file name
  */
void get_path(char **token, char **arr, 
	char **file, int *filelen, int *ind2, int *ind1, int *tkin)
{
	int arrlen;

	while ((*token)[(*tkin)] != '\0')
		(*tkin)++;
	arrlen = *filelen + (*tkin) + 2;
	*arr = malloc(sizeof(char) * arrlen);
	for ((*ind1) = 0; (*token)[(*ind1)] != '\0'; (*ind1)++)
		(*arr)[(*ind1)] = (*token)[(*ind1)];
	(*arr)[(*ind1)] = '/';
	(*ind1)++;
	while ((*file)[(*ind2)] != '\0')
	{
		(*arr)[(*ind1)] = (*file)[(*ind2)];
		(*ind1)++;
		(*ind2)++;
	}
	(*arr)[(*ind1)] = '\0';
}
/**
  * _which - Looks for files in current path
  * @file: File to look for
  * Return: Path for file or if unsuccessful 0
  */
char *_which(char *file)
{
	struct stat st;
	char *path = getenv("PATH"), *token, *arr;
	int filelen = 0, tkin = 0, ind1, ind2 = 0, state;

	while (file[filelen] != '\0')
		filelen++;
	if ((stat(file, &st) == 0))
	{
		if (S_ISREG(st.st_mode))
			return (file);
	}
	else
	{

		token = strtok(path, ":");
		while (token != NULL)
		{
			get_path(&token, &arr, &file, &filelen, &ind2, &ind1, &tkin);
			if ((stat(arr, &st) == 0))
			{
				state = 1;
				break;
			}
			else
			{
				state = 0;
				tkin = 0;
				ind1 = 0;
				ind2 = 0;
				token = strtok(NULL, ":");
			}
		}
		if (state == 1)
			return (arr);
		free(arr);
		return (0);
	}
	return (0);
}
