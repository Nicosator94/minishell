/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:00:36 by agomes-g          #+#    #+#             */
/*   Updated: 2023/10/12 11:42:40 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*gethome(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp && ft_strncmp(tmp->name, "HOME", 4) != 0)
		tmp = tmp->next;
	if (tmp)
		return (tmp->value);
	return (NULL);
}

int	count(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i + 1])
		i ++;
	return (i);
}

int	cd(char **cmd, t_env *env)
{
	int i;
	char *home;

	i = 1;
	if (count(cmd) > 1)
		return (ft_putstr_fd("too many arguments", 1), 1);
	if (!cmd[i])
	{
		home = gethome(env);
		if (!home)
			return (ft_putstr_fd("Can't access to home", 1), 1);
		if (chdir(home) != 0)
			return (perror ("Bad file"), 1);
	}
	else
	{
		if (chdir(cmd[i]) != 0)
			return (perror(cmd[i]), 1);
	}
	return (0);
}
