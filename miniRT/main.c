/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:01:38 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/17 03:10:39 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
/*
void	create_window(t_scene *scn)
{
	if (!(scn->mlx_win = mlx_new_window(rt->mlx, rt->res.x,
		rt->res.y, "miniRT")))
		handle_error("fail to create Minilibx window", rt);
	mlx_hook(scn->mlx_win, 2, 0, get_keypress, rt);
	mlx_hook(scn->mlx_win, 4, 0, mouse_press, rt);
	mlx_hook(scn->mlx_win, 5, 0, mouse_release, rt);
	mlx_hook(scn->mlx_win, 6, 0, get_mouse_pos, rt);
	mlx_hook(scn->mlx_win, 17, 0, exit_and_free, rt);
	mlx_put_image_to_window(rt->mlx_ptr, scn->mlx_win, rt->cam->img.ptr, 0, 0);
	mlx_loop(rt->mlx_ptr);
}
*/
int             main(void)
{
    t_scene scn;
    int		i;

    scn = (t_scene){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    init_scene(&scn);

	scn.mlx = mlx_init();
    i = 0;
    while (scn.cam[i].fov)
    {
        scn.mlx_win = mlx_new_window(scn.mlx, scn.resW, scn.resH, "MiniRT");
        scn.cam[i].data.img = mlx_new_image(scn.mlx, scn.resW, scn.resH);
        scn.cam[i].data.addr = mlx_get_data_addr(scn.cam[i].data.img, &scn.cam[i].data.bits_per_pixel, &scn.cam[i].data.line_length,
                                 &scn.cam[i].data.endian);
        create_img(scn.cam[i], scn.cam[i].data, scn);
        mlx_put_image_to_window(scn.mlx, scn.mlx_win, scn.cam[i].data.img, 0, 0);
        i++;
    }
    free_scene(scn);
    mlx_loop(scn.mlx);
}
