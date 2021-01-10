/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:03:35 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/10 16:15:01 by adesvall         ###   ########.fr       */
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

void	create_img(t_cam cam, t_scn scn)
{
	int	nthr;
	pthread_t	t[4];
	t_targs		arg[4];

	cam.dir = normalize(cam.dir);
	if (cam.dir.x == 0 && cam.dir.y == 0)
		cam.right = normalize((t_vect){1, 0, 0});
	else
		cam.right = normalize((t_vect){100*cam.dir.y, -100*cam.dir.x, 0});
	cam.down = normalize(prod_vect(cam.dir, cam.right));

	nthr = 0;
	while (nthr < 4)
	{
		arg[nthr] = (t_targs){nthr * scn.resH/4, cam, scn, 0};
		pthread_create(&t[nthr], NULL, (void*)find_col, &arg[nthr]);
		nthr++;
	}
	nthr = 0;
	while (nthr < 4)
	{
		if (t[nthr])
			pthread_join(t[nthr], NULL);
		nthr++;
	}
	
	/*int i=0;
	while (i < scn.resH)
	{
		nthr=0;
		while (nthr < 16)
		{
			if (i < scn.resH)
			{
				arg[nthr] = (t_targs){i, cam, scn, 0};
				pthread_create(&t[nthr], NULL, (void*)find_col, &arg[nthr]);
			}
			else
				t[nthr] = (pthread_t)0;
			nthr++;
			i++;
		}
		nthr=0;
		while (nthr < 16)
		{
			if (t[nthr])
				pthread_join(t[nthr], NULL);
			nthr++;
		}
	}*/
}
