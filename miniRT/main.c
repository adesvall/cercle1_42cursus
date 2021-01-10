/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:01:38 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/10 16:13:50 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	create_window(t_scn *scn)
{
	if (!(scn->mlx_win = mlx_new_window(scn->mlx, scn->resW, scn->resH, "miniRT")))
		return ;//handle_error("fail to create Minilibx window", scn);
	//mlx_hook(scn->mlx_win, 2, 0, get_keypress, rt);
	//mlx_hook(scn->mlx_win, 4, 0, mouse_press, rt);
	//mlx_hook(scn->mlx_win, 5, 0, mouse_release, rt);
	//mlx_hook(scn->mlx_win, 6, 0, get_mouse_pos, rt);
	mlx_key_hook(scn->mlx_win, get_keypress, scn);
	mlx_put_image_to_window(scn->mlx, scn->mlx_win, scn->cam->data.img, 0, 0);
	mlx_loop(scn->mlx);
}

int             main(void)
{
    t_scn scn;
    int		i;

    ft_bzero(&scn, sizeof(t_scn));
    init_scn(&scn);

	scn.mlx = mlx_init();
    i = 0;
    while (i < scn.cam[i].fov)
    {
        scn.cam[i].data.img = mlx_new_image(scn.mlx, scn.resW, scn.resH);
        scn.cam[i].data.addr = mlx_get_data_addr(scn.cam[i].data.img, &scn.cam[i].data.bits_per_pixel, &scn.cam[i].data.line_length,
                                 &scn.cam[i].data.endian);
        create_img(scn.cam[i], scn);
        create_window(&scn);
        i++;
    }
}
