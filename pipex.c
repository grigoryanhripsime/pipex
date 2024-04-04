#include "pipex.h"

int *init_fd()
{
	int *fd;

	fd = malloc(sizeof(int) * 2);
	if (!fd)
		return (0);
	if (pipe(fd) == -1)
	{
		free(fd);
		return (0);
	}
	return (fd);
}

char **init_dirs(char **envp)
{
	int i;
	char **dirs;

	i = 0;
	while (envp[i])
	{
		if (ft_strstr(envp[i], "PATH="))
			break ;
		i++;
	}
	dirs = ft_split(envp[i] + 5, ':');
	return (dirs);
}

char **check_for_command(char *cmd_from_terminal, char **dirs)
{
	char **command;
	int i;
	char *cmd;

	command = ft_split(cmd_from_terminal, ' ');
	i = 0;
	while (dirs[i])
	{
		cmd = ft_strjoin(dirs[i], command[0]);
		if (access(cmd, X_OK) != -1)
		{
			free(command[0]);
			command[0] = cmd;
			break ;
		}
		free(cmd);
		i++;
	}
	if (!dirs[i])
		return (0);
	return (command);
}


int main(int argc, char *argv[], char **envp)
{
	char **dirs;
	char **cmd;
	int *fd;

	if (argc != 5 || access(argv[1], F_OK) == -1)
		return (0);
	dirs = init_dirs(envp);
	fd = init_fd();
	if (!fd)
		return (0);
	int pid1 = fork();
	if (pid1 == 0)
	{
		cmd = check_for_command(argv[2], dirs);
		if (!cmd)
		{
			//free_list(dirs);
			return (0);
		}
		close(fd[0]);
		dup2(open(argv[1], O_RDONLY), 0);
		dup2(fd[1], 1);
		close(fd[1]);
		execve(cmd[0], cmd, envp);
	}
	else 
	{
		close(fd[1]);
		int pid2 = fork();
		if (pid2 == 0)
		{
			cmd = check_for_command(argv[4], dirs);
			if (!cmd)
			{
				//free_list(dirs);
				return (0);
			}
			dup2(fd[0], 0);
			dup2(open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777), 1);
			execve(cmd[0], cmd, envp);
		}
		wait(NULL);
	}
	system("leaks pipex");
}
