/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:19:42 by niromano          #+#    #+#             */
/*   Updated: 2023/09/28 14:44:05 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_mat(char **mat)
{
	int	i;

	i = 0;
	while (mat[i] != NULL)
	{
		free(mat[i]);
		i ++;
	}
	free(mat);
}

void	affiche_mat(char **mat)
{
	int	i;

	i = 0;
	while (mat[i] != NULL)
	{
		printf("%d = %s\n", i, mat[i]);
		i ++;
	}
}

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

void	copy(char *dst, const char *src, int size)
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
			while ((s[i] == '|' || s[i] == '<' || s[i] == '>') && s[i] != '\0')
				i ++;
			parsed[j] = malloc(sizeof(char) * (i - old + 1));
			copy(parsed[j], &s[old], i - old);
			j ++;
		}
		while (s[i] == ' ')
			i ++;
		old = i;
		if (s[i] != '|' && s[i] != '<' && s[i] != '>' && s[i] != '\0')
		{
			while (s[i] != '|' && s[i] != '<' && s[i] != '>' && s[i] != '\0')
				i ++;
			parsed[j] = malloc(sizeof(char) * (i - old + 1));
			copy(parsed[j], &s[old], i - old);
			j ++;
		}
		while (s[i] == ' ')
			i ++;
		old = i;
	}
	parsed[j] = NULL;
	return (parsed);
}

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

char	**parsing(char *s)
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
	return (parsed);
}

int	prompt(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	const char	*prompt = "minishell$ ";
	char		*s;
	char		**parsed;

	while (1)
	{
		s = readline(prompt);
		parsed = parsing(s);
		free(s);
		affiche_mat(parsed);
		free_mat(parsed);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	prompt(argc, argv, env);
	return (0);
}
