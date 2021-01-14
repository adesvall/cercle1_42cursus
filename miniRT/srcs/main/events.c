/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 11:29:17 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/14 17:32:44 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	free_cams_img(t_list *cams, void *mlx)
{
	void	*ptr;

	while (cams)
	{
		ptr = ((t_cam*)cams->content)->data.img;
		if (ptr)
			mlx_destroy_image(mlx, ptr);
		cams = cams->next;
	}
}

void	clean_scene(t_scn *scn)
{
	free_cams_img(scn->cams, scn->mlx);
	ft_lstclear(&scn->cams, free);
	ft_lstclear(&scn->sphs, free);
	ft_lstclear(&scn->lums, free);
	ft_lstclear(&scn->plns, free);
	ft_lstclear(&scn->tris, free);
	ft_lstclear(&scn->cyls, free);
	ft_lstclear(&scn->sqrs, free);
}

int		handle_error(char *msg, int err, t_scn *scn)
{
	printf("%s - code: %d\n", msg, err);
	clean_scene(scn);
	if (scn->mlx_win)
	{
		mlx_clear_window(scn->mlx, scn->mlx_win);
		mlx_destroy_window(scn->mlx, scn->mlx_win);
	}
	exit(err);
	return (err);
}

int		exit_and_free(t_scn *scn)
{
	clean_scene(scn);
	if (scn->mlx_win)
	{
		mlx_clear_window(scn->mlx, scn->mlx_win);
		mlx_destroy_window(scn->mlx, scn->mlx_win);
	}
	exit(0);
	return (0);
}

int		get_keypress(int key, t_scn *scn)
{
	t_cam 	*cam;
	t_lum	*lum;
	
	//printf("%d\n", key);
	if (key == 65307) //ESC
		exit_and_free(scn);
	else if (key == 108) //L
	{
		if ((scn->actuallum = scn->actuallum->next) == NULL)
			scn->actuallum = scn->lums;
		lum = scn->actuallum->content;
		scn->sl_obj.pos = &lum->pos;
		scn->sl_obj.dir = NULL;
		printf("You selected Light at (%.0f,%.0f,%.0f).\n",
					scn->sl_obj.pos->x, scn->sl_obj.pos->y, scn->sl_obj.pos->z);
	}
	else if (key == 100 || key == 122 || key == 115 || key == 65361 || key == 65363
			|| key == 65364 || key == 65362 || key == 113 || key == 120 || key == 119) //zqsdwx<>^v
	{
		translate(scn->sl_obj.pos, 5 * ((key == 122) - (key == 115)),
					5 * ((key == 113) - (key == 100)), 5 * ((key == 120) - (key == 119)));
		if (scn->sl_obj.dir && (key == 65361 || key == 65363 || key == 65364 || key == 65362))
			*scn->sl_obj.dir = turn_vect(*scn->sl_obj.dir, M_PI/12 * ((key == 65361) - (key == 65363)), M_PI/20 * ((key == 65364) - (key == 65362)));
		create_img((cam = scn->actualcam->content), scn);
		mlx_put_image_to_window(scn->mlx, scn->mlx_win, cam->data.img, 0, 0);
	}
	else if (key == 99) //C
	{
		if ((scn->actualcam = scn->actualcam->next) == NULL)
			scn->actualcam = scn->cams;
		cam = scn->actualcam->content;
		scn->sl_obj.pos = &cam->origin;
		scn->sl_obj.dir = &cam->dir;
		create_img(cam, scn);
		printf("The actual Camera is selected.\n");
		mlx_put_image_to_window(scn->mlx, scn->mlx_win, cam->data.img, 0, 0);
	}
	else if (key == 114) //R
	{
		clean_scene(scn);
		parse_file(scn);
		scn->actualcam = scn->cams;
		cam = scn->actualcam->content;
		scn->actuallum = scn->lums;
		scn->sl_obj.pos = &cam->origin;
		scn->sl_obj.dir = &cam->dir;
		create_all_img(scn);
		printf("The actual Camera is selected.\n");
		mlx_put_image_to_window(scn->mlx, scn->mlx_win, cam->data.img, 0, 0);
	}
	return (1);
}

int		mouse_press(int button, int x, int y, t_scn *scn)
{
	t_rescl res;
	t_cam *cam = scn->actualcam->content;

	if (button == Button1 && (res = collision_any(find_ray(cam, y, x, scn), scn, NULL, -1)).elem != NULL)
	{
		scn->sl_obj.pos = res.pos;
		scn->sl_obj.dir = res.dir;
		if (res.dir)
			printf("You selected %s at (%.0f,%.0f,%.0f) with direction (%.2f,%.2f,%.2f).\n", res.type,
					scn->sl_obj.pos->x, scn->sl_obj.pos->y, scn->sl_obj.pos->z,
					scn->sl_obj.dir->x, scn->sl_obj.dir->y, scn->sl_obj.dir->z);
		else
			printf("You selected %s at (%.0f,%.0f,%.0f).\n", res.type,
					scn->sl_obj.pos->x, scn->sl_obj.pos->y, scn->sl_obj.pos->z);
	}
	else
	{
		scn->sl_obj.pos = &cam->origin;
		scn->sl_obj.dir = &cam->dir;
		printf("You selected the actual Camera at (%.0f,%.0f,%.0f) with direction (%.2f,%.2f,%.2f).\n",
					scn->sl_obj.pos->x, scn->sl_obj.pos->y, scn->sl_obj.pos->z,
					scn->sl_obj.dir->x, scn->sl_obj.dir->y, scn->sl_obj.dir->z);
	}
	return (1);
}