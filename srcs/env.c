/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 07:27:15 by niromano          #+#    #+#             */
/*   Updated: 2023/10/02 09:03:36 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**separate_env(char *s)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char *) * 3);
	while (s[i] != '=')
		i ++;
	tmp[0] = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i] != '=')
	{
		tmp[0][i] = s[i];
		i ++;
	}
	tmp[0][i] = '\0';
	i ++;
	tmp[1] = malloc(sizeof(char) * (ft_strlen(s) - i + 1));
	while (s[i] != '\0')
	{
		tmp[1][j] = s[i];
		i ++;
		j ++;
	}
	tmp[1][j] = '\0';
	tmp[2] = NULL;
	return (tmp);
}

t_env	*fill_env(char **tmp)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	new_env->name = ft_strdup(tmp[0]);
	new_env->value = ft_strdup(tmp[1]);
	new_env->next = NULL;
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	return (new_env);
}

char	**create_env(void)
{
	char	**env;

	env = malloc(sizeof(char *) * 3);
	
	return (env);
}

t_env	*create_without_env(void)
{
	t_env	*own_env;
	t_env	*next;
	char	*pwd;

	own_env = malloc(sizeof(t_env));
	own_env->name = ft_strdup("PWD");
	printf("%s\n", own_env->name);
	pwd = getcwd(NULL, 100);
	own_env->value = ft_strdup(pwd);
	free(pwd);
	printf("%s\n", own_env->value);
	next = malloc(sizeof(t_env));
	own_env->next = next;
	next->name = ft_strdup("SHLVL");
	printf("%s\n", next->name);
	next->value = ft_strdup("1");
	printf("%s\n", next->value);
	next->next = NULL;
	return (own_env);
}

t_env	*create_own_env(char **env)
{
	t_env	*start_env;
	t_env	*own_env;
	t_env	*new_env;
	char	**tmp;
	int		i;

	i = 1;
	tmp = separate_env(env[0]);
	own_env = fill_env(tmp);
	start_env = own_env;
	while (env[i] != NULL)
	{
		tmp = separate_env(env[i]);
		new_env = fill_env(tmp);
		own_env->next = new_env;
		own_env = new_env;
		i ++;
	}
	return (start_env);
}

void	clear_env(t_env *env)
{
	t_env	*tmp;

	while (env->next != NULL)
	{
		free(env->name);
		free(env->value);
		tmp = env;
		env = env->next;
		free(tmp);
	}
	free(env->name);
	free(env->value);
	free(env);
}
