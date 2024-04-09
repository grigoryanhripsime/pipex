/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:33:34 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/04/09 18:47:43 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	running_processes(t_cmd *cmd)
{
	int	pid;
	int	i;

	while (cmd -> cmd_index < cmd -> argc - 1)
	{
		pid = fork();
		if (pid == 0)
		{
			if ((cmd -> cmd_index) == 2)
				first_command(cmd);
			else if (cmd -> cmd_index == cmd -> argc - 2)
				last_command(cmd);
			else
				middle_command(cmd);
		}
		(cmd -> cmd_index)++;
	}
	close_fd(cmd);
	i = 0;
	while (i++ < cmd -> argc - 2)
		wait(NULL);
}

int	main(int argc, char *argv[], char **envp)
{
	t_cmd	*cmd;
	char	**dirs;

	if (argc < 5)
		error_exit();
	cmd = malloc(sizeof(t_cmd));
	cmd -> argc = argc;
	cmd -> argv = argv;
	cmd -> envp = envp;
	init_fd(cmd);
	dirs = init_dirs(envp);
	cmd -> dirs = dirs;
	cmd -> cmd_index = 2;
	running_processes(cmd);
	system("leaks pipex");
	return (0);
}
