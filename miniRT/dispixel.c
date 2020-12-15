/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:03:35 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/15 20:16:44 by adesvall         ###   ########.fr       */
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

void	create_img(t_cam cam, t_data img, t_scene scene)
{
	int	i;
	int	j;
	t_sph	sph;
	t_vect lum, camdir, up , right;
	int col;
	t_ray ray;
	int value;
	double fov = cam.fov;

	sph = scene.sph[0];
	ray.origin = cam.origin;
	camdir = normalize(cam.dir);
	right = normalize((t_vect){-100*camdir.y/camdir.x, 100, 0});
	up = normalize(prod_vect(right, camdir));
	lum = scene.lum[0].pos;

	i=0;
	while (i < scene.resH)
	{
		j=0;
		while (j < scene.resW)
		{
			ray.dir = normalize(sum(camdir, sum(mult(tan(fov * M_PI / 360) * (j - scene.resW / 2)/scene.resW,right), mult(tan(fov * M_PI / 360) * (i - scene.resH / 2)/scene.resW, up))));
			//ray.dir = newvect(scene.resW / 2 / tan(90/2), j - scene.resW / 2, i - scene.resH / 2);
			//ray.dir = turn_vect(ray.dir, atan2(ray.origin.y, ray.origin.x), atan2(ray.origin.z, norm((t_vect){ray.origin.x, ray.origin.y, 0})) + M_PI / 4);
			//ray.dir = turn_vect(camdir, -(j - scene.resW / 2) * fov * M_PI / (180 * scene.resW), (i - scene.resH / 2) * fov * M_PI / (180 * scene.resW));
			col = find_col(ray, scene);
			my_mlx_pixel_put(&img, j, i, col);
			j++;
		}
    	i++;
    }
}
