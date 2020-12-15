/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:03:35 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/15 06:06:51 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	create_img(t_data img, t_scene scene)
{
	int	i;
	int	j;
	t_sph	sph;
	t_vect col, lum, camdir, up , right;
	t_ray ray;
	int value;
	double fov = 100;
	
	lum = newvect(0, -100, 0);
	sph.center = (t_vect){100, 0, 0};
	sph.radius = 20;
	scene.sph = &sph;
	ray.origin = newvect(0, 0, 0);
	camdir = normalize((t_vect){1, 0, 0});
	
	right = normalize((t_vect){-100*camdir.y/camdir.x, 100, 0});
	up = normalize(prod_vect(right, camdir));

	i=0;
	while (i < scene.resH)
	{
		j=0;
		while (j < scene.resW)
		{
			ray.dir = normalize(sum(camdir, sum(mult(2.0*(j - scene.resW / 2)/scene.resW,right), mult(2.0*(i - scene.resH / 2)/scene.resW, up))));
			//ray.dir = newvect(scene.resW / 2 / tan(90/2), j - scene.resW / 2, i - scene.resH / 2);
			//ray.dir = turn_vect(ray.dir, atan2(ray.origin.y, ray.origin.x), atan2(ray.origin.z, norm((t_vect){ray.origin.x, ray.origin.y, 0})) + M_PI / 4);
			//ray.dir = turn_vect(camdir, -(j - scene.resW / 2) * fov * M_PI / (180 * scene.resW), (i - scene.resH / 2) * fov * M_PI / (180 * scene.resW));
			col = collision_sph(ray, sph);
			if (col.x == 0 && col.y == 0 && col.x == 0)
				my_mlx_pixel_put(&img, j, i, create_trgb(0, 50, 50, 50));
			else
			{
				value = 150*dot(diff(col, sph.center), diff(lum, col))+50; // pow(norm(diff(lum, col)), 2);
				if (value < 0)
					value = 0;
				else if (value > 255)
					value = 255;
				my_mlx_pixel_put(&img, j, i, create_trgb(0, value, value, value));
			}
			j++;
		}
    	i++;
    }
}