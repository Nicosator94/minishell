/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_new_element.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agomes-g <agomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:30:42 by agomes-g          #+#    #+#             */
/*   Updated: 2023/10/24 09:17:49 by agomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*new_element(char *name, char *value, char *cmd)
{
	t_env	*liste;
	int		i;

	i = 0;
	if (!name || !value)
	{
		if (name)
			free (name);
		if (value)
			free (value);
		return (NULL);
	}
	liste = malloc(sizeof(t_env));
	if (liste == NULL)
		return (NULL);
	liste->name = name;
	while (cmd[i] && cmd[i] != '=')
		i ++;
	if (!cmd[i])
		liste->val = 0;
	else
		liste->val = 1;
	liste->value = value;
	liste->next = NULL;
	return (liste);
}

void	add_back(t_env **lst, t_env *new)
{
	t_env	*p;
	int		i;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	p = *lst;
	if (p != NULL)
	{
		i = size_env(p);
		while (i > 1)
		{
			p = p->next;
			i --;
		}
		p->next = new;
	}
	else
		*lst = new;
}

char	*get_value(char *s)
{
	char	*value;
	int		i;

	i = 0;
	while (s[i] && s[i] != '=')
		i ++;
	if (!s[i] || !s[i + 1])
		return ("");
	i ++;
	value = malloc(sizeof(char) * (ft_strlen(s) - i + 1));
	if (!value)
		return (NULL);
	ft_strlcpy(value, &s[i], ft_strlen(s) - i + 1);
	return (value);
}

char	*get_name(char *s)
{
	char	*name;
	int		i;

	i = 0;
	while (s[i] && s[i] != '=')
		i ++;
	name = malloc(sizeof(char) * i + 1);
	if (!name)
		return (NULL);
	ft_strlcpy(name, s, i + 1);
	return (name);
}
