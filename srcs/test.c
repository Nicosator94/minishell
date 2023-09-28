
#include "../includes/minishell.h"

void	exec(char *cmd, char **env)
{
	pid_t	pid;
	char	*path = "/usr/bin/clear";
	char	**cmd1;

	(void)cmd;
	cmd1 = malloc(sizeof(char *) * 2);
	cmd1[0] = "clear";
	cmd1[1] = NULL;
	pid = fork();
	if (pid == 0)
	{
		execve(path, cmd1, env);
		printf("error\n");
		exit(0);
	}
	if (pid != 0)
		wait(NULL);
}
