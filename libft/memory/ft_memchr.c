/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:54:53 by niromano          #+#    #+#             */
/*   Updated: 2023/05/09 08:51:44 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	const char		*temp;

	i = 0;
	temp = s;
	while (c >= 256)
		c = c - 256;
	while (i < n)
	{
		if (temp[i] == c)
			return ((char *)&temp[i]);
		i ++;
	}
	return (NULL);
}
