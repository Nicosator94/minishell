/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:13:57 by niromano          #+#    #+#             */
/*   Updated: 2023/05/10 13:12:35 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	start(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (set[j] != '\0')
	{
		if (set[j] == s1[i])
		{
			j = -1;
			i ++;
		}
		j ++;
	}
	return (i);
}

static int	end(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	len;

	i = ft_strlen(s1) - 1;
	j = 0;
	len = 0;
	while (set[j] != '\0')
	{
		if (set[j] == s1[i])
		{
			j = -1;
			i --;
			len ++;
		}
		j ++;
	}
	return (len);
}

static char	*rien(void)
{
	char	*s;

	s = malloc(sizeof(char) * 1);
	if (s == NULL)
		return (NULL);
	s[0] = '\0';
	return (s);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*s;
	unsigned int	i;
	int				sta;
	int				total;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	sta = start(s1, set);
	total = sta + end(s1, set);
	if (sta == (int)ft_strlen(s1))
		s = rien();
	else
	{
		s = malloc(sizeof(char) * (ft_strlen(s1) - total + 1));
		if (s == NULL)
			return (NULL);
		while (i < (ft_strlen(s1) - total))
			s[i++] = s1[sta++];
		s[i] = '\0';
	}
	return (s);
}
