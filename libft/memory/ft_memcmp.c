/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:38:09 by niromano          #+#    #+#             */
/*   Updated: 2023/05/15 14:22:19 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned char		*p_s1;
	unsigned char		*p_s2;

	i = 0;
	if (n == 0)
		return (0);
	p_s1 = (unsigned char *) s1;
	p_s2 = (unsigned char *) s2;
	while (p_s1[i] == p_s2[i] && i < n - 1)
		i ++;
	return (p_s1[i] - p_s2[i]);
}
