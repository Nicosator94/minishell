/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:22:03 by niromano          #+#    #+#             */
/*   Updated: 2023/11/20 13:17:17 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	syntax_error_check(char *s)
{
	if (check_quotes(s) == 1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected ", 2);
		ft_putstr_fd("token `quote'\n", 2);
		return (1);
	}
	if (check_brackets(s) == 1 || check_multi_brackets(s) == 1
		|| check_space_brackets(s) == 1 || check_opposite_brackets(s) == 1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected ", 2);
		ft_putstr_fd("token `angle bracket'\n", 2);
		return (1);
	}
	if (check_pipes(s) == 1 || check_multi_pipes(s) == 1
		|| check_brackets_before_pipes(s) == 1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected ", 2);
		ft_putstr_fd("token `pipe'\n", 2);
		return (1);
	}
	if (check_spaces(s) == 1)
		return (1);
	return (0);
}
