/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:07:07 by niromano          #+#    #+#             */
/*   Updated: 2023/09/29 14:47:26 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_of_parsed(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '|' || s[i] == '<' || s[i] == '>')
		{
			while ((s[i] == '|' || s[i] == '<' || s[i] == '>') && s[i] != '\0')
				i ++;
			j ++;
		}
		if (s[i] != '|' && s[i] != '<' && s[i] != '>' && s[i] != '\0')
		{
			while (s[i] != '|' && s[i] != '<' && s[i] != '>' && s[i] != '\0')
				i ++;
			j ++;
		}
	}
	return (j);
}

int	syntax_error_check(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
		{
			i ++;
			while (s[i] != '\'' && s[i] != '\0')
				i ++;
			if (s[i] == '\0')
				return (1);
		}
		else if (s[i] == '\"')
		{
			i ++;
			while (s[i] != '\"' && s[i] != '\0')
				i ++;
			if (s[i] == '\0')
				return (1);
		}
		i ++;
	}
	return (0);
}

// int	check_syntax_error(char *s)
// {
// 	if (s[0] == '|' || s[ft_strlen(s) - 1] == '>' || s[ft_strlen(s) - 1] == '<')
// 		printf("minishell: syntax error near unexpected token\n");
// 	return (0);
// }