/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:24:47 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/04/18 17:03:59 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"
#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2 || n <= 0)
		return (-2);
	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return (1);
		if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return (-1);
		i++;
	}
	return (0);
}

void	here_doc(char *limiter, t_cmd *cmd)
{
	char	*str;
	int		len;

	while (1)
	{
		str = get_next_line(0);
		if (!ft_strncmp(str, limiter, ft_strlen(str) - 1))
		{
			free(str);
			break ;
		}
		len = ft_strlen(str);
		write(cmd -> fd[0][1], str, len);
		free(str);
	}
	close(cmd -> fd[0][1]);
}
