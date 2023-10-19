/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:56:08 by niromano          #+#    #+#             */
/*   Updated: 2023/10/18 23:35:56 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quotes(char *s)
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

int	check_brackets(char *s)
{
	int		i;
	char	chara;

	i = 0;
	chara = ' ';
	while (s[i] != '\0')
	{
		if ((s[i] < 9 || s[i] > 13) && s[i] != ' ')
			chara = s[i];
		i ++;
	}
	if (chara == '>' || chara == '<')
		return (1);
	return (0);
}

int	check_multi_brackets(char *s)
{
	int	i;
	int	brackets;

	i = 0;
	brackets = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '>' || s[i] == '<')
			brackets ++;
		else if (s[i] != '>' && s[i] != '<' && s[i] != ' '
			&& (s[i] < 9 || s[i] > 13))
			brackets = 0;
		if (brackets == 3)
			return (1);
		i ++;
	}
	return (0);
}

int	check_space_brackets(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '<' || s[i] == '>')
		{
			i ++;
			if (s[i] == '<' || s[i] == '>')
				i ++;
			while (((s[i] >= 9 && s[i] <= 13) || s[i] == ' ') && s[i] != '\0')
				i ++;
			if (s[i] == '<' || s[i] == '>')
				return (1);
		}
		else
			i ++;
	}
	return (0);
}

int	check_opposite_brackets(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '<' || s[i] == '>')
		{
			if (s[i] == '<' && s[i + 1] == '>')
				return (1);
			if (s[i] == '>' && s[i + 1] == '<')
				return (1);
		}
		i ++;
	}
	return (0);
}
