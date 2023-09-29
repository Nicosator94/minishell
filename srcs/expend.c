/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:17:45 by niromano          #+#    #+#             */
/*   Updated: 2023/09/29 15:25:11 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	size_of_name(char *s)
{
	int	i;

	i = 0;
	while ((s[i] >= 'a' && s[i] <= 'z')
		|| (s[i] >= 'A' && s[i] <= 'Z')
		|| (s[i] >= '0' && s[i] <= '9')
		|| s[i] == '_')
		i ++;
	return (i);
}

char	*get_name(char *s)
{
	int		i;
	int		size;
	char	*name;

	i = 0;
	size = size_of_name(s);
	name = malloc(sizeof(char) * (size + 2));
	while (i != size)
	{
		name[i] = s[i];
		i ++;
	}
	name[i] = '=';
	name[i + 1] = '\0';
	return (name);
}

char	*get_value(char *name, char **env)
{
	int		i;
	char	*s;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(name, env[i], ft_strlen(name)) == 0)
		{
			s = ft_strdup(&env[i][ft_strlen(name)]);
			return (s);
		}
		i ++;
	}
	s = malloc(sizeof(char));
	s[0] = '\0';
	return (s);
}

char	*get_value_of_env_name(char *s, char **env)
{
	char	*name;
	char	*value;

	name = get_name(s);
	value = get_value(name, env);
	free(name);
	if (value == NULL)
	{
		value = malloc(sizeof(char));
		value[0] = '\0';
	}
	return (value);
}

char	*replace_env_name_by_value(char *s, int j, char **env)
{
	int		i;
	char	*new_s;
	char	*env_value;
	char	*temp_s;
	char	*end;

	(void)env;
	i = 0;
	new_s = malloc(sizeof(char) * (j + 1));
	while (i != j)
	{
		new_s[i] = s[i];
		i ++;
	}
	new_s[i] = '\0';
	j ++;
	env_value = get_value_of_env_name(&s[j], env);
	temp_s = ft_strjoin(new_s, env_value);
	free(new_s);
	end = ft_strdup(&s[j + size_of_name(&s[j])]);
	new_s = ft_strjoin(temp_s, end);
	free(end);
	free(temp_s);
	free(env_value);
	free(s);
	return (new_s);
}

char	*interpret_quotes(char *s, char **env)
{
	int		i;

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
			{
				// if (s[i] == '$')
				// {
				// 	s = replace_env_name_by_value(s, i, env);
				// 	i = -1;
				// }
				i ++;
			}
		}
		else if (s[i] == '$')
		{
			s = replace_env_name_by_value(s, i, env);
			i = -1;
		}
		i ++;
	}
	return (s);
}

void	expend(char **parsed, char **env)
{
	(void)env;
	(void)parsed;
	int	i;

	i = 0;
	while (parsed[i] != NULL)
	{
		parsed[i] = interpret_quotes(parsed[i], env);
		i ++;
	}
}
