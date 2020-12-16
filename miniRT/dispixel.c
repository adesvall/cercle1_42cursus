/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:03:35 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/16 23:53:58 by adesvall         ###   ########.fr       */
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
	t_vect down, right;
	int color;
	t_ray ray;
	double fov = cam.fov;

	ray.origin = cam.origin;
	cam.dir = normalize(cam.dir);
	right = normalize((t_vect){100*cam.dir.y/cam.dir.x, -100, 0});
	down = normalize(prod_vect(cam.dir, right));

	i = 0;
	while (i < scene.resH)
	{
		j = 0;
		while (j < scene.resW)
		{
			ray.dir = normalize(sum(cam.dir, sum(mult(tan(fov * M_PI / 360) * (j - scene.resW / 2)/scene.resW, right), mult(tan(fov * M_PI / 360) * (i - scene.resH / 2)/scene.resW, down))));
			//ray.dir = newvect(scene.resW / 2 / tan(90/2), j - scene.resW / 2, i - scene.resH / 2);
			//ray.dir = turn_vect(ray.dir, atan2(ray.origin.y, ray.origin.x), atan2(ray.origin.z, norm((t_vect){ray.origin.x, ray.origin.y, 0})) + M_PI / 4);
			//ray.dir = turn_vect(camdir, -(j - scene.resW / 2) * fov * M_PI / (180 * scene.resW), (i - scene.resH / 2) * fov * M_PI / (180 * scene.resW));
			color = find_col(ray, scene);
			my_mlx_pixel_put(&img, j, i, color);
			j++;
		}
    	i++;
    }
}
