#include "main.h"
/**
 * exit_m - Exits parent process
 * @pid: process id
*/
void exit_m(pid_t pid)
{
	kill(pid, SIGHUP);
}

