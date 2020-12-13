/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:03:35 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/14 00:11:40 by adesvall         ###   ########.fr       */
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

void	create_img(t_data img)
{
	int	i;
	int	j;
	t_vect col, lum;
	t_sph sph;
	t_ray ray;
	int value;
	
	lum = newvect(-100, 0, 0);
	sph.center = newvect(0, 0, 100);
	sph.radius = 20;
	ray.origin = newvect(0, 0, 0);
	i=0;
	while (i < img.resy)
	{
		j=0;
		while (j < img.resx)
		{
			ray.dir = newvect(j - img.resx / 2, i - img.resy / 2, img.resx / 2 / tan(90/2));
			ray.dir = div(norm(ray.dir), ray.dir);
			col = collision_sph(ray, sph);
			if (col.x == ray.origin.x && col.y == ray.origin.y && col.x == ray.origin.x)
				my_mlx_pixel_put(&img, j, i, create_trgb(0, 50, 50, 50));
			else
			{
				value = 256*dot(diff(col, sph.center), diff(lum, col)); // pow(norm(diff(lum, col)), 2);
				if (value < 0)
					value = 0;
				else if (value > 255)
					value = 255;
				my_mlx_pixel_put(&img, j, i, create_trgb(0, 0, value, value));
			}
			j++;
		}
    	i++;
    }
}