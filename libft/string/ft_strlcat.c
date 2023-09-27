/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:28:50 by niromano          #+#    #+#             */
/*   Updated: 2023/05/10 12:26:05 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	total;
	unsigned int	j;

	i = 0;
	j = 0;
	if (dst == NULL)
		return (0);
	total = ft_strlen(dst) + ft_strlen(src);
	if (size == 0 || ft_strlen(dst) >= size)
		return (ft_strlen(src) + size);
	while (dst[i] != '\0')
		i ++;
	if (size > i)
	{
		while (src[j] != '\0' && i < size - 1)
		{
			dst[i] = src[j];
			i ++;
			j ++;
			if (j < size - 1)
				dst[i] = '\0';
		}
	}
	return (total);
}
