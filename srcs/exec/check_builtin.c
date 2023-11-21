/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:53:06 by niromano          #+#    #+#             */
/*   Updated: 2023/11/21 10:53:32 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_builtin(char *main_cmd)
{
	if (main_cmd == NULL)
		return (1);
	if (ft_strncmp(main_cmd, "echo", 5) == 0)
		return (0);
	else if (ft_strncmp(main_cmd, "cd", 3) == 0)
		return (0);
	else if (ft_strncmp(main_cmd, "pwd", 4) == 0)
		return (0);
	else if (ft_strncmp(main_cmd, "export", 7) == 0)
		return (0);
	else if (ft_strncmp(main_cmd, "unset", 6) == 0)
		return (0);
	else if (ft_strncmp(main_cmd, "env", 4) == 0)
		return (0);
	else if (ft_strncmp(main_cmd, "exit", 5) == 0)
		return (0);
	return (1);
}
