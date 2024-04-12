/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:33:20 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/04/12 17:25:49 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_cmd
{
	int		(*fd)[2]; //malloced
	int		argc;
	char	**argv;
	char	**envp;
	int		cmd_index;
	char	**dirs; //malloced
}	t_cmd;

size_t	ft_strlen(const char *s);
char	*ft_strstr(char *str, char *to_find);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);

void	free_struct(t_cmd *cmd);
void	command_not_found(t_cmd *cmd, char **command);
void	print_error(char *str);

void	init_fd(t_cmd *cmd);
void	init_dirs(t_cmd *cmd);

void	error_free_exit(char *name, char *error, t_cmd *cmd);
char	**check_for_command(t_cmd *cmd);
void	first_command(t_cmd *cmd);
void	middle_command(t_cmd *cmd);
void	last_command(t_cmd *cmd);
void	close_fd(t_cmd *cmd);

void	running_processes(t_cmd *cmd);
int		main(int argc, char *argv[], char **envp);

#endif
