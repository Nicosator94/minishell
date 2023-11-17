/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agomes-g <agomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:00:36 by agomes-g          #+#    #+#             */
/*   Updated: 2023/11/17 11:08:13 by agomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*gethome(t_env *env, int val)
{
	t_env	*tmp;

	tmp = env;
	if (!val)
	{
		while (tmp && ft_strncmp(tmp->name, "HOME", 5) != 0)
			tmp = tmp->next;
		if (tmp)
			return (tmp->value);
	}
	else
	{
		while (tmp && ft_strncmp(tmp->name, "OLDPWD", 7) != 0)
			tmp = tmp->next;
		if (tmp)
			return (tmp->value);
	}
	return (NULL);
}

int	change_current(t_env **env)
{
	char	*current;
	int		check;
	t_env	*new_current;

	current = getcwd(NULL, 0);
	if (!current)
		return (-2);
	new_current = new_element("PWD", current, "=ok");
	if (!new_current)
		return (free(current), -2);
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
		return (-2);
	check = check_occurence(env, new_old);
	if (!(check))
		add_back(env, new_old);
	else if (check == 2)
		clear_env(new_old);
	else
		free(new_old);
	return (change_current(env));
}

int	annexe(char	*s, t_env *env)
{
	char	*path;

	if (s[0] == '-' && !s[1])
	{
		path = gethome(env, 1);
		if (!path)
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), 1);
		if (chdir(path) != 0)
			return (ft_putstr_fd("minishell: cd: Bad file\n", 2), 1);
		else
		{
			ft_putstr_fd(path, 1);
			ft_putchar_fd('\n', 1);
		}
	}
	else
	{
		if (chdir(s) != 0)
			return (ft_putstr_fd("minishell: cd: ", 2), ft_putstr_fd(s, 2),
				ft_putstr_fd(": No such file or directory\n", 2), 1);
	}
	return (0);
}

int	cd(char **cmd, t_env **env)
{
	char	*home;
	char	*old;

	if (cmd[1] && cmd[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	old = getcwd(NULL, 0);
	if (!old)
		return (-2);
	if (!cmd[1] || (cmd[1][0] == '~' && !cmd[1][1]))
	{
		home = gethome(*env, 0);
		if (!home)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2),
				free(old), 1);
		if (chdir(home) != 0)
			return (ft_putstr_fd("minishell: cd: Bad file\n", 2), free(old), 1);
	}
	else
	{
		if (annexe(cmd[1], *env))
			return (free(old), 1);
	}
	return (change_path(old, env));
}
