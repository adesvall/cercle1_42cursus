/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:52:40 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/08 00:52:42 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
