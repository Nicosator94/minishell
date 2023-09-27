/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:36:17 by niromano          #+#    #+#             */
/*   Updated: 2023/05/10 10:10:41 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	char	nb[10];
	long	temp;

	i = 0;
	temp = n;
	if (temp == 0)
		ft_putchar_fd('0', fd);
	if (temp < 0)
	{
		ft_putchar_fd('-', fd);
		temp = -temp;
	}
	while (temp > 0)
	{
		nb[i] = temp % 10 + 48;
		temp = temp / 10;
		i ++;
	}
	while (i > 0)
	{
		ft_putchar_fd(nb[i - 1], fd);
		i --;
	}
}
