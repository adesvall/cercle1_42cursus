/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagsft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:38:27 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/08 19:45:49 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_minus(t_flags *flags)
{
	flags->minus = 1;
	flags->zero = 0;
}

void	flag_digit(char c, t_flags *flags)
{
	if (flags->star == 1)
		flags->width = 0;
	flags->width = (flags->width * 10) + (c - '0');
}

void	flag_width(va_list args, t_flags *flags)
{
	flags->star = 1;
	flags->width = va_arg(args, int);
	if (flags->width < 0)
	{
		flags->minus = 1;
		flags->width *= -1;
		flags->zero = 0;
	}
}

int		flag_dot(const char *save, int start, t_flags *flags, va_list args)
{
	int i;

	flags->zero = 0;
	i = start;
	i++;
	if (save[i] == '*')
	{
		flags->dot = va_arg(args, int);
		i++;
	}
	else
	{
		flags->dot = 0;
		while (ft_is_in(save[i], "0123456789"))
			flags->dot = (flags->dot * 10) + (save[i++] - '0');
	}
	return (i);
}
