/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:52:40 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/09 01:13:09 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ulllen_base(unsigned long long i, char *base)
{
	unsigned int	lenbase;
	int				count;

	count = 0;
	lenbase = ft_strnlen(base, -1);
	if (i >= lenbase)
		count += ft_ulllen_base((i / lenbase), base);
	return (count + 1);
}

int	ft_strnlen(char *s, int n)
{
	int i;

	i = 0;
	while (s[i] && (n < 0 || i < n))
		i++;
	return (i);
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstrn(char *s, int n)
{
	if (!s)
		return (0);
	write(1, s, ft_strnlen(s, n));
	return (ft_strnlen(s, n));
}

int	ft_is_in(char c, const char *str)
{
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}
