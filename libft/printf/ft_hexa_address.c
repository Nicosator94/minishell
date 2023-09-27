/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_address.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:42:52 by niromano          #+#    #+#             */
/*   Updated: 2023/05/16 09:43:04 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_hexa_address(unsigned long nb, char *hexa)
{
	char			*s;
	int				i;
	unsigned long	temp;

	i = 0;
	temp = nb;
	if (nb == 0)
		return (NULL);
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

int	tempo(int temp, char *s)
{
	int	i;

	i = 0;
	if (temp == 1 && s[0] != '-')
		ft_putchar_fd('+', 1);
	else if ((temp == 2 || temp == 5) && s[0] != '0')
	{
		if (temp == 2)
			ft_putstr_fd("0x", 1);
		else if (temp == 5)
			ft_putstr_fd("0X", 1);
		i += 1;
	}
	else if (temp == 4 && s[0] != '-')
		ft_putchar_fd(' ', 1);
	else if (temp == 1 || temp == 2 || temp == 5 || temp == 4)
		i += -1;
	return (i);
}
