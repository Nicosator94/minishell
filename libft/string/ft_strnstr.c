/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:57:09 by niromano          #+#    #+#             */
/*   Updated: 2023/05/10 14:09:54 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (big == NULL)
		return (NULL);
	if (little[0] == '\0')
		return ((char *)&big[i]);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		if (big[i] == little[j])
		{
			while (big[i] == little[j] && little[j] != '\0' && i < len)
			{
				i ++;
				j ++;
			}
			if (little[j] == '\0')
				return ((char *)&big[i - j]);
			i = i - j;
		}
		i ++;
	}
	return (NULL);
}
