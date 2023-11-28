/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_failed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:19:05 by niromano          #+#    #+#             */
/*   Updated: 2023/11/21 11:19:27 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	directory_check(char *cmd)
{
	struct stat	buf;

	stat(cmd, &buf);
	if (buf.st_mode & __S_IFDIR)
		return (0);
	return (1);
}

static int	print_file_error(char *cmd, int trig)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (trig == 1)
	{
		if (access(cmd, F_OK) == 0 && directory_check(cmd) == 0)
		{
			ft_putstr_fd(": Is a directory\n", 2);
			return (126);
		}
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
		ft_putstr_fd(": command not found\n", 2);
	return (127);
}

int	print_failed(char *cmd)
{
	int	i;
	int	trig;

	i = 0;
	trig = 0;
	if (cmd == NULL)
		return (0);
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			trig = 1;
		i ++;
	}
	return (print_file_error(cmd, trig));
}

void	exec_failed(t_mini *minishell, char *path, char **mat_env, char *cmd)
{
	int	i;
	int	return_value;

	i = 0;
	if (path != NULL)
		free(path);
	while (mat_env[i] != NULL && mat_env != NULL)
	{
		free(mat_env[i]);
		i ++;
	}
	if (mat_env != NULL)
		free(mat_env);
	return_value = print_failed(cmd);
	clear_all(minishell);
	exit(return_value);
}
