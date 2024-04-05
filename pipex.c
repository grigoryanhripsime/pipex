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
	if (access(command[0], X_OK) != -1)
		return (command);
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
		command_not_found(command, dirs);
	return (command);
}

void first_command(char *command, char *infile, char **envp, int *fd)
{
	char **cmd;
	char **dirs;
	int infile_fd;

	infile_fd = open(infile, O_RDONLY);
	// if (infile_fd < 0)
	// 	permission_denied(fd);
	dirs = init_dirs(envp);
	cmd = check_for_command(command, dirs);
	close(fd[0]);
	if (dup2(infile_fd, 0) == -1 || dup2(fd[1], 1) == -1)
	{
		free_list(dirs);
		error_free_exit(fd, cmd);
	}
	close(fd[1]);
	close(infile_fd);
	free_list(dirs);
	if (execve(cmd[0], cmd, envp) == -1)
		error_free_exit(fd, cmd);
}

void last_command(char *command, char *outfile, char **envp, int *fd)
{
	char **cmd;
	char **dirs;
	int outfile_fd;

	outfile_fd = open(outfile,  O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd < 0)
		permission_denied(fd);
	dirs = init_dirs(envp);
	cmd = check_for_command(command, dirs);
	close(fd[1]);
	if (dup2(outfile_fd, 1) == -1 || dup2(fd[0], 0) == -1)
	{
		free_list(dirs);
		error_free_exit(fd, cmd);
	}
	close(fd[0]);
	close(outfile_fd);
	free_list(dirs);
	if (execve(cmd[0], cmd, envp) == -1)
		error_free_exit(fd, cmd);
}

void running_processes(char **argv, char **envp, int *fd)
{
	int pid1;
	int pid2;

	pid1 = fork();
	if (pid1 == 0)
		first_command(argv[2], argv[1], envp, fd);
	else
	{
		pid2 = fork();
		if (pid2 == 0)
			last_command(argv[3], argv[4], envp, fd);
		wait(NULL);
		wait(NULL);
	}
}

int main(int argc, char *argv[], char **envp)
{
	int *fd;

	if (argc != 5)
		error_exit();
	if (access(argv[1], F_OK) == -1)
		write(2, "No such file or directory\n", 26);
	fd = init_fd();
	if (!fd)
		return (0);
	running_processes(argv, envp, fd);

	//system("leaks pipex");
}
