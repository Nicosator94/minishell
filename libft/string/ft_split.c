/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 07:33:57 by niromano          #+#    #+#             */
/*   Updated: 2023/05/10 13:40:42 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	cmp_m(char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			len ++;
			while (s[i] != c && s[i] != '\0')
				i ++;
			i --;
		}
		i ++;
	}
	return (len);
}

static int	cmp_l(char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] != '\0' || len != 0)
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i] != '\0')
			{
				i ++;
				len ++;
			}
			return (len);
		}
		i ++;
	}
	return (len);
}

static int	c_malloc(char **m, int t, int len_l)
{
	m[t] = malloc(sizeof(char) * (len_l + 1));
	if (m[t] == NULL)
	{
		while (t > -1)
		{
			free(m[t]);
			t --;
		}
		free(m);
		return (-1);
	}
	return (0);
}

static int	split_2(char *m, char const *s, int len_l, int i)
{
	int	j;

	j = 0;
	while (len_l > j)
	{
		m[j] = s[i];
		i ++;
		j ++;
	}
	m[j] = '\0';
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**m;
	int		i;
	int		t;

	i = 0;
	if (s == NULL)
		return (NULL);
	m = malloc(sizeof(char *) * (cmp_m(s, c) + 1));
	if (m == NULL)
		return (NULL);
	t = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i ++;
		if (s[i] != c && s[i] != '\0')
		{
			if (c_malloc(m, t, cmp_l(&s[i], c)) == -1)
				return (NULL);
			i = split_2(m[t], s, cmp_l(&s[i], c), i);
			t ++;
		}
	}
	m[t] = NULL;
	return (m);
}
