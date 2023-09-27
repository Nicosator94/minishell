/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:13:56 by niromano          #+#    #+#             */
/*   Updated: 2023/05/10 08:34:18 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	j;

	i = (int)ft_strlen(s);
	j = -1;
	while (c > 256)
		c = c - 256;
	while (i >= 0)
	{
		if (s[i] == c)
		{
			j = i;
			return ((char *)&s[j]);
		}
		i --;
	}
	return (NULL);
}
