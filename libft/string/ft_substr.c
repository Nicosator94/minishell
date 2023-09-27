/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:19:59 by niromano          #+#    #+#             */
/*   Updated: 2023/05/10 12:37:23 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*zero(void)
{
	char	*c;

	c = malloc(sizeof(char) * 1);
	if (c == NULL)
		return (NULL);
	c[0] = '\0';
	return (c);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*c;
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
	{
		c = zero();
		return (c);
	}
	if (ft_strlen(s) - start <= len)
		c = malloc(sizeof(char) * ((ft_strlen(s) - start) + 1));
	else
		c = malloc(sizeof(char) * (len + 1));
	if (c == NULL)
		return (NULL);
	while (i < len && s[start] != '\0')
	{
		c[i] = s[start];
		i ++;
		start ++;
	}
	c[i] = '\0';
	return (c);
}
