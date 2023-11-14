/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agomes-g <agomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 08:02:36 by agomes-g          #+#    #+#             */
/*   Updated: 2023/10/24 09:45:33 by agomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

long	ft_atoi_long(const char *nptr)
{
	int		i;
	long	s;
	long	conv;

	i = 0;
	conv = 0;
	s = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i ++;
	if (nptr[i] != '-' && !(nptr[i] >= 48 && nptr[i] <= 57) && nptr[i] != '+')
		return (0);
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			s = -1;
		i ++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		conv = (conv * 10) + (nptr[i] - '0');
		i ++;
	}
	return (s * conv);
}

int	ft_overflow(char *s)
{
	if (ft_atoi_long(s) != ft_atoi(s))
		return (0);
	return (1);
}

int	digits_spaces(char *s)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	while (s[i] && sign < 2)
	{
		if (s[i] == '-' || s[i] == '+')
			sign ++;
		if (!((s[i] >= '0' && s[i] <= '9') || (s[i] >= 9 && s[i] <= 13)
				|| s[i] == ' ' || sign < 2))
			return (0);
		i ++;
	}
	return (1);
}

unsigned int	my_exit(char **cmd, t_env *env)
{
	printf ("exit\n");
	if (cmd[1])
	{
		if (cmd[2])
		{
			printf("minishell: exit : Too many arguments\n");
			return (1);
		}
	}
	clear_env(env);
	if (!cmd[1])
		exit(0);
	if (!digits_spaces(cmd[1]) || !ft_overflow(cmd[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
		exit (2);
	}
	else
		exit((unsigned int)ft_atoi(cmd[1]));
}
