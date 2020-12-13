/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:31:37 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/13 23:16:01 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vect collision_sph(t_ray ray, t_sph sphere)
{
	double	a, b, c, delta;

	a = pow(ray.dir.x, 2) + pow(ray.dir.y, 2) + pow(ray.dir.z, 2);
	b = 2 * (ray.dir.x * (ray.origin.x - sphere.center.x) + ray.dir.y * (ray.origin.y - sphere.center.y) + ray.dir.z * (ray.origin.z - sphere.center.z));
	c = pow(ray.origin.x - sphere.center.x, 2) + pow(ray.origin.y - sphere.center.y, 2) + pow(ray.origin.z - sphere.center.z, 2) - pow(sphere.radius, 2);
	delta = pow(b, 2) - 4 * a * c;
	if (delta >= 0)
		return (sum(ray.origin, mult(-(b + sqrt(delta))/(2*a) , ray.dir)));
	return (ray.origin);
}