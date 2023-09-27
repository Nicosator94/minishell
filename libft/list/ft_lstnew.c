/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 08:23:29 by niromano          #+#    #+#             */
/*   Updated: 2023/06/28 13:22:54 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*liste;

	liste = malloc(sizeof(t_list));
	if (liste == NULL)
		return (NULL);
	liste->content = content;
	liste->next = NULL;
	return (liste);
}
