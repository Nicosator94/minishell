/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:51:40 by niromano          #+#    #+#             */
/*   Updated: 2023/11/13 11:13:14 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	take_infile(t_cmd *cmd, int tmp_file)
{
	t_redi	*tmp;
	int		infile;

	infile = tmp_file;
	tmp = cmd->file;
	while (tmp != NULL)
	{
		if (tmp->status == 1 || tmp->status == 3)
		{
			if (infile > 0)
				close(infile);
			infile = open(tmp->file, O_RDONLY);
			if (infile == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(tmp->file, 2);
				if (access(tmp->file, F_OK) == 0)
					ft_putstr_fd(": Permission denied\n", 2);
				else
					ft_putstr_fd(": No such file or directory\n", 2);
				return (-1);
			}
		}
		tmp = tmp->next;
	}
	return (infile);
}

int	init_outfile(int outfile, t_redi *tmp)
{
	if (outfile > 0)
		close(outfile);
	if (tmp->status == 2)
		outfile = open(tmp->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (tmp->status == 4)
		outfile = open(tmp->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (outfile == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tmp->file, 2);
		if (access(tmp->file, F_OK) == 0)
			ft_putstr_fd(": Permission denied\n", 2);
		else
			ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	return (outfile);
}

int	take_outfile(t_cmd *cmd, int last)
{
	t_redi	*tmp;
	int		outfile;

	outfile = -2;
	if (last == 1)
		outfile = open("/dev/stdout", O_WRONLY | O_TRUNC);
	tmp = cmd->file;
	while (tmp != NULL)
	{
		if (tmp->status == 2 || tmp->status == 4)
		{
			outfile = init_outfile(outfile, tmp);
			if (outfile == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (outfile);
}
