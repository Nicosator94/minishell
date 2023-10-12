/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 08:36:23 by agomes-g          #+#    #+#             */
/*   Updated: 2023/10/12 11:42:48 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_option(char *opt)
{
	int i;

	i = 1;
	if (!opt)
		return (0);
	if (opt[0] != '-')
		return (0);
	if (!opt[i])
		return (0);
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (0);
		i ++;
	}
	return (1);
}

void	my_echo(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!cmd[i])
	{
		printf("\n");
		return;
	}
	while(check_option(cmd[i]))
	{
		j ++;
		i ++;
	}
	while(cmd[i])
	{
		printf("%s", cmd[i]);
		i ++;
		if (cmd[i])
			printf(" ");
	}
	if (!j)
		printf("\n");
}
