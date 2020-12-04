/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:19:48 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/04 14:47:08 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_is_in(char c, const char *str)
{
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

int		convert_and_print(int c, t_flags flags, va_list args)
{
	int char_count;

	char_count = 0;
	if (c == 'c')
		char_count = ft_treat_char(va_arg(args, int), flags);
	else if (c == 's')
		char_count = ft_treat_string(va_arg(args, char *), flags);
	else if (c == 'p')
		char_count = ft_treat_pointer(va_arg(args, unsigned long long), flags);
	else if (c == 'd' || c == 'i')
		char_count = ft_treat_int(va_arg(args, int), flags);
	else if (c == 'u')
		char_count += ft_treat_uint((unsigned int)va_arg(args, unsigned int),
		flags);
	else if (c == 'x')
		char_count += ft_treat_hexa(va_arg(args, unsigned int), 1, flags);
	else if (c == 'X')
		char_count += ft_treat_hexa(va_arg(args, unsigned int), 0, flags);
	else if (c == '%')
		char_count += ft_treat_percent(flags);
	return (char_count);
}