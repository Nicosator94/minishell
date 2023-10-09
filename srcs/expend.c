/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:17:45 by niromano          #+#    #+#             */
/*   Updated: 2023/10/09 08:47:48 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*copy(char *s, int i)
{
	char	*cpy;
	int		j;

	j = 0;
	cpy = malloc(sizeof(char) * (i + 1));
	while (j != i)
	{
		cpy[j] = s[j];
		j ++;
	}
	cpy[j] = '\0';
	return (cpy);
}

int	dollar_len(char *s, int i)
{
	int	len;

	len = 0;
	while (((s[i] >= 'a' && s[i] <= 'z')
			|| (s[i] >= 'A' && s[i] <= 'Z')
			|| (s[i] >= '0' && s[i] <= '9')
			|| s[i] == '_') && s[i] != '\0')
	{
		i ++;
		len ++;
	}
	return (len);
}

char	*replace(char *name, t_env *env)
{
	char	*value;

	while (env != NULL)
	{
		if (ft_strncmp(env->name, name, ft_strlen(name) + 1) == 0)
		{
			free(name);
			return (ft_strdup(env->value));
		}
		env = env->next;
	}
	value = malloc(sizeof(char));
	value[0] = '\0';
	free(name);
	return (value);
}

char	*replace_with_env(char *s, int i, t_env *env)
{
	char	*new_cmd;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	int		len;

	tmp1 = copy(s, i);
	i ++;
	len = dollar_len(s, i);
	tmp2 = copy(&s[i], len);
	tmp2 = replace(tmp2, env);
	tmp3 = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	tmp1 = ft_strdup(&s[i + len]);
	new_cmd = ft_strjoin(tmp3, tmp1);
	free(tmp3);
	free(tmp1);
	free(s);
	return (new_cmd);
}

void	expend(t_cmd *cmd, t_env *env)
{
	int	i;
	int	count;

	count = 0;
	while (cmd != NULL)
	{
		i = 0;
		while (cmd->line[i] != '\0')
		{
			if (cmd->line[i] == '\"')
				count += 1;
			if (cmd->line[i] == '\'' && count % 2 == 0)
			{
				i ++;
				while (cmd->line[i] != '\'')
					i ++;
			}
			else if (cmd->line[i] == '$'
				&& ((cmd->line[i + 1] >= 'a' && cmd->line[i + 1] <= 'z')
					|| (cmd->line[i + 1] >= 'A' && cmd->line[i + 1] <= 'Z')
					|| cmd->line[i + 1] == '_'))
			{
				cmd->line = replace_with_env(cmd->line, i, env);
				i = -1;
				count = 0;
			}
			i ++;
		}
		cmd = cmd->next;
	}
}
