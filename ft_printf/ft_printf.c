/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:08:32 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/07 17:05:06 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags		ft_init_flags(void)
{
	t_flags		flags;

	flags.dot = -1;
	flags.minus = 0;
	flags.star = 0;
	flags.type = 0;
	flags.width = 0;
	flags.zero = 0;
	return (flags);
}

int		parse_flags(const char *format, int i, t_flags *flags, va_list args)
{
	while (format[i])
	{
		if (!ft_is_in(format[i], "0123456789") &&
		!ft_is_in(format[i], "%diuxXpcs") && !ft_is_in(format[i], "-0.*"))
			break ;
		if (format[i] == '0' && flags->width == 0 && flags->minus == 0)
			flags->zero = 1;
		if (format[i] == '.')
			i = flag_dot(format, i, flags, args);
		if (format[i] == '-')
			flag_minus(flags);
		if (format[i] == '*')
			flag_width(args, flags);
		if (ft_is_in(format[i], "0123456789"))
			flag_digit(format[i], flags);
		if (ft_is_in(format[i], "%diuxXpcs"))
		{
			flags->type = format[i];
			break ;
		}
		i++;
	}
	return (i);
}

int			process_format(const char *format, va_list args)
{
	int			i;
	t_flags		flags;
	int			count;

	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			flags = ft_init_flags();
			i = parse_flags(format, ++i, &flags, args);
			if (ft_is_in(format[i], "cpsdiuxX%"))
				count += main_display(flags.type, flags, args);
		}
		else if (format[i] != '%')
			count += ft_putchar(format[i]);
		i++;
	}
	return (count);
}

int		ft_printf(const char* format, ...)
{
	va_list args;
	int		count;

	va_start(args, format);
	count = process_format(format, args);
	va_end(args);
	return (count);
}