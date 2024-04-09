/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:42:25 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/04/09 18:50:41 by hrigrigo         ###   ########.fr       */
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
		return ;
	while (i < cmd -> argc - 2)
	{
		if (pipe(fd[i]) == -1)
		{
			free(fd);
			error_exit();
		}
		i++;
	}
	cmd -> fd = fd;
}

char	**init_dirs(char **envp)
{
	int		i;
	char	**dirs;

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
