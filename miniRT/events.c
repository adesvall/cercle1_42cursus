/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 11:29:17 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/10 16:24:04 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		handle_error(char *msg, t_scn *scn)
{
	if (write(1, msg, ft_strlen(msg))){}
	free(scn->cam);
	free(scn->lum);
	free(scn->sph);
	free(scn->pln);
	free(scn->tri);
	free(scn->cyl);
	free(scn->car);
	if (scn->mlx_win)
	{
		mlx_clear_window(scn->mlx, scn->mlx_win);
		mlx_destroy_window(scn->mlx, scn->mlx_win);
	}
	exit(1);
	return (1);
}

int		exit_and_free(t_scn *scn)
{
	free(scn->cam);
	free(scn->lum);
	free(scn->sph);
	free(scn->pln);
	free(scn->tri);
	free(scn->cyl);
	free(scn->car);
	if (scn->mlx_win)
	{
		mlx_clear_window(scn->mlx, scn->mlx_win);
		mlx_destroy_window(scn->mlx, scn->mlx_win);
	}
	exit(0);
	return (1);
}

int		get_keypress(int key, t_scn *scn)
{
	if (key == 65307)
		exit_and_free(scn);
	else if (key == 100 || key == 113 || key == 122 || key == 115 || key == 97 || key == 101)
	{
		scn->cam->origin.x += 30 * ((key == 122) - (key == 115));
		scn->cam->origin.y += 30 * ((key == 113) - (key == 100));
		scn->cam->dir = turn_vect(scn->cam->dir, M_PI/12 * ((key == 97) - (key == 101)), 0);
		create_img(scn->cam[0], *scn);
		mlx_put_image_to_window(scn->mlx, scn->mlx_win, scn->cam[0].data.img, 0, 0);
	}
	return (1);
}