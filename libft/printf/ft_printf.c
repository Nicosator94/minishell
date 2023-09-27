/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:49:32 by niromano          #+#    #+#             */
/*   Updated: 2023/05/15 08:48:55 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	chara(va_list arg, char A)
{
	char	c;
	char	*s;

	if (A == 'c')
	{
		c = va_arg(arg, int);
		ft_putchar_fd(c, 1);
	}
	else if (A == 's')
	{
		s = va_arg(arg, char *);
		if (!s)
		{
			ft_putstr_fd("(null)", 1);
			return (4);
		}
		ft_putstr_fd(s, 1);
		return (ft_strlen(s) - 2);
	}
	else if (A == '%')
		ft_putchar_fd('%', 1);
	return (-1);
}

int	number(va_list arg, char A, int temp)
{
	char	*s;
	int		i;

	if (A == 'd' || A == 'i')
		s = ft_itoa(va_arg(arg, int));
	else if (A == 'u')
		s = ft_unsigned_itoa(va_arg(arg, unsigned int));
	else if (A == 'x')
		s = ft_conv_hexa(va_arg(arg, unsigned int), "0123456789abcdef");
	else if (A == 'X')
	{
		s = ft_conv_hexa(va_arg(arg, unsigned int), "0123456789ABCDEF");
		temp += 3;
	}
	temp = tempo(temp, s);
	ft_putstr_fd(s, 1);
	i = ft_strlen(s) - 2 + temp;
	free(s);
	return (i);
}

int	hexa(va_list arg)
{
	char	*s;
	int		i;

	s = ft_hexa_address(va_arg(arg, unsigned long), "0123456789abcdef");
	if (s == NULL)
	{
		ft_putstr_fd("(nil)", 1);
		return (3);
	}
	write(1, "0x", 2);
	ft_putstr_fd(s, 1);
	i = ft_strlen(s);
	free(s);
	return (i);
}

int	check_chara(va_list arg, const char *f, int i)
{
	int		nb;
	int		temp;
	char	c;

	nb = 0;
	temp = 0;
	c = f[i];
	if (c == '+' || c == '#' || c == ' ')
	{
		if (c == '+')
			temp = 1;
		else if (c == '#')
			temp = 2;
		else if (c == ' ')
			temp = 4;
		c = f[i + 1];
	}
	if (c == 'c' || c == 's' || c == '%')
		nb += chara(arg, c);
	else if (c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X')
		nb += number(arg, c, temp);
	else if (c == 'p')
		nb += hexa(arg);
	return (nb);
}

int	ft_printf(const char *f, ...)
{
	int		i;
	int		nb;
	va_list	arg;

	i = 0;
	nb = 0;
	va_start(arg, f);
	while (f[i] != '\0')
	{
		if (f[i] == '%')
		{
			i ++;
			nb += check_chara(arg, f, i);
			if (f[i] == ' ' && f[i + 1] == 's')
				nb += -1;
			if (f[i] == '+' || f[i] == '#' || f[i] == ' ')
				i ++;
		}
		else
			ft_putchar_fd(f[i], 1);
		i ++;
	}
	va_end(arg);
	return (i + nb);
}
