/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:53:19 by niromano          #+#    #+#             */
/*   Updated: 2023/06/21 10:45:12 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	check(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i + 1);
		i ++;
	}
	return (0);
}

char	*last_line(char *temp, int len_of_temp)
{
	char	*n_line;
	int		i;

	i = 0;
	if (len_of_temp == 0)
		len_of_temp = ft_strlen(temp);
	n_line = malloc(sizeof(char) * (len_of_temp + 1));
	if (n_line == NULL)
		return (NULL);
	while (i < len_of_temp)
	{
		n_line[i] = temp[i];
		i ++;
	}
	n_line[i] = '\0';
	return (n_line);
}

char	*simple_line(char *temp, int len_of_temp)
{
	char	*n_line;
	int		i;

	i = 0;
	n_line = malloc(sizeof(char) * (len_of_temp + 1));
	if (n_line == NULL)
		return (NULL);
	while (i < len_of_temp)
	{
		n_line[i] = temp[i];
		i ++;
	}
	n_line[i] = '\0';
	return (n_line);
}

char	*new_temp(char *temp, int len_of_read)
{
	char	*n_temp;
	int		i;
	int		len_of_temp;

	i = 0;
	len_of_temp = check(temp);
	if (len_of_temp == 0 && len_of_read < BUFFER_SIZE)
	{
		n_temp = malloc(sizeof(char) * 1);
		if (n_temp == NULL)
			return (NULL);
		n_temp[0] = '\0';
		free(temp);
		return (n_temp);
	}
	n_temp = malloc(sizeof(char) * (ft_strlen(temp) - len_of_temp + 1));
	if (n_temp == NULL)
		return (NULL);
	while (temp[len_of_temp] != '\0')
		n_temp[i++] = temp[len_of_temp++];
	n_temp[i] = '\0';
	free(temp);
	return (n_temp);
}
