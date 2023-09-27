/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:31:18 by niromano          #+#    #+#             */
/*   Updated: 2023/05/10 12:48:07 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*c;
	int		i;
	int		len;

	i = 0;
	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	c = malloc(sizeof(char) * (len + 1));
	if (c == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		c[i] = f(i, s[i]);
		i ++;
	}
	c[i] = '\0';
	return (c);
}
