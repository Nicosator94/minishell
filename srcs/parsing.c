/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:05:41 by niromano          #+#    #+#             */
/*   Updated: 2023/09/29 10:19:12 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	copy(char *dst, const char *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i ++;
	}
	dst[i] = '\0';
}

char	**parser(char *s)
{
	char	**parsed;
	int		i;
	int		j;
	int		old;

	i = 0;
	j = 0;
	old = 0;
	parsed = malloc(sizeof(char *) * (len_of_parsed(s) + 1));
	while (s[i] != '\0')
	{
		if (s[i] == '|' || s[i] == '<' || s[i] == '>')
		{
			while ((s[i] == '|' || s[i] == '<' || s[i] == '>') && s[i] != '\0' && s[i] != '\'' && s[i] != '\"')
				i ++;
			parsed[j] = malloc(sizeof(char) * (i - old + 1));
			copy(parsed[j], &s[old], i - old);
			j ++;
		}
		while (s[i] == ' ' && s[i] != '\0')
			i ++;
		old = i;
		if (s[i] != '|' && s[i] != '<' && s[i] != '>' && s[i] != '\0')
		{
			while (s[i] != '|' && s[i] != '<' && s[i] != '>' && s[i] != '\0')
			{
				if (s[i] == '\'')
				{
					i ++;
					while (s[i] != '\'')
						i ++;
				}
				else if (s[i] == '\"')
				{
					i ++;
					while (s[i] != '\"')
						i ++;
				}
				i ++;
			}
			parsed[j] = malloc(sizeof(char) * (i - old + 1));
			copy(parsed[j], &s[old], i - old);
			j ++;
		}
		while (s[i] == ' ' && s[i] != '\0')
			i ++;
		old = i;
	}
	parsed[j] = NULL;
	return (parsed);
}

char	**parsing(char *s, char **env)
{
	char	**parsed;
	char	*temp_s;

	while (check_quotes(s) == 1)
	{
		s = ft_strjoin(s, "\n");
		temp_s = readline("> ");
		s = ft_strjoin(s, temp_s);
		free(temp_s);
	}
	if (s[0] != '\0')
		add_history(s);
	parsed = parser(s);
	expend(parsed, env);
	return (parsed);
}
