/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 07:45:29 by agomes-g          #+#    #+#             */
/*   Updated: 2023/10/12 11:42:59 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void my_env(char **cmd, t_env *env) 
{
    t_env	*lst;

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
			printf("%s=\"\"\n", lst->name);
        lst = lst->next;
    }
}
