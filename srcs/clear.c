/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:12:14 by niromano          #+#    #+#             */
/*   Updated: 2023/10/25 08:52:56 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_env(t_env *env)
{
	t_env	*tmp;

	while (env != NULL)
	{
		if (env->name != NULL)
			free(env->name);
		if (env->value != NULL)
			free(env->value);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

void	clear_list_cmd(t_list *l_cmd)
{
	t_list	*tmp;
	
	while (l_cmd != NULL)
	{
		if (l_cmd->content != NULL)
			free(l_cmd->content);
		tmp = l_cmd;
		l_cmd = l_cmd->next;
		free(tmp);
	}
}

void	clear_mat(char **mat)
{
	int	i;

	i = 0;
	if (mat != NULL)
	{
		while (mat[i] != NULL)
		{
			free(mat[i]);
			i ++;
		}
		free(mat);
		mat = NULL;
	}
}

void	clear_redi(t_redi *redi)
{
	t_redi	*tmp;

	while (redi != NULL)
	{
		if (redi->file != NULL)
		{
			if (redi->status == 3)
			{
				if (access(redi->file, F_OK) == 0)
					unlink(redi->file);
			}
			free(redi->file);
		}
		tmp = redi;
		redi = redi->next;
		free(tmp);
	}
}

void	clear_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd != NULL)
	{
		if (cmd->line != NULL)
			free(cmd->line);
		if (cmd->l_cmd != NULL)
			clear_list_cmd(cmd->l_cmd);
		if (cmd->cmd != NULL)
			clear_mat(cmd->cmd);
		if (cmd->file != NULL)
			clear_redi(cmd->file);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

void	clear_all_malloc_failed(t_mini *minishell)
{
	if (minishell->env != NULL)
		clear_env(minishell->env);
	if (minishell->cmd != NULL)
		clear_cmd(minishell->cmd);
	if (minishell != NULL)
		free(minishell);
	rl_clear_history();
	ft_putstr_fd("Malloc Failed !\n", 2);
	exit(1);
}

void	clear_all(t_mini *minishell)
{
	if (minishell->env != NULL)
		clear_env(minishell->env);
	if (minishell->cmd != NULL)
		clear_cmd(minishell->cmd);
	if (minishell != NULL)
		free(minishell);
	rl_clear_history();
}
