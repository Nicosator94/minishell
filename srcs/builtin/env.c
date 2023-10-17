/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agomes-g <agomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 07:45:29 by agomes-g          #+#    #+#             */
/*   Updated: 2023/10/17 21:42:13 by agomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_env(char **cmd, t_env *env)
{
	t_env	*lst;

	if (!env)
		return ;
	lst = env;
	if (cmd[1])
	{
		printf("Invalid option/args\n");
		return ;
	}
	while (lst != NULL)
	{
		if (lst->value)
			printf("%s=%s\n", lst->name, lst->value);
		else if (lst->val)
			printf("%s=\n", lst->name);
		lst = lst->next;
	}
}
