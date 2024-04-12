/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:53:04 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/04/12 17:22:41 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**check_for_command(t_cmd *cmd)
{
	char	**command;
	int		i;
	char	*joined_cmd;

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
		command_not_found(cmd, command);
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
	int		infile_fd;
	int		i;

	infile_fd = open(cmd -> argv[1], O_RDONLY);
	if (access(cmd -> argv[1], F_OK) == -1)
		error_free_exit(cmd -> argv[1], ": No such file or directory\n", cmd);
	else if (infile_fd < 0)
		error_free_exit(cmd -> argv[1], ": Permition denied\n", cmd);
	doing_dups(infile_fd, cmd -> fd[0][1], cmd);
	close(infile_fd);
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
