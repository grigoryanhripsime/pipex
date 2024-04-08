#include "pipex.h"

void print_str(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(2, str + i, 1);
		i++;
	}
}

void error_exit(void)
{
	//system("leaks pipex");
	exit(1);
}

void free_struct(t_cmd *cmd)
{
	int i;

	free(cmd -> fd);
	i = 0;
	while (cmd -> dirs[i])
	{
		free(cmd -> dirs[i]);
		i++;
	}
	free(cmd -> dirs);
}
void command_not_found(t_cmd *cmd)
{
	print_str(cmd -> argv[cmd -> cmd_index]);
	print_str(": command not found\n");
	cmd -> valid = 0; 

}

void permission_denied(t_cmd *cmd)
{
	print_str(cmd -> argv[1]);
	print_str(": Permission denied\n");
	cmd -> valid = 0; 
}

