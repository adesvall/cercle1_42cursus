/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 00:59:16 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/09 01:46:45 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		disp_pointer(unsigned long long ptr, t_flags flags)
{
	int	count;

	count = 0;
	if (ptr == 0 && flags.dot == 0 && flags.zero == 0)
		count += disp_width(flags.width, 2, 0) + ft_putstrn("0x", 2);
	else
	{
		if (flags.minus == 1)
			count += ft_putstrn("0x", 2) + ft_putull_base(ptr, "0123456789abcdef", flags.dot);
		count += disp_width(flags.width, ft_ulllen_base(ptr, "0123456789abcdef", flags.dot) + 2, 0);
		if (flags.minus == 0)
			count += ft_putstrn("0x", 2) + ft_putull_base(ptr, "0123456789abcdef", flags.dot);
	}
	return (count);
}

int		disp_int(int n, t_flags flags)
{
	int	count;
	int nbrlen;

	count = 0;
	if (n == 0 && flags.dot == 0 && flags.zero == 0)
		count += disp_width(flags.width, 0, 0);
	else
	{
		if (n < 0 && flags.zero == 1 && flags.dot != -1)
			flags.dot--;
		nbrlen = ft_nbrlen_base(n, "0123456789", flags.dot);
		if (flags.minus == 1)
			count += ft_putnbr_base(n, "0123456789", flags.dot);
		count += disp_width(flags.width, nbrlen, flags.zero);
		if (flags.minus == 0)
			count += ft_putnbr_base(n, "0123456789", flags.dot);
	}
	return (count);
}

int		disp_uint(unsigned int n, t_flags flags)
{
	int count;
	int nbrlen;

	count = 0;
	if (n == 0 && flags.dot == 0 && flags.zero == 0)
		count += disp_width(flags.width, 0, 0);
	else
	{
		nbrlen = ft_unbrlen_base(n, "0123456789", flags.dot);
		if (flags.minus == 1)
			count += ft_putunbr_base(n, "0123456789", flags.dot);
		count += disp_width(flags.width, nbrlen, flags.zero);
		if (flags.minus == 0)
			count += ft_putunbr_base(n, "0123456789", flags.dot);
	}
	return (count);
}

int		disp_hexa(unsigned int n, int maj, t_flags flags)
{
	int		count;
	int		nbrlen;
	char	*base;

	count = 0;
	if (n == 0 && flags.dot == 0 && flags.zero == 0)
		count += disp_width(flags.width, 0, 0);
	else
	{
		base = (maj == 1) ? "0123456789ABCDEF" : "0123456789abcdef";
		nbrlen = ft_unbrlen_base(n, base, flags.dot);
		if (flags.minus == 1)
			count += ft_putunbr_base(n, base, flags.dot);
		count += disp_width(flags.width, nbrlen, flags.zero);
		if (flags.minus == 0)
			count += ft_putunbr_base(n, base, flags.dot);
	}
	return (count);
}
