#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char **envp);
size_t	ft_strlen(const char *s);
char	*ft_strstr(char *str, char *to_find);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void free_list(char **arr);
void error_exit(void);

#endif