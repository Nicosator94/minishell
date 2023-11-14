/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agomes-g <agomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:10:33 by agomes-g          #+#    #+#             */
/*   Updated: 2023/10/24 10:30:07 by agomes-g         ###   ########.fr       */
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

void	export_annexe(char **cmd, t_env **env)
{
	t_env	*new;
	int		check;
	int		i;

	i = 0;
	while (cmd[++i])
	{
		new = new_element(get_name(cmd[i]), get_value(cmd[i]), cmd[i]);
		if (!new)
			return (all_clear_command(*env, NULL));
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
}

void	export(char **cmd, t_env **env)
{
	int		i;

	if (!cmd[1])
		return (print_sort_list(*env));
	i = 0;
	while (cmd[++i])
	{
		if (!check_parsing(cmd[i]))
			return (ft_putstr_fd("not a valid identifier\n", 1));
	}
	export_annexe(cmd, env);
}
