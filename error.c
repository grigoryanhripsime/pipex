#include "pipex.h"

void error_exit(void)
{
	//write(2, "Error\n", 6);
	//system("leaks push_swap");
	exit(1);
}

void free_list(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

