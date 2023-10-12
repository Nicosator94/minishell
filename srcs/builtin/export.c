/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:10:33 by agomes-g          #+#    #+#             */
/*   Updated: 2023/10/12 11:48:21 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void printList(t_env *env) 
{
    t_env	*lst;

	lst = env;
    while (lst != NULL)
	{
        printf("export %s", lst->name);
		if (lst->value != NULL)
			printf("=\"%s\"", lst->value);
		else if (lst->val)
			printf("=\"\"");
		printf("\n");
        lst = lst->next;
    }
}

int	envsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_env	*new_element(char *name, char *value, char *cmd)
{
	t_env	*liste;
	int		i;

	i = 0;
	liste = malloc(sizeof(t_env));
	if (liste == NULL)
		return (NULL);
	if (!name)
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

	p = *lst;
	if (p != NULL)
	{
		i = envsize(p);
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

char *get_value(char *s)
{
	char	*value;
	int		i;

	i = 0;
	while (s[i] && s[i] != '=')
		i ++;
	if (!s[i] || !s[i + 1])
		return (NULL);
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

int	check_parsing(char *cmd)
{
	int	i;

	i = 1;
	if (!((cmd[0] >='a' && cmd[0] <= 'z') || (cmd[0] >= 'A' && cmd[0] <= 'Z') || cmd[0] == '_'))
		return (0); 
	while (cmd[i] && cmd[i] != '=')
	{
		if  (!((cmd[i] >='a' && cmd[i] <= 'z') || (cmd[i] >= 'A' && cmd[i] <= 'Z')
			|| (cmd[i] >= '0' && cmd[i] <= '9') || cmd[i] == '_'))
			return (0);
		i ++;
	}
	if (cmd[i])
	{
		i ++;
		while (cmd[i])
		{
			if (!ft_isprint(cmd[i]))
				return (0);
			i ++;
		}
	}
	return (1);
}

void	sort_list(t_env *env) //ajouter les changements avec val
{
	char	*name;
	char	*value;
	t_env	*tmp;

	while (env != NULL)
	{
		tmp = env->next;
		while (tmp != NULL)
		{
			if (ft_strncmp(env->name, tmp->name, ft_strlen(env->name)) == 1)
			{
				name = env->name;
				value = env->value;
				env->name = tmp->name;
				env->value = tmp->value;
				tmp->name = name;
				tmp->value = value;
			}
			tmp = tmp->next;
		}
		env = env->next;
	}
}
int	check_occurence(t_env *env, t_env *new)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, new->name, ft_strlen(new->name)) == 0)
		{
			if (new->val)
				tmp->value = new->value;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	export(char **cmd, t_env *env)
{
	t_env	*new;
	
	if (!cmd[1])
	{
		sort_list(env);
		return (printList(env));
	}
	if (cmd[2] || !check_parsing(cmd[1]))
		return (ft_putstr_fd("not a valid identifier\n", 1));
	new = new_element(get_name(cmd[1]), get_value(cmd[1]), cmd[1]);
	if (!(check_occurence(env, new)))
		add_back(&env, new);
	else
		clear_env(new);
	printList(env); // ne pas oublier de retirer
}
