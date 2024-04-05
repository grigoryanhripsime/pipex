#include "pipex.h"

void error_exit(void)
{
	//system("leaks pipex");
	exit(1);
}

void error_free_exit(int *fd, char **cmd)
{
		free(fd);
		free_list(cmd);
		exit(1);
}

void free_list(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
void command_not_found(char **command, char **dirs)
{
	free_list(command);
	free_list(dirs);
	write(2, "command not found\n", 18);
	error_exit();
}

void permission_denied(int *fd)
{
	(void)fd;
	//free(fd);
	write(2, "Permission denied\n", 18);

}

