/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:08:32 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/04 14:46:12 by adesvall         ###   ########.fr       */
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
			i = ft_flag_dot(format, i, flags, args);
		if (format[i] == '-')
			ft_flag_minus(flags);
		if (format[i] == '*')
			ft_flag_width(args, flags);
		if (ft_isdigit(format[i]))
			ft_flag_digit(format[i], *flags);
		if (ft_is_in(format[i], "%diuxXpcs"))
		{
			flags->type = format[i];
			break ;
		}
		i++;
	}
	return (i);
}

void	printelem(code, elem)
{
	const char	*conv; 

	conv = "cspdiuxX%"
}

int		ft_printf(const char* format, ...)
{
	va_list args;
	int		i;
	char	code;

	va_start(args, format);
	
	va_end(args);
}