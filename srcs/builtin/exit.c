/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 08:02:36 by agomes-g          #+#    #+#             */
/*   Updated: 2023/11/15 10:38:37 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

unsigned long long	ft_atoi_ulong(const char *nptr)
{
	int				i;
	unsigned long	s;
	unsigned long	conv;

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
	return (conv);
}

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
	unsigned long	nb;

	if (ft_atoi_long(s) < 0)
		nb = (-1) * ft_atoi_long(s);
	else
		nb = ft_atoi_long(s);
	if (ft_atoi_ulong(s) != nb)
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
		{
			sign ++;
			i ++;
		}	
		if (!((s[i] >= '0' && s[i] <= '9') || (s[i] >= 9 && s[i] <= 13)
				|| s[i] == ' ' || sign >= 2))
			return (0);
		i ++;
	}
	return (1);
}

unsigned int	my_exit(char **cmd)
{
	if (!cmd[1])
		return (-3);
	if (!digits_spaces(cmd[1]) || !ft_overflow(cmd[1]))
	{
		ft_putstr_fd("minishell: exit : ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	if (cmd[1])
	{
		if (cmd[2])
		{
			ft_putstr_fd("minishell: exit : Too many arguments\n", 2);
			return (-1);
		}
	}
	return ((unsigned char)ft_atoi_long(cmd[1]));
}
