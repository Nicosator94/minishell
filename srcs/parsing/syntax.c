/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:22:03 by niromano          #+#    #+#             */
/*   Updated: 2023/11/17 12:14:05 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	passes_quotes(char *s, int i)
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
	return (i);
}

int	check_pipes(char *s)
{
	int		i;
	char	chara;

	i = 0;
	chara = ' ';
	while (s[i] != '\0' && chara == ' ')
	{
		if ((s[i] < 9 || s[i] > 13) && s[i] != ' ')
			chara = s[i];
		i ++;
	}
	if (chara == '|')
		return (1);
	i = 0;
	chara = ' ';
	while (s[i] != '\0')
	{
		if ((s[i] < 9 || s[i] > 13) && s[i] != ' ')
			chara = s[i];
		i ++;
	}
	if (chara == '|')
		return (1);
	return (0);
}

int	check_multi_pipes(char *s)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
			i = passes_quotes(s, i);
		if (s[i] == '|')
			pipe ++;
		else if (s[i] != '|' && s[i] != ' ' && (s[i] < 9 || s[i] > 13))
			pipe = 0;
		if (pipe == 2)
			return (1);
		i ++;
	}
	return (0);
}

int	check_brackets_before_pipes(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
			i = passes_quotes(s, i);
		if (s[i] == '<' || s[i] == '>')
		{
			i ++;
			while (((s[i] >= 9 && s[i] <= 13) || s[i] == ' ') && s[i] != '\0')
				i ++;
			if (s[i] == '|')
				return (1);
		}
		else
			i ++;
	}
	return (0);
}

int	check_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
			return (0);
		i ++;
	}
	return (1);
}

int	syntax_error_check(char *s)
{
	if (check_quotes(s) == 1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected ", 2);
		ft_putstr_fd("token `quote'\n", 2);
		return (1);
	}
	if (check_brackets(s) == 1 || check_multi_brackets(s) == 1
		|| check_space_brackets(s) == 1 || check_opposite_brackets(s) == 1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected ", 2);
		ft_putstr_fd("token `angle bracket'\n", 2);
		return (1);
	}
	if (check_pipes(s) == 1 || check_multi_pipes(s) == 1
		|| check_brackets_before_pipes(s) == 1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected ", 2);
		ft_putstr_fd("token `pipe'\n", 2);
		return (1);
	}
	if (check_spaces(s) == 1)
		return (1);
	return (0);
}
