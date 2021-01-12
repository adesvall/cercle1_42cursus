/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:01:38 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/12 22:00:43 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"

void	create_window(t_scn *scn)
{
	if (!(scn->mlx_win = mlx_new_window(scn->mlx, scn->res.W, scn->res.H, "miniRT")))
		return ;//handle_error("fail to create Minilibx window", scn);
	//mlx_hook(scn->mlx_win, 2, 0, get_keypress, rt);
	//mlx_hook(scn->mlx_win, 4, 0, mouse_press, rt);
	//mlx_hook(scn->mlx_win, 5, 0, mouse_release, rt);
	//mlx_hook(scn->mlx_win, 6, 0, get_mouse_pos, rt);
	mlx_key_hook(scn->mlx_win, get_keypress, scn);
	mlx_put_image_to_window(scn->mlx, scn->mlx_win, ((t_cam*)scn->actualcam->content)->data.img, 0, 0);
	mlx_loop(scn->mlx);
}

int             main(int argc, char **argv)
{
    t_scn scn;
	t_list *ite;
	t_cam *cam;

	if (argc > 3)
		printf("Too many arguments.\n");
	if (argc == 1)
		printf("No arguments.\n");
	ft_bzero(&scn, sizeof(t_scn));
    parse_file(argv[1], &scn);
    scn.mlx = mlx_init();
    ite = scn.cams;
    while (ite)
    {
        cam = (t_cam*)ite->content;
		cam->data.img = mlx_new_image(scn.mlx, scn.res.W, scn.res.H);
        cam->data.addr = mlx_get_data_addr(cam->data.img, &cam->data.bits_per_pixel, &cam->data.line_length,
                                &cam->data.endian);
        create_img(*cam, &scn);
        ite = ite->next;
    }
	if (argc == 3 && ft_strcmp(argv[2], "-save") == 0)
	{
		save_bmp(argv[1], (unsigned char*)((t_cam*)scn.actualcam->content)->data.addr, &scn);
		exit_and_free(&scn);
	}
    else
		create_window(&scn);
}
