#include "pipex.h"

char *check_for_command(char **dirs, char *command1)
{
	char *command;
	int i;

	i = 0;
	while (dirs[i])
	{
		command = ft_strjoin(dirs[i], command1);
		if (access(command, X_OK) != -1)
			return (command);
		free(command);
		i++;
	}
	if (!dirs[i])
	{
		free_list(dirs);
		error_exit();
	}
	return (0);
}

int main(int argc, char *argv[], char **envp)
{
	char **dirs;
	int i;

	if (argc != 4)
		error_exit();
	if (access(argv[1], F_OK) == -1 || access(argv[4], F_OK) == -1)
		error_exit();
	i = 0;
	while (envp[i])
	{
		if (ft_strstr(envp[i], "PATH="))
			break ;
		i++;
	}
	dirs = ft_split(envp[i] + 5, ':');
	check_for_command(dirs, argv[2]);
	check_for_command(dirs, argv[3]);
	free_list(dirs);
}
