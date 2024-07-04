/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:42:25 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/04/18 17:09:56 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_fd(t_cmd *cmd)
{
	int	(*fd)[2];
	int	i;

	i = 0;
	fd = malloc(sizeof(int [2]) * (cmd -> argc - 3));
	if (!fd)
	{
		free(cmd);
		exit(1);
	}
	while (i < cmd -> argc - 2)
	{
		if (pipe(fd[i]) == -1)
		{
			while (i > 0)
			{
				close(fd[i][0]);
				close(fd[i--][1]);
			}
			free(fd);
			exit(1);
		}
		i++;
	}
	cmd -> fd = fd;
}

void	init_dirs(t_cmd *cmd)
{
	int		i;
	char	**dirs;

	i = 0;
	while (cmd -> envp[i])
	{
		if (ft_strstr(cmd -> envp[i], "PATH="))
			break ;
		i++;
	}
	dirs = ft_split(cmd -> envp[i] + 5, ':');
	if (!dirs)
	{
		close_fd(cmd);
		free(cmd);
		print_error("There are no directories found.\n");
		exit(1);
	}
	cmd -> dirs = dirs;
}

void	open_infile(t_cmd *cmd)
{
	int		infile_fd;

	if (cmd -> here_doc)
	{
		here_doc(cmd -> argv[2], cmd);
		cmd -> cmd_index++;
		doing_dups(cmd -> fd[0][0], cmd -> fd[1][1], cmd);
	}
	else
	{
		infile_fd = open(cmd -> argv[1], O_RDONLY);
		if (access(cmd -> argv[1], F_OK) == -1)
			error_free_exit(cmd -> argv[1],
				": No such file or directory\n", cmd);
		else if (infile_fd < 0)
			error_free_exit(cmd -> argv[1], ": Permition denied\n", cmd);
		doing_dups(infile_fd, cmd -> fd[0][1], cmd);
		close(infile_fd);
	}
}
