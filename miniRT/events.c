/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 11:29:17 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/12 21:47:30 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"

int		handle_error(char *msg, int err, t_scn *scn)
{
	if (write(1, msg, ft_strlen(msg))){}
	ft_lstclear(&scn->cams, free);
	ft_lstclear(&scn->sphs, free);
	ft_lstclear(&scn->lums, free);
	ft_lstclear(&scn->plns, free);
	ft_lstclear(&scn->tris, free);
	ft_lstclear(&scn->cyls, free);
	ft_lstclear(&scn->sqrs, free);
	if (scn->mlx_win)
	{
		mlx_clear_window(scn->mlx, scn->mlx_win);
		mlx_destroy_window(scn->mlx, scn->mlx_win);
	}
	exit(err);
	return (1);
}

int		exit_and_free(t_scn *scn)
{
	ft_lstclear(&scn->cams, free);
	ft_lstclear(&scn->sphs, free);
	ft_lstclear(&scn->lums, free);
	ft_lstclear(&scn->plns, free);
	ft_lstclear(&scn->tris, free);
	ft_lstclear(&scn->cyls, free);
	ft_lstclear(&scn->sqrs, free);
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
	t_cam *cam = scn->actualcam->content;
	
	if (key == 65307)
		exit_and_free(scn);
	else if (key == 100 || key == 113 || key == 122 || key == 115 || key == 97 || key == 101)
	{
		cam->origin.x += 30 * ((key == 122) - (key == 115));
		cam->origin.y += 30 * ((key == 113) - (key == 100));
		cam->dir = turn_vect(cam->dir, M_PI/12 * ((key == 97) - (key == 101)), 0);
		create_img(*cam, scn);
		mlx_put_image_to_window(scn->mlx, scn->mlx_win, cam->data.img, 0, 0);
	}
	else if (key == 99)
	{
		if ((scn->actualcam = scn->actualcam->next) == NULL)
			scn->actualcam = scn->cams;
		cam = scn->actualcam->content;
		mlx_put_image_to_window(scn->mlx, scn->mlx_win, cam->data.img, 0, 0);
	}
	return (1);
}