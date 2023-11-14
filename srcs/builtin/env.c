/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agomes-g <agomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 07:45:29 by agomes-g          #+#    #+#             */
/*   Updated: 2023/10/24 09:51:39 by agomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_env(t_env *env)
{
	t_env	*lst;

	if (!env)
		return ;
	lst = env;
	while (lst != NULL)
	{
		if (!lst->val)
			lst = lst->next;
		if (lst == NULL)
			return ;
		if (lst->value)
			printf("%s=%s\n", lst->name, lst->value);
		lst = lst->next;
	}
}
