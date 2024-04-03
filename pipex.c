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
	char *cmd1;
	char *cmd2;
	int i;
	int *fd;

	if (argc != 5 || access(argv[1], F_OK) == -1 || access(argv[4], F_OK) == -1)
		error_exit();

	fd = malloc(sizeof(int) * 2);
	if (!fd)
		error_exit();
	if (pipe(fd) == -1)
	{
		free(fd);
		error_exit();
	}
	i = 0;
	while (envp[i])
	{
		if (ft_strstr(envp[i], "PATH="))
			break ;
		i++;
	}
	dirs = ft_split(envp[i] + 5, ':');
	char **command1 = ft_split(argv[2], ' ');
	char **command2 = ft_split(argv[3], ' ');
	cmd1 = check_for_command(dirs, command1[0]);
	if (!cmd1)
	{
		free_list(command1);
		free_list(dirs);
		error_exit();
	}
	cmd2 = check_for_command(dirs, command2[0]);
	free_list(dirs);
	if (!cmd2)
	{
		free_list(command1);
		free_list(command2);
		free(cmd1);
		error_exit();
	}
	int pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(open(argv[1], O_RDONLY), 0);
		dup2(fd[1], 1);
		char *argv2[] = {0};
		close(fd[1]);
		execve(cmd1, command1, argv2);
	}
	else 
	{
		close(fd[1]);
		wait(NULL);
		int pid1 = fork();
		if (pid1 == 0)
		{
			dup2(fd[0], 0);
			dup2(open(argv[4], O_WRONLY), 1);
			char *argv2[] = {0};
			execve(cmd2, command2, argv2);
		}
	}	
}
