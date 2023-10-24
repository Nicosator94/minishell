/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:59:04 by niromano          #+#    #+#             */
/*   Updated: 2023/10/24 06:45:55 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*replace_with_env_utils(char *s, char *tmp1, char *tmp2)
{
	char	*tmp3;
	char	*new_cmd;

	tmp3 = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	if (tmp3 == NULL)
		return (NULL);
	tmp1 = ft_strdup(s);
	if (tmp1 == NULL)
	{
		free(tmp3);
		return (NULL);
	}
	new_cmd = ft_strjoin(tmp3, tmp1);
	free(tmp3);
	free(tmp1);
	return (new_cmd);
}

char	*replace(char *name, t_env *env, int *exit_status)
{
	char	*value;

	if (name[0] == '?')
	{
		free(name);
		return (ft_itoa(*exit_status));
	}
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

int	dollar_len(char *s, int i)
{
	int	len;

	len = 0;
	if (s[i] == '?')
		return (1);
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
