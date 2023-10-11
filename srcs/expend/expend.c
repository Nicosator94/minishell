/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:17:45 by niromano          #+#    #+#             */
/*   Updated: 2023/10/11 15:24:12 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*copy(char *s, int i)
{
	char	*cpy;
	int		j;

	j = 0;
	cpy = malloc(sizeof(char) * (i + 1));
	if (cpy == NULL)
		return (NULL);
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
	if (value == NULL)
	{
		free(name);
		return (NULL);
	}
	value[0] = '\0';
	free(name);
	return (value);
}

void	clear_all(t_env *env, t_cmd *cmd, char *s)
{
	t_cmd	*tmp;

	if (s != NULL)
		free(s);
	clear_env(env);
	while (cmd != NULL)
	{
		free(cmd->line);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
	ft_putstr_fd("Malloc Failed !\n", 2);
	exit(1);
}

char	*replace_with_env(char *s, int i, t_env *env, t_cmd *cmd)
{
	char	*new_cmd;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	int		len;

	tmp1 = copy(s, i);
	if (tmp1 == NULL)
		clear_all(env, cmd, NULL);
	i ++;
	len = dollar_len(s, i);
	tmp2 = copy(&s[i], len);
	if (tmp2 == NULL)
		clear_all(env, cmd, tmp1);
	tmp2 = replace(tmp2, env);
	if (tmp2 == NULL)
		clear_all(env, cmd, tmp1);
	tmp3 = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	if (tmp3 == NULL)
		clear_all(env, cmd, NULL);
	tmp1 = ft_strdup(&s[i + len]);
	if (tmp1 == NULL)
		clear_all(env, cmd, tmp3);
	new_cmd = ft_strjoin(tmp3, tmp1);
	free(tmp3);
	free(tmp1);
	if (new_cmd == NULL)
		clear_all(env, cmd, NULL);
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
				cmd->line = replace_with_env(cmd->line, i, env, cmd);
				i = -1;
				count = 0;
			}
			i ++;
		}
		cmd = cmd->next;
	}
}
