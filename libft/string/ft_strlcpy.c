/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 08:39:14 by niromano          #+#    #+#             */
/*   Updated: 2023/05/09 15:22:37 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i ++;
		}
	}
	if (size != 0)
		dst[i] = '\0';
	while (src[i] != '\0')
		i ++;
	return (i);
}
