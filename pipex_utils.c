/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:30:40 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/04/18 16:30:41 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_in_dirs(char *command, t_cmd *cmd)
{
	int		i;
	char	*joined_cmd;

	i = 0;
	while (cmd -> dirs[i])
	{
		joined_cmd = ft_strjoin(cmd -> dirs[i], command);
		if (access(joined_cmd, X_OK) != -1)
		{
			free(command);
			command = joined_cmd;
			break ;
		}
		free(joined_cmd);
		i++;
	}
	if (!cmd -> dirs[i])
		return (0);
	return (command);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1_size;
	size_t	s2_size;
	char	*s3;
	int		i;

	i = 0;
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	s3 = (char *)malloc(sizeof(char) * (s1_size + s2_size + 2));
	if (!s3)
		return (NULL);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	s3[i++] = '/';
	while (s2[i - s1_size - 1])
	{
		s3[i] = s2[i - s1_size - 1];
		i++;
	}
	s3[i] = '\0';
	return (s3);
}

char	*ft_strstr(char *str, char *to_find)
{
	int		i;
	int		j;

	i = 0;
	if (*to_find == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] != '\0' && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == 0)
				return (&str[i]);
			j++;
		}
		i++;
	}
	return (0);
}
