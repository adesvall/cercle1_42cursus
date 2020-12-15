/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 20:51:54 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/15 19:34:53 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vect	newvect(double x, double y, double z)
{
	t_vect res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
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
	return ((v1.x * v2.x + v1.y * v2.y + v1.z * v2.z) / norm(v1) / norm(v2));
}

double	norm(t_vect v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
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