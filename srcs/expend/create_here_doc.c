/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 04:08:12 by niromano          #+#    #+#             */
/*   Updated: 2023/11/28 10:26:29 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*create_name(int nb, t_mini *minishell)
{
	char	*name;
	char	*number;

	number = ft_itoa(nb);
	if (number == NULL)
		clear_all_malloc_failed(minishell);
	name = ft_strjoin("/tmp/here_doc_", number);
	free(number);
	if (name == NULL)
		clear_all_malloc_failed(minishell);
	return (name);
}

void	end_of_here_doc(char *s, char *lim, int fd)
{
	if (s == NULL && g_signal != 4)
	{
		ft_putstr_fd("minishell: warning: ", 2);
		ft_putstr_fd("here-document delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(lim, 2);
		ft_putstr_fd("')\n", 2);
	}
	else
		free(s);
	close(fd);
}

char	*create_file(char *lim, int nb, t_mini *minishell)
{
	char	*name;
	char	*s;
	int		fd;

	name = create_name(nb, minishell);
	fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd != -1)
	{
		s = readline("> ");
		while (s != NULL && ft_strncmp(s, lim, ft_strlen(lim) + 1) != 0)
		{
			if (access(name, F_OK | W_OK) == 0)
			{
				ft_putstr_fd(s, fd);
				ft_putstr_fd("\n", fd);
			}
			free(s);
			s = readline("> ");
		}
		end_of_here_doc(s, lim, fd);
	}
	free(lim);
	return (name);
}

void	create_here_doc(t_mini *minishell)
{
	t_cmd	*cmd;
	t_redi	*tmp;
	int		nb;

	cmd = minishell->cmd;
	nb = 1;
	while (cmd != NULL && g_signal != 4)
	{
		tmp = cmd->file;
		while (tmp != NULL)
		{
			if (tmp->status == 3)
			{
				g_signal = 3;
				tmp->file = create_file(tmp->file, nb, minishell);
				if (g_signal != 4)
					g_signal = 0;
				nb += 1;
			}
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
}

void	clean_here_doc(t_cmd *cmd)
{
	t_cmd	*tmp_cmd;
	t_redi	*tmp_file;

	tmp_cmd = cmd;
	while (tmp_cmd != NULL)
	{
		tmp_file = tmp_cmd->file;
		while (tmp_file != NULL)
		{
			if (tmp_file->status == 3)
			{
				if (access(tmp_file->file, F_OK) == 0)
					unlink(tmp_file->file);
			}
			tmp_file = tmp_file->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
}
