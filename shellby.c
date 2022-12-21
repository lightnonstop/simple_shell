#include"main.h"
/**
  * prompt_cmd - Handles prompting and reads command
  * @lineptr: Pointer to read line
  * @hdline: Pointer to the one which holds copy of read line
  * @n: Pointer to the number of byte allocated for characters read on the line
  * @n_count: Pointer to the number of characters read from line
  * @lineptr_c: Pointer to a copy of read line
  * @token: Pointer to a token from a delimited string
  * @holdtk: Pointer to copy of the token
  */
void prompt_cmd(char **lineptr, char **hdline, size_t *n, ssize_t *n_count,
	char **lineptr_c, char **token, char **holdtk)
{
	int line_ind = 0, hdl_ind = 0, ind, i;
	char *prompt = "($) ";

	printf("%s ", prompt);
	*n_count = getline(&(*lineptr), &(*n), stdin);
	if (*n_count == -1)
		exit(0);
	*lineptr_c = malloc(sizeof(char) * (*n_count));
	if (*lineptr_c == NULL)
	{
		free(*lineptr);
		exit(0);
	}
	while ((*lineptr)[line_ind] != '\0' && (*lineptr)[line_ind] != '\n')
		line_ind++;
	line_ind = 0;
	while ((*lineptr)[line_ind] != '\0' && (*lineptr)[line_ind] != '\n')
	{
		(*lineptr_c)[line_ind] = (*lineptr)[line_ind];
		line_ind++;
	}
	(*lineptr_c)[line_ind] = '\0';
	*hdline = malloc(sizeof(char) * (*n_count));
	if (*hdline == NULL)
	{
		free(*hdline);
		exit(0);
	}
	while ((*lineptr_c)[hdl_ind] != '\0' && (*lineptr_c)[hdl_ind] != '\n')
	{
		(*hdline)[hdl_ind] = (*lineptr_c)[hdl_ind];
		hdl_ind++;
	}
	(*hdline)[hdl_ind] = '\0';
	(*token) = _strtok((*lineptr_c), " ");
	for (ind = 0; (*token)[ind]; ind++)
	(*holdtk) = malloc(sizeof(char) * ind);
	for (i = 0; (*token)[i]; i++)
		(*holdtk)[i] = (*token)[i];
	(*holdtk)[i] = '\0';
}
/**
  * exec_m - Executes read commands from main
  * @arr: Pointer to array of commands
  * @argt: Pointer to each command as argument
  * @hdline: Pointer to the one which holds copy of read line
  * @fullpath: Retrieves the full path of a command if it exists
  * @env: Points to array of environment Variables
  */
void exec_m(char ***arr, char **argt, char **hdline,
	char ***env, char **fullpath)
{
	int ind = 0;
	(*arr)[ind] = (*fullpath);
	ind = 1;
	(*argt) = _strtok((*hdline), " ");
	while ((*argt) != NULL)
	{
		*argt = _strtok(NULL, " ");
		(*arr)[ind] = (*argt);
		ind++;
	}
	(*arr)[ind] = NULL;
	execve((*arr)[0], (*arr), *env);
}
/**
  * only_env - Executes only env command
  * @argv: Pointer to array of commands
  * @fullpath: Retrieves the full path of a command if it exists
  * @env: Points to array of environment Variables
  */
void only_env(char ***argv, char ***env, char **fullpath)
{
	(*argv)[0] = *fullpath;
	(*argv)[1] = NULL;
	execve((*argv)[0], *argv, *env);
}
/**
  * main - Starting point
  * Description: Executes shell commands
  * @argc: Argument counter
  * @argv: Argument vector
  * @env: Environment variable array
  * Return: Always success (0)
  */
int main(int argc __attribute__((unused)), char **argv, char *env[])
{
	pid_t id;
	char *token, *hdline, *holdtk, *fullpath, *argt, *lineptr = NULL, *lineptr_c;
	size_t n;
	ssize_t  n_count = 0;

	while (1)
	{
		id = getpid();
		if (fork() == 0)
		{
			prompt_cmd(&lineptr, &hdline, &n, &n_count, &lineptr_c, &token, &holdtk);
			fullpath = _which(holdtk);
			if (!(fullpath))
			{
				if (_strcmp(holdtk, "exit") == 0)
					exit_m(id);
				else
					printf("%s: command not found\n", holdtk);
			}
			else
			{
				if (fork() == 0)
				{
					if (_strcmp(holdtk, "env") == 0)
						only_env(&argv, &env, &fullpath);
					else
						exec_m(&argv, &argt, &hdline, &env, &fullpath);
					exit(0);
				}
				else
					wait(NULL);
			}
			exit(0);
		}
		else
			wait(NULL);
	}
	return (0);
}
