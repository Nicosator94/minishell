/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 06:26:17 by agomes-g          #+#    #+#             */
/*   Updated: 2023/10/12 11:48:38 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void printList(t_env *env) 
{
    t_env	*lst;

	lst = env;
    while (lst != NULL)
	{
        printf("export %s", lst->name);
		if (lst->value != NULL)
			printf("=\"%s\"", lst->value);
		else if (lst->val)
			printf("=\"\"");
		printf("\n");
        lst = lst->next;
    }
}


void	delete_element(char *name, t_env **env)
{
	t_env	*tmp;
	t_env	*new;

	tmp = *env;
	new = NULL;
	if (!(ft_strncmp((*env)->name, name, ft_strlen((*env)->name))))
	{
		*env = (*env)->next;
		if (tmp->value)
			free(tmp->value);
		return (free(tmp->name), free(tmp));
	}
	while (tmp && (ft_strncmp(tmp->name, name, ft_strlen(tmp->name)) != 0))
	{
		new = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		new->next = tmp->next;
		if (tmp->value)
			free(tmp->value);
		return (free(tmp->name), free(tmp));
	}
}

void	unset(char **cmd, t_env **env)
{
	int		i;

	i = 1;
	if (!cmd[1] || !env)
		return ;
	if (cmd[i][0] == '-')
	{
		printf("Invalid option\n");
		return ;
	}
	while (cmd[i])
	{
		delete_element(cmd[i], env);
		i ++;
	}
}
