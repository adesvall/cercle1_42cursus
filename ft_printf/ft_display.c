/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:20:38 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/07 18:19:12 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		main_display(char c, t_flags flags, va_list args)
{
	int count;

	count = 0;
	if (c == 'c')
		count = disp_char(va_arg(args, int), flags);
	else if (c == 's')
		count = disp_string(va_arg(args, char *), flags);
	else if (c == 'p')
		count = disp_pointer(va_arg(args, unsigned long long), flags);
	else if (c == 'd' || c == 'i')
		count = disp_int(va_arg(args, int), flags);
	/*else if (c == 'u')
		count += disp_uint((unsigned int)va_arg(args, unsigned int),
		flags);
	else if (c == 'x')
		count += disp_hexa(va_arg(args, unsigned int), 1, flags);
	else if (c == 'X')
		count += disp_hexa(va_arg(args, unsigned int), 0, flags);
	else if (c == '%')
		count += disp_percent(flags);*/
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

	if (flags.minus == 1)
		ft_putstrn(str, flags.dot);
	count = disp_width(flags.width, ft_strnlen(str, flags.dot), 0) + ft_strnlen(str, flags.dot);
	if (flags.minus == 0)
		ft_putstrn(str, flags.dot);
	return (count);
}

int		disp_pointer(unsigned long long ptr, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.minus == 1)
		count += ft_putstrn("0x", 2) + ft_putnbr_base(ptr, "0123456789abcdef");
	count += disp_width(flags.width, 14, 0);
	if (flags.minus == 0)
		count += ft_putstrn("0x", 2) + ft_putnbr_base(ptr, "0123456789abcdef");
	return (count);
}

int		disp_int(int n, t_flags flags)
{
	int	count;

	count = 0;
	return (count);
}