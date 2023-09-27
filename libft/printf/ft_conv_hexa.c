/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_hexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 07:28:22 by niromano          #+#    #+#             */
/*   Updated: 2023/05/16 07:28:23 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*zero(void)
{
	char	*s;

	s = malloc(sizeof(char) * 2);
	if (s == NULL)
		return (NULL);
	s[0] = '0';
	s[1] = '\0';
	return (s);
}

char	*ft_conv_hexa(unsigned int nb, char *hexa)
{
	char			*s;
	int				i;
	unsigned int	temp;

	i = 0;
	temp = nb;
	if (nb == 0)
		return (zero());
	while (temp > 0)
	{
		temp = temp / 16;
		i ++;
	}
	s = malloc(sizeof(char) * (i + 1));
	if (s == NULL)
		return (NULL);
	s[i] = '\0';
	while (i != 0)
	{
		s[i - 1] = hexa[nb % 16];
		nb = nb / 16;
		i --;
	}
	return (s);
}
