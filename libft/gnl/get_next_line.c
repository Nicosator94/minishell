/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:52:58 by niromano          #+#    #+#             */
/*   Updated: 2023/06/28 10:15:05 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*fill_temp(char *buf, char *temp)
{
	char	*n_temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (temp != NULL)
		n_temp = malloc(sizeof(char) * (ft_strlen(buf) + ft_strlen(temp) + 1));
	else
		n_temp = malloc(sizeof(char) * (ft_strlen(buf) + 1));
	if (n_temp == NULL)
		return (NULL);
	if (temp != NULL)
	{
		while (temp[i] != '\0')
		{
			n_temp[i] = temp[i];
			i ++;
		}
		free(temp);
	}
	while (buf[j] != '\0')
		n_temp[i++] = buf[j++];
	n_temp[i] = '\0';
	return (n_temp);
}

char	*create_line(char *temp, int len_of_read)
{
	char	*n_line;
	int		len_of_temp;

	len_of_temp = check(temp);
	if (len_of_read < BUFFER_SIZE)
		n_line = last_line(temp, len_of_temp);
	else if (len_of_temp > 0)
		n_line = simple_line(temp, len_of_temp);
	else
		return (NULL);
	return (n_line);
}

char	*final_return(char *line, char *temp, char *lim)
{
	if (lim != NULL)
	{
		if (ft_strncmp(line, lim, ft_strlen(lim)) == 0)
		{
			free(temp);
			free(line);
			return (lim);
		}
	}
	if (line[0] == '\0')
	{
		free(temp);
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd, char *lim)
{
	char			*line;
	char			*buf;
	static char		*temp[65535];
	int				len_of_read;

	line = NULL;
	while (line == NULL)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return (NULL);
		len_of_read = read(fd, buf, BUFFER_SIZE);
		if (len_of_read <= 0 && temp[fd] == NULL)
		{
			free(buf);
			return (NULL);
		}
		buf[len_of_read] = '\0';
		if (len_of_read != 0)
			temp[fd] = fill_temp(buf, temp[fd]);
		free(buf);
		line = create_line(temp[fd], len_of_read);
		temp[fd] = new_temp(temp[fd], len_of_read);
	}
	return (final_return(line, temp[fd], lim));
}
