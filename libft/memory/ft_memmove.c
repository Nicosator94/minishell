/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 08:08:52 by niromano          #+#    #+#             */
/*   Updated: 2023/05/10 12:10:55 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*p_dest;
	char	*p_src;

	p_dest = (char *)dest;
	p_src = (char *)src;
	if (dest == NULL)
		return (NULL);
	if (p_src <= p_dest)
	{
		while (n != 0)
		{
			p_dest[n - 1] = p_src[n - 1];
			n --;
		}
		return (dest);
	}
	ft_memcpy(dest, src, n);
	return (dest);
}
