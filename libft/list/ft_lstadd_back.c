/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:47:14 by niromano          #+#    #+#             */
/*   Updated: 2023/05/11 14:48:22 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*p;
	int		i;

	p = *lst;
	if (p != NULL)
	{
		i = ft_lstsize(p);
		while (i > 1)
		{
			p = p->next;
			i --;
		}
		p->next = new;
	}
	else
		*lst = new;
}
