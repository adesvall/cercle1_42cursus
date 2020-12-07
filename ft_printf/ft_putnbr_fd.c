/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:08:23 by adesvall          #+#    #+#             */
/*   Updated: 2020/11/21 22:58:47 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(int n, char *base)
{
	unsigned int	i;
	char			c;
	int				lenbase;
	int				count;

	lenbase = ft_strnlen(base, -1);
	if (n < 0)
	{
		write(1, "-", 1);
		count++;
		i = -n;
	}
	else
		i = n;
	if (i > 9)
		count += ft_putnbr_base((int)(i / lenbase), base);
	c = base[i % lenbase];
	write(1, &c, 1);
	return (count + 1);
}
