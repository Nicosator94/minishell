/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:54:18 by niromano          #+#    #+#             */
/*   Updated: 2023/10/06 14:24:38 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_len_of_file(char *s)
{
	int	i;

	i = 0;
	while (s[i] == '<' || s[i] == '>')
		i ++;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i ++;
	while (s[i] != '\0' && s[i] != '<' && s[i] != '>'
		&& s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
	{
		if (s[i] == '\'')
		{
			i ++;
			while (s[i] != '\'')
				i ++;
		}
		else if (s[i] == '\"')
		{
			i ++;
			while (s[i] != '\"')
				i ++;
		}
		i ++;
	}
	return (i);
}

char	*copy_file(char *s, int len)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = malloc(sizeof(char) * (len + 1));
	while (i != len)
	{
		cpy[i] = s[i];
		i ++;
	}
	cpy[i] = '\0';
	return (cpy);
}

void	add_redi(t_cmd *cmd, t_redi *add)
{
	t_redi	*tmp;

	if (cmd->file == NULL)
		cmd->file = add;
	else
	{
		tmp = cmd->file;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = add;
	}
}

int	get_file(t_cmd *cmd, int i)
{
	int		len;
	t_redi	*add;

	len = get_len_of_file(&cmd->line[i]);
	add = malloc(sizeof(t_redi));
	add->file = copy_file(&cmd->line[i], len);
	add->next = NULL;
	add_redi(cmd, add);
	i += len;
	return (i);
}
