/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:33:20 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/04/18 16:29:19 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"

typedef struct s_cmd
{
	int		(*fd)[2]; //malloced
	int		argc;
	char	**argv;
	char	**envp;
	int		cmd_index;
	char	**dirs; //malloced
	int		here_doc;
}	t_cmd;

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strstr(char *str, char *to_find);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
void	free_struct(t_cmd *cmd);
char	*check_in_dirs(char *command, t_cmd *cmd);
void	command_not_found(t_cmd *cmd, char **command);
void	print_error(char *str);
void	init_fd(t_cmd *cmd);
void	init_dirs(t_cmd *cmd);
void	open_infile(t_cmd *cmd);
void	doing_dups(int infile, int outfile, t_cmd *cmd);
void	error_free_exit(char *name, char *error, t_cmd *cmd);
char	**check_for_command(t_cmd *cmd);
void	first_command(t_cmd *cmd);
void	middle_command(t_cmd *cmd);
void	last_command(t_cmd *cmd);
void	close_fd(t_cmd *cmd);
void	running_processes(t_cmd *cmd);
void	here_doc(char *limiter, t_cmd *cmd);

#endif
