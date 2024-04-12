/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:33:47 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/04/12 17:25:30 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		write(2, str + i, 1);
		i++;
	}
}

void	close_fd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd -> argc - 4)
	{
		close(cmd -> fd[i][1]);
		close(cmd -> fd[i][0]);
		i++;
	}
}

void	free_struct(t_cmd *cmd)
{
	int	i;

	free(cmd -> fd);
	i = 0;
	while (cmd -> dirs[i])
	{
		free(cmd -> dirs[i]);
		i++;
	}
	free(cmd -> dirs);
	free(cmd);
}

void	command_not_found(t_cmd *cmd, char **command)
{
	int	i;

	print_error(command[0]);
	print_error(": command not found\n");
	close_fd(cmd);
	free_struct(cmd);
	i = 0;
	while (command[i])
	{
		free(command[i]);
		i++;
	}
	free(command);
	exit(1);
}

void	error_free_exit(char *name, char *error, t_cmd *cmd)
{
	print_error(name);
	print_error(error);
	close_fd(cmd);
	free_struct(cmd);
	exit(1);
}
