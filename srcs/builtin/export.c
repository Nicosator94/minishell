/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:10:33 by agomes-g          #+#    #+#             */
/*   Updated: 2023/11/14 09:22:02 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_parsing(char *cmd)
{
	int	i;

	i = 1;
	if (!((cmd[0] >= 'a' && cmd[0] <= 'z')
			|| (cmd[0] >= 'A' && cmd[0] <= 'Z') || cmd[0] == '_'))
		return (0);
	while (cmd[i] && cmd[i] != '=')
	{
		if (!((cmd[i] >= 'a' && cmd[i] <= 'z')
				|| (cmd[i] >= 'A' && cmd[i] <= 'Z')
				|| (cmd[i] >= '0' && cmd[i] <= '9') || cmd[i] == '_'))
			return (0);
		i ++;
	}
	if (cmd[i])
	{
		i ++;
		while (cmd[i])
		{
			if (!ft_isprint(cmd[i]))
				return (0);
			i ++;
		}
	}
	return (1);
}

int	check_occurence(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!(*env))
		return (0);
	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, new->name, ft_strlen(new->name) + 1) == 0)
		{
			if (new->val)
			{
				if (tmp->value && tmp->value[0] != '\0')
					free(tmp->value);
				tmp->value = new->value;
				tmp->val = new->val;
				return (1);
			}
			return (2);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	export_annexe(char **cmd, t_env **env)
{
	t_env	*new;
	int		check;
	int		i;

	i = 0;
	while (cmd[++i])
	{
		new = new_element(get_name(cmd[i]), get_value(cmd[i]), cmd[i]);
		if (!new)
			return (-2);
		check = check_occurence(env, new);
		if (!(check))
			add_back(env, new);
		else if (check == 2)
			clear_env(new);
		else
		{
			free(new->name);
			free(new);
		}
	}
	return (0);
}

int	export(char **cmd, t_env **env)
{
	int		i;

	if (!cmd[1])
		return (print_sort_list(*env));
	i = 0;
	while (cmd[++i])
	{
		if (!check_parsing(cmd[i]))
			return (ft_putstr_fd("not a valid identifier\n", 1), 1);
	}
	return (export_annexe(cmd, env));
}
