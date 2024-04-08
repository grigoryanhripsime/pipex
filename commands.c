#include "pipex.h"

char **check_for_command(t_cmd *cmd)
{
	char **command;
	int i;
	char *joined_cmd;

	command = ft_split(cmd -> argv[cmd -> cmd_index], ' ');
	if (access(command[0], X_OK) != -1)
		return (command);
	i = 0;
	while (cmd -> dirs[i])
	{
		joined_cmd = ft_strjoin(cmd -> dirs[i], command[0]);
		if (access(joined_cmd, X_OK) != -1)
		{
			free(command[0]);
			command[0] = joined_cmd;
			break ;
		}
		free(joined_cmd);
		i++;
	}
	if (!cmd -> dirs[i])
		command_not_found(cmd);
	return (command);
}

void first_command(t_cmd *cmd)
{
	char **command;
	int infile_fd;

	infile_fd = open(cmd -> argv[1], O_RDONLY);
	if (access(cmd -> argv[1], F_OK) == -1)
	{
		print_str(cmd -> argv[1]);
		print_str(": No such file or directory\n");
		cmd -> valid = 0; 
	}
	else if (infile_fd < 0)
		permission_denied(cmd);
	if (cmd -> valid == 0)
		return ;
	command = check_for_command(cmd);
	if (cmd -> valid == 0 || dup2(infile_fd, 0) == -1 || dup2(cmd -> fd[0][1], 1) == -1)
	{
		free(command);
		return ;
	}
	close_fd(cmd);
	close(infile_fd);
	execve(command[0], command, cmd -> envp);
}

void middle_command(t_cmd *cmd)
{
	char **command;
	int i;

	i = cmd -> cmd_index;
	command = check_for_command(cmd);
	if (cmd -> valid == 0 || dup2(cmd -> fd[i - 2][1], 1) == -1 || dup2(cmd -> fd[i - 3][0], 0) == -1)
	{
		free(command);
		return ;
	}
	close_fd(cmd);
	execve(command[0], command, cmd -> envp);
}

void last_command(t_cmd *cmd)
{
	char **command;
	int outfile_fd;
	int i;

	i = cmd -> cmd_index;
	outfile_fd = open(cmd -> argv[cmd -> argc - 1],  O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		free_struct(cmd);
		error_exit();
	}
	command = check_for_command(cmd);
	if (cmd -> valid == 0 || dup2(outfile_fd, 1) == -1 || dup2(cmd -> fd[i - 3][0], 0) == -1)
	{
		free(command);
		return ;
	}
	close_fd(cmd);
	close(outfile_fd);
	execve(command[0], command, cmd -> envp);
}

void close_fd(t_cmd *cmd) 
{
	int i;

	i = 0;
	while (i < cmd -> argc - 2)
	{
		close(cmd -> fd[i][1]);
		close(cmd -> fd[i][0]);
		i++;
	}
}