/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:30:41 by niromano          #+#    #+#             */
/*   Updated: 2023/05/10 12:06:10 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	char			*p_dest;
	const char		*p_src;

	i = 0;
	p_dest = dest;
	p_src = src;
	if (dest == NULL)
		return (NULL);
	while (i < n)
	{
		p_dest[i] = p_src[i];
		i ++;
	}
	return (dest);
}
