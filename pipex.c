/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:33:34 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/04/12 17:25:30 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_childs(t_cmd *cmd)
{
	int	i;

	close_fd(cmd);
	i = 0;
	while (i++ < cmd -> argc - 2)
		wait(NULL);
}

void	running_processes(t_cmd *cmd)
{
	int	pid;

	while (cmd -> cmd_index < cmd -> argc - 1)
	{
		pid = fork();
		if (pid == -1)
		{
			free_struct(cmd);
			print_error("Fork ended with error.\n");
			exit(1);
		}
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
	wait_childs(cmd);
}

int	main(int argc, char *argv[], char **envp)
{
	t_cmd	*cmd;

	if (argc < 5)
		exit(1);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		exit(1);
	cmd -> argc = argc;
	cmd -> argv = argv;
	cmd -> envp = envp;
	init_fd(cmd);
	init_dirs(cmd);
	cmd -> cmd_index = 2;
	running_processes(cmd);
	free_struct(cmd);
	//system("leaks pipex");
	return (0);
}
