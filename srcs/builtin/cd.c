/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agomes-g <agomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:00:36 by agomes-g          #+#    #+#             */
/*   Updated: 2023/10/24 12:38:43 by agomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*gethome(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp && ft_strncmp(tmp->name, "HOME", 5) != 0)
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

int	change_current(t_env **env)
{
	char	*current;
	int		check;
	t_env	*new_current;

	current = getcwd(NULL, 0);
	if (!current)
		return (perror("Can't get pwd"), clear_env(*env), 0);
	new_current = new_element("PWD", current, "=ok");
	if (!new_current)
		return (all_clear_command(*env, NULL), 0);
	check = check_occurence(env, new_current);
	if (!(check))
		add_back(env, new_current);
	else if (check == 2)
		clear_env(new_current);
	else
		free(new_current);
	return (0);
}

int	change_path(char *old, t_env **env)
{
	
	int		check;
	t_env	*new_old;

	new_old = new_element("OLDPWD", old, "=ok");
	if (!new_old)
		return (all_clear_command(*env, NULL), 0);
	check = check_occurence(env, new_old);
	if (!(check))
		add_back(env, new_old);
	else if (check == 2)
		clear_env(new_old);
	else
		free(new_old);
	return (change_current(env));
}

int	cd(char **cmd, t_env **env)
{
	int		i;
	char	*home;
	char	*old;

	i = 1;
	if (count(cmd) > 1)
		return (ft_putstr_fd("too many arguments\n", 1), 1);
	old = getcwd(NULL, 0);
	if (!old)
		return (perror("Can't get pwd"), clear_env(*env), 0);
	if (!cmd[i])
	{
		home = gethome(*env);
		if (!home)
			return (ft_putstr_fd("HOME not set\n", 1), 1);
		if (chdir(home) != 0)
			return (perror ("Bad file\n"), 1);
	}
	else
	{
		if (chdir(cmd[i]) != 0)
			return (perror(cmd[i]), 1);
	}
	return (change_path(old, env));
}
