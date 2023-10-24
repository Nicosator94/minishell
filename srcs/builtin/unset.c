/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agomes-g <agomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 06:26:17 by agomes-g          #+#    #+#             */
/*   Updated: 2023/10/24 10:20:48 by agomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_element(char *name, t_env **env)
{
	t_env	*tmp;
	t_env	*new;

	new = NULL;
	tmp = *env;
	if (!(ft_strncmp(tmp->name, name, ft_strlen(tmp->name) + 1)))
	{
		*env = tmp->next;
		if (tmp->value && tmp->value[0] != '\0')
			free(tmp->value);
		return (free(tmp->name), free(tmp));
	}
	while (tmp && (ft_strncmp(tmp->name, name, ft_strlen(tmp->name) + 1) != 0))
	{
		new = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		new->next = tmp->next;
		if (tmp->value && tmp->value[0] != '\0')
			free(tmp->value);
		return (free(tmp->name), free(tmp));
	}
}

void	unset(char **cmd, t_env **env)
{
	int		i;

	i = 1;
	if (!cmd[1] || !(*env))
		return ;
	while (cmd[i])
	{
		delete_element(cmd[i], env);
		i ++;
	}
}
