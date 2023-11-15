/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agomes-g <agomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:13:03 by agomes-g          #+#    #+#             */
/*   Updated: 2023/11/15 09:47:36 by agomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sort_list_annexe(t_env *env, t_env *tmp)
{
	char	*name;
	char	*value;
	int		val;

	name = env->name;
	value = env->value;
	val = env->val;
	env->name = tmp->name;
	env->value = tmp->value;
	env->val = tmp->val;
	tmp->name = name;
	tmp->value = value;
	tmp->val = val;
}

void	sort_list(t_env *env)
{
	t_env	*tmp;

	while (env != NULL)
	{
		tmp = env->next;
		while (tmp != NULL)
		{
			if (ft_strncmp(env->name, tmp->name, ft_strlen(env->name) + 1) == 1)
				sort_list_annexe(env, tmp);
			tmp = tmp->next;
		}
		env = env->next;
	}
}

t_env	*copy_env_annexe(t_env *tmp)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(tmp->name);
	if (!new->name)
		return (free(new), NULL);
	if (tmp->val)
	{
		new->value = ft_strdup(tmp->value);
		if (!new->value)
			return (free(new->name), free(new), NULL);
	}
	else
		new->value = NULL;
	new->val = tmp->val;
	return (new);
}

t_env	*copy_env(t_env *env)
{
	t_env	*copy;
	t_env	*tmp_copy;
	t_env	*tmp;
	t_env	*new;

	copy = NULL;
	tmp_copy = copy;
	tmp = env;
	while (tmp)
	{
		new = (copy_env_annexe(tmp));
		if (!new)
			return (NULL);
		if (!copy)
			copy = new;
		else
			tmp_copy->next = new;
		tmp_copy = new;
		tmp = tmp->next;
	}
	if (tmp_copy)
		tmp_copy->next = NULL;
	return (copy);
}

int	print_sort_list(t_env *env)
{
	t_env	*lst;
	t_env	*tmp;

	if (!env)
		return (0);
	lst = copy_env(env);
	if (!lst)
		return (-2);
	tmp = lst;
	sort_list(lst);
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
	clear_env(tmp);
	return (0);
}
