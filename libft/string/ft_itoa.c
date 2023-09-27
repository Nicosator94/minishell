/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:29:30 by niromano          #+#    #+#             */
/*   Updated: 2023/05/10 10:54:30 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*zero(void)
{
	char	*nb;

	nb = malloc(sizeof(char) * 2);
	if (nb == NULL)
		return (NULL);
	nb[0] = '0';
	nb[1] = '\0';
	return (nb);
}

static char	*init(char *nb, int moins, long tmp, int i)
{
	nb[i] = '\0';
	while (i > 0)
	{
		nb[i - 1] = tmp % 10 + 48;
		tmp = tmp / 10;
		i --;
	}
	if (moins == 1)
		nb[0] = '-';
	return (nb);
}

char	*ft_itoa(int n)
{
	int		i;
	int		moins;
	long	temp;
	char	*nb;

	i = 0;
	moins = 0;
	temp = n;
	if (temp < 0)
	{
		temp = -temp;
		moins ++;
		i ++;
	}
	if (temp == 0)
		return (zero());
	while (n != 0)
	{
		n = n / 10;
		i ++;
	}
	nb = malloc(sizeof(char) * (i + 1));
	if (nb == NULL)
		return (NULL);
	return (init(nb, moins, temp, i));
}
