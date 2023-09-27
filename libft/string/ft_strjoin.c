/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:34:53 by niromano          #+#    #+#             */
/*   Updated: 2023/05/10 13:10:46 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL)
		return (NULL);
	new_s = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new_s == NULL)
		return (NULL);
	while (s1[i] != '\0')
		new_s[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		new_s[j++] = s2[i++];
	new_s[j] = '\0';
	return (new_s);
}
