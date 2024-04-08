#include "pipex.h"

void running_processes(t_cmd *cmd)
{
	int pid;
	int i;

	while (cmd -> cmd_index < cmd -> argc - 1)
	{
		pid = fork();
		if (pid > 0)
			cmd -> child_pid = pid;
		if (pid == 0)
		{
			cmd -> valid = 1;
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

int main(int argc, char *argv[], char **envp)
{
	t_cmd *cmd;
	char **dirs;

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
	//system("leaks pipex");
}
