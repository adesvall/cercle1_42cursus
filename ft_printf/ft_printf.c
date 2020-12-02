/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:08:32 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/02 18:14:43 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printelem(code, elem)
{
	const char	*conv; 

	conv = "cspdiuxX%"
}

int		ft_printf(const char* format, ...)
{
	va_list ap;
	int		i;
	char	code;
	
	va_start(ap, format);
	i = 0;
	while (format[i])
	{
		if (code = 'i' || code == 'd')
			ft_putnbr(va_arg(ap, int));
		i++;
	}
	va_end(ap);
}