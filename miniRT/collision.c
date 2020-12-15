/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:31:37 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/15 20:34:08 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		find_col(t_ray ray, t_scene scene)
{
	int		i;
	int		value;
	t_vect	col, closest;
	double	rescol;

	closest = (t_vect){0, 0, 0};
	value = 50;
	if (scene.sph)
	{
		i = 0;
		while (scene.sph[i].radius)
		{
			if ((rescol = collision_sph(ray, scene.sph[i])) != -1)
			{
				col = sum(ray.origin, mult(rescol, ray.dir));
				if (norm(diff(col, ray.origin)) < norm(diff(closest, ray.origin)) || egal_vect(closest, (t_vect){0, 0, 0}))
				{
					closest = col;
					if (i == 0 || collision_sph((t_ray){closest, normalize(diff(scene.lum[0].pos, closest))}, scene.sph[0]) == -1)
						value += 150*dot(diff(col, scene.sph[i].center), diff(scene.lum[0].pos, col));// pow(norm(diff(lum, col)), 2);
					else
						value = 0;
					
				}
			}
			i++;
		}
	}
	if (value < 0)
		value = 0;
	else if (value > 255)
		value = 255;
	return (create_trgb(0, value, value, value));
}

double	collision_sph(t_ray ray, t_sph sphere)
{
	double	a, b, c, delta, res;

	a = pow(ray.dir.x, 2) + pow(ray.dir.y, 2) + pow(ray.dir.z, 2);
	b = 2 * (ray.dir.x * (ray.origin.x - sphere.center.x) + ray.dir.y * (ray.origin.y - sphere.center.y) + ray.dir.z * (ray.origin.z - sphere.center.z));
	c = pow(ray.origin.x - sphere.center.x, 2) + pow(ray.origin.y - sphere.center.y, 2) + pow(ray.origin.z - sphere.center.z, 2) - pow(sphere.radius, 2);
	delta = pow(b, 2) - 4 * a * c;
	if (delta >= 0)
	{
		res = -(b + sqrt(delta))/(2*a);
		if (res > 0)
			return (res);
	}
	return (-1);
}