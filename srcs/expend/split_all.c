/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 07:17:51 by niromano          #+#    #+#             */
/*   Updated: 2023/11/22 09:04:59 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	return_intern_size_of_quotes(char *s, int i, char c)
{
	i ++;
	while (s[i] != c)
		i ++;
	return (i);
}

int	len_of_cmd(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		len += 1;
		while (s[i] != '\0' && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
		{
			if (s[i] == '\'')
				i = return_intern_size_of_quotes(s, i, '\'');
			else if (s[i] == '\"')
				i = return_intern_size_of_quotes(s, i, '\"');
			i ++;
		}
		while (s[i] != '\0' && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
			i ++;
	}
	return (len);
}

int	len_of_word(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
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
		else if (s[i] == '\0' || s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
			return (i);
		i ++;
	}
	return (i);
}

char	**split_all(char *s, t_mini *minishell)
{
	char	**new;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * (len_of_cmd(s) + 1));
	if (new == NULL)
		clear_all_malloc_failed(minishell);
	while (s[i] != '\0')
	{
		len = len_of_word(&s[i]);
		new[j] = copy(&s[i], len);
		if (new[j++] == NULL)
		{
			clear_mat(new);
			clear_all_malloc_failed(minishell);
		}
		i += len;
		while (s[i] != '\0' && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
			i ++;
	}
	new[j] = NULL;
	return (new);
}
