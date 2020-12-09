/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:20:38 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/09 01:41:41 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		main_display(char c, t_flags flags, va_list args)
{
	int count;

	if (flags.zero == 1 && flags.dot == -1 && ft_is_in(c, "diuxXp"))
	{
		flags.dot = flags.width;
		flags.width = 0;
	}
	count = 0;
	if (c == 'c')
		count = disp_char(va_arg(args, int), flags);
	else if (c == 's')
		count = disp_string(va_arg(args, char *), flags);
	else if (c == 'p')
		count = disp_pointer(va_arg(args, unsigned long long), flags);
	else if (c == 'd' || c == 'i')
		count = disp_int(va_arg(args, int), flags);
	else if (c == 'u')
		count = disp_uint(va_arg(args, unsigned int), flags);
	else if (c == 'x')
		count = disp_hexa(va_arg(args, unsigned int), 0, flags);
	else if (c == 'X')
		count = disp_hexa(va_arg(args, unsigned int), 1, flags);
	else if (c == '%')
		count = disp_char('%', flags);
	return (count);
}

int		disp_width(int width, int rest, int has_zero)
{
	int	count;

	count = 0;
	while (width - rest > 0)
	{
		if (has_zero)
			ft_putchar('0');
		else
			ft_putchar(' ');
		width--;
		count++;
	}
	return (count);
}

int		disp_char(int c, t_flags flags)
{
	int count;

	if (flags.minus == 1)
		ft_putchar(c);
	count = disp_width(flags.width, 1, 0) + 1;
	if (flags.minus == 0)
		ft_putchar(c);
	return (count);
}

int		disp_string(char *str, t_flags flags)
{
	int count;

	if (!str)
		str = "(null)";
	if (flags.minus == 1)
		ft_putstrn(str, flags.dot);
	count = disp_width(flags.width, ft_strnlen(str, flags.dot), flags.zero);
	if (flags.minus == 0)
		ft_putstrn(str, flags.dot);
	return (count + ft_strnlen(str, flags.dot));
}
