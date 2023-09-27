/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:34:12 by niromano          #+#    #+#             */
/*   Updated: 2023/05/10 10:53:32 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	negatif(int less, int nb)
{
	if (less == 1)
		return (-nb);
	return (nb);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nb;
	int	less;

	i = 0;
	nb = 0;
	less = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i ++;
	if (nptr[i] == '-')
		less ++;
	if (nptr[i] == '-' || nptr[i] == '+')
		i ++;
	if (nptr[i] >= '0' && nptr[i] <= '9')
	{
		while (nptr[i] >= '0' && nptr[i] <= '9')
		{
			nb = nb * 10;
			nb = nb + nptr[i] - 48;
			i ++;
		}
		return (negatif(less, nb));
	}
	return (0);
}
