/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:53:04 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/04/18 16:31:14 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

char	**check_for_command(t_cmd *cmd)
{
	char	**command;
	char	*cmd1;

	command = ft_split(cmd -> argv[cmd -> cmd_index], ' ');
	cmd1 = check_in_dirs(ft_strdup(command[0]), cmd);
	if (!cmd1)
	{
		if (access(command[0], X_OK) != -1)
			return (command);
		command_not_found(cmd, command);
	}
	else
	{
		free(command[0]);
		command[0] = cmd1;
	}
	return (command);
}

void	doing_dups(int infile, int outfile, t_cmd *cmd)
{
	if (dup2(infile, 0) == -1 || dup2(outfile, 1) == -1)
	{
		print_error("Dup failed\n");
		close_fd(cmd);
		if (cmd -> cmd_index == 2)
			close(infile);
		else if (cmd -> cmd_index == cmd -> argc - 2)
			close(outfile);
		error_free_exit(0, 0, cmd);
	}
	close_fd(cmd);
}

void	first_command(t_cmd *cmd)
{
	char	**command;
	int		i;

	open_infile(cmd);
	command = check_for_command(cmd);
	if (execve(command[0], command, cmd -> envp) == -1)
	{
		i = 0;
		while (command[i])
			free(command[i++]);
		free(command);
		error_free_exit(0, "Executing command failed\n", cmd);
	}
}

void	middle_command(t_cmd *cmd)
{
	char	**command;
	int		i;

	i = cmd -> cmd_index;
	doing_dups(cmd -> fd[i - 3][0], cmd -> fd[i - 2][1], cmd);
	command = check_for_command(cmd);
	if (execve(command[0], command, cmd -> envp) == -1)
	{
		i = 0;
		while (command[i])
			free(command[i++]);
		free(command);
		error_free_exit(0, "Executing command failed\n", cmd);
	}
}

void	last_command(t_cmd *cmd)
{
	char	**command;
	int		outfile_fd;
	int		i;

	i = cmd -> cmd_index;
	if (cmd -> here_doc)
		outfile_fd = open(cmd -> argv[cmd -> argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		outfile_fd = open(cmd -> argv[cmd -> argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
		error_free_exit(0, "Coudn't open the file\n", cmd);
	doing_dups(cmd -> fd[i - 3][0], outfile_fd, cmd);
	close(outfile_fd);
	close_fd(cmd);
	command = check_for_command(cmd);
	if (execve(command[0], command, cmd -> envp) == -1)
	{
		i = 0;
		while (command[i])
			free(command[i++]);
		free(command);
		error_free_exit(0, "Executing command failed\n", cmd);
	}
}
