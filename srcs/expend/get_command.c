/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:01:35 by niromano          #+#    #+#             */
/*   Updated: 2023/11/22 05:09:35 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*copy(char *s, int i)
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

int	get_len_of_command(char *s)
{
	int	i;

	i = 0;
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

void	add_cmd(t_cmd *cmd, t_list *add)
{
	t_list	*tmp;

	if (cmd->l_cmd == NULL)
		cmd->l_cmd = add;
	else
	{
		tmp = cmd->l_cmd;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = add;
	}
}

int	get_command(t_cmd *cmd, int i, t_mini *minishell)
{
	int		len;
	t_list	*add;

	len = get_len_of_command(&cmd->line[i]);
	add = malloc(sizeof(t_redi));
	if (add == NULL)
		clear_all_malloc_failed(minishell);
	add->content = copy(&cmd->line[i], len);
	if (add->content == NULL)
	{
		free(add);
		clear_all_malloc_failed(minishell);
	}
	add->next = NULL;
	add_cmd(cmd, add);
	i += len;
	return (i);
}
