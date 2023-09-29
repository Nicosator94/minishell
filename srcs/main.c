/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:19:42 by niromano          #+#    #+#             */
/*   Updated: 2023/09/29 12:47:01 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_mat(char **mat);
void	affiche_mat(char **mat);

int	prompt(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	const char	*prompt = "minishell$ ";
	char		*s;
	char		**parsed;

	while (1)
	{
		s = readline(prompt);
		parsed = parsing(s, env);
		free(s);
		if (parsed == NULL)
			return (1);
		affiche_mat(parsed);
		free_mat(parsed);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	prompt(argc, argv, env);
	return (0);
}

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
