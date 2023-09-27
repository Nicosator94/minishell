/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_itoa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 06:47:17 by niromano          #+#    #+#             */
/*   Updated: 2023/05/16 06:47:19 by niromano         ###   ########.fr       */
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

static char	*init(char *nb, long tmp, int i)
{
	nb[i] = '\0';
	while (i > 0)
	{
		nb[i - 1] = tmp % 10 + 48;
		tmp = tmp / 10;
		i --;
	}
	return (nb);
}

char	*ft_unsigned_itoa(unsigned int n)
{
	int		i;
	long	tmp;
	char	*nb;

	i = 0;
	tmp = n;
	if (tmp == 0)
		return (zero());
	while (n != 0)
	{
		n = n / 10;
		i ++;
	}
	nb = malloc(sizeof(char) * (i + 1));
	if (nb == NULL)
		return (NULL);
	return (init(nb, tmp, i));
}
