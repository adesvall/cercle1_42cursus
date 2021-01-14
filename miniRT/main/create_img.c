/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:03:35 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/13 23:46:14 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_ray	find_ray(t_cam *cam, int i, int j, t_scn *scn)
{
	t_vect	right;
	t_vect	down;

	right = mult(tan(cam->fov * M_PI / 360) * (j - scn->res.W / 2)/scn->res.W, cam->right);
	down = mult(tan(cam->fov * M_PI / 360) * (i - scn->res.H / 2)/scn->res.W, cam->down);
	return ((t_ray){cam->origin, normalize(sum(cam->dir, sum(right, down)))});
}

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

void	create_img(t_cam *cam, t_scn *scn)
{
	//int	nthr;
	//pthread_t	t[4];
	//t_targs		arg[4];
	
	set_cam(cam);
	fill_img(&(t_targs){0, cam, scn});
	/*
	nthr = 0;
	while (nthr < 4)
	{
		arg[nthr] = (t_targs){nthr * scn->res.H/4, cam, scn, 2};
		pthread_create(&t[nthr], NULL, (void*)fill_img, &arg[nthr]);
		nthr++;
	}
	nthr = 0;
	while (nthr < 4)
	{
		if (t[nthr])
			pthread_join(t[nthr], NULL);
		nthr++;
	}*/
}
