/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agomes-g <agomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 07:45:29 by agomes-g          #+#    #+#             */
/*   Updated: 2023/11/14 08:38:58 by agomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	my_env(t_env *env)
{
	t_env	*lst;

	if (!env)
		return (0);
	lst = env;
	while (lst != NULL)
	{
		if (!lst->val)
			lst = lst->next;
		if (lst == NULL)
			return (0);
		if (lst->value)
			printf("%s=%s\n", lst->name, lst->value);
		lst = lst->next;
	}
	return (0);
}
