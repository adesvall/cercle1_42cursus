/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:33:46 by user42            #+#    #+#             */
/*   Updated: 2020/11/22 18:41:09 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t i;

	if (n == 0)
		return (dest);
	if (src == 0 && dest == 0)
		return (0);
	if (dest > src)
	{
		i = n;
		while (i >= 1)
		{
			i--;
			((char*)dest)[i] = ((char*)src)[i];
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((char*)dest)[i] = ((char*)src)[i];
			i++;
		}
	}
	return (dest);
}
