/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:55:11 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/12 22:44:59 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vect	tabto_vect(char **s)
{
	t_vect v;

	v.x = ft_atod(s[0]);
	v.y = ft_atod(s[1]);
	v.z = ft_atod(s[2]);
	return (v);
}

t_vect	tabto_lumrgb(char **s)
{
	t_vect v;

	v.x = limit_color(ft_atod(s[0]));
	v.y = limit_color(ft_atod(s[1]));
	v.z = limit_color(ft_atod(s[2]));
	return (v);
}

t_rgb	tabto_rgb(char **s)
{
	t_rgb v;

	v.r = (int)limit_color(ft_atod(s[0]));
	v.g = (int)limit_color(ft_atod(s[1]));
	v.b = (int)limit_color(ft_atod(s[2]));
	return (v);
}