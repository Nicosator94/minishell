/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_clear_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:32:59 by niromano          #+#    #+#             */
/*   Updated: 2023/10/11 14:42:11 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	clear_matrix(char **mat)
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

static void	clear_file(t_redi *file)
{
	t_redi	*tmp;

	while (file != NULL)
	{
		if (file->file != NULL)
			free(file->file);
		tmp = file;
		file = file->next;
		free(tmp);
	}
}

static void	clear_list(t_list *list)
{
	t_list	*tmp;

	while (list != NULL)
	{
		if (list->content != NULL)
			free(list->content);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

void	all_clear_command(t_env *env, t_cmd *cmd)
{	
	if (env != NULL)
		clear_env(env);
	while (cmd != NULL)
	{
		if (cmd->cmd != NULL)
			clear_matrix(cmd->cmd);
		if (cmd->file != NULL)
			clear_file(cmd->file);
		if (cmd->l_cmd != NULL)
			clear_list(cmd->l_cmd);
		if (cmd->line != NULL)
			free(cmd->line);
		cmd = cmd->next;
	}
	ft_putstr_fd("Malloc Failed !\n", 2);
	exit(1);
}
