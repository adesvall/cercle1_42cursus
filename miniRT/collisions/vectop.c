/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 20:51:54 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/16 17:50:53 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		limit_color(double n)
{
	if (n > 255)
		return (255);
	if (n < 0)
		return (0);
	return ((int)n);
}

t_col	mult_col(double n, t_vect coef, t_col color)
{
	color.r = limit_color(color.r * n * coef.x);
	color.g = limit_color(color.g * n * coef.y);
	color.b = limit_color(color.b * n * coef.z);
	return (color);
}

int		egal_vect(t_vect v1, t_vect v2)
{
	return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}

t_vect	sum(t_vect v1, t_vect v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_vect	diff(t_vect v1, t_vect v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}

t_vect	mult(double n, t_vect v)
{
	v.x *= n;
	v.y *= n;
	v.z *= n;
	return (v);
}

t_vect	divn(double n, t_vect v)
{
	v.x /= n;
	v.y /= n;
	v.z /= n;
	return (v);
}

double	dot(t_vect v1, t_vect v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	norm(t_vect v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

double	normed_dot(t_vect v1, t_vect v2)
{
	return ((v1.x * v2.x + v1.y * v2.y + v1.z * v2.z) / norm(v1) / norm(v2));
}

t_vect	normalize(t_vect v)
{
	return (divn(norm(v), v));
}

t_vect	prod_vect(t_vect v1, t_vect v2)
{
	t_vect	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}

t_vect	turn_vect(t_vect dir0, double angw, double angh)
{
	t_vect	tmp, res, axe;

	tmp = (t_vect){cos(angw) * dir0.x - sin(angw) * dir0.y, sin(angw) * dir0.x + cos(angw) * dir0.y, dir0.z};
	res = mult(cos(angh), tmp);
	axe = normalize((t_vect){-tmp.y, tmp.x, 0});
	return (normalize(sum(res, mult(sin(angh), prod_vect(axe, tmp)))));
}