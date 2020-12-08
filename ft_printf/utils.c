/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:19:48 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/08 19:54:22 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_nbrlen_base(int n, char *base, int precision)
{
	unsigned int	i;
	unsigned int	lenbase;
	int				count;

	lenbase = ft_strnlen(base, -1);
	count = 0;
	if (n < 0)
	{
		count++;
		i = -n;
	}
	else
		i = n;
	if (i >= lenbase || precision > 1)
		count += ft_nbrlen_base((int)(i / lenbase), base, precision - 1);
	return (count + 1);
}

int	ft_putnbr_base(int n, char *base, int precision)
{
	unsigned int	i;
	char			c;
	unsigned int	lenbase;
	int				count;

	count = 0;
	lenbase = ft_strnlen(base, -1);
	if (n < 0)
	{
		write(1, "-", 1);
		count++;
		i = -n;
	}
	else
		i = n;
	if (i >= lenbase || precision > 1)
		count += ft_putnbr_base((int)(i / lenbase), base, precision - 1);
	c = base[i % lenbase];
	write(1, &c, 1);
	return (count + 1);
}

int	ft_unbrlen_base(unsigned int un, char *base, int precision)
{
	unsigned int	lenbase;
	int				count;

	count = 0;
	lenbase = ft_strnlen(base, -1);
	if (un >= lenbase || precision > 1)
		count += ft_unbrlen_base((un / lenbase), base, precision - 1);
	return (count + 1);
}

int	ft_putunbr_base(unsigned int un, char *base, int precision)
{
	char			c;
	unsigned int	lenbase;
	int				count;

	count = 0;
	lenbase = ft_strnlen(base, -1);
	if (un >= lenbase || precision > 1)
		count += ft_putunbr_base((un / lenbase), base, precision - 1);
	c = base[un % lenbase];
	write(1, &c, 1);
	return (count + 1);
}

int	ft_putull_base(unsigned long long i, char *base)
{
	char			c;
	unsigned int	lenbase;
	int				count;

	count = 0;
	lenbase = ft_strnlen(base, -1);
	if (i >= lenbase)
		count += ft_putull_base((i / lenbase), base);
	c = base[i % lenbase];
	write(1, &c, 1);
	return (count + 1);
}
