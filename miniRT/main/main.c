/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:01:38 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/14 16:48:57 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	create_window(t_scn *scn)
{
	printf("Creating window...\n");
	if (!(scn->mlx_win = mlx_new_window(scn->mlx, scn->res.W, scn->res.H, "miniRT")))
		handle_error("Fail to create Minilibx window", WINDOW_FAIL, scn);
	scn->actualcam = scn->cams;
	scn->actuallum = scn->lums;
	scn->sl_obj.pos = &((t_cam*)scn->actualcam->content)->origin;
	scn->sl_obj.dir = &((t_cam*)scn->actualcam->content)->dir;
	printf("The actual Camera is selected.\n");
	//mlx_hook(scn->mlx_win, ButtonPress, NoEventMask, mouse_press, scn);
	//mlx_hook(scn->mlx_win, 5, 0, mouse_release, rt);
	//mlx_hook(scn->mlx_win, 6, 0, get_mouse_pos, rt);
	mlx_mouse_hook(scn->mlx_win, mouse_press, scn);
	mlx_hook(scn->mlx_win, ClientMessage, NoEventMask, exit_and_free, scn);
	mlx_key_hook(scn->mlx_win, get_keypress, scn);
	mlx_put_image_to_window(scn->mlx, scn->mlx_win, ((t_cam*)scn->actualcam->content)->data.img, 0, 0);
	mlx_loop(scn->mlx);
}

void	create_all_img(t_scn *scn)
{
	t_list	*ite;
	t_cam	*cam;

	ite = scn->cams;
    while (ite)
    {
        cam = (t_cam*)ite->content;
		cam->data.img = mlx_new_image(scn->mlx, scn->res.W, scn->res.H);
        cam->data.addr = mlx_get_data_addr(cam->data.img, &cam->data.bits_per_pixel, &cam->data.line_length,
                                &cam->data.endian);
        create_img(cam, scn);
        ite = ite->next;
    }
}

void	set_cam(t_cam *cam)
{
	if (cam->dir.x == 0 && cam->dir.y == 0)
		cam->right = normalize((t_vect){0, -1, 0});
	else
		cam->right = normalize((t_vect){100*cam->dir.y, -100*cam->dir.x, 0});
	cam->down = normalize(prod_vect(cam->dir, cam->right));
}

int		main(int argc, char **argv)
{
    t_scn scn;

	if (argc == 1 || argc > 3)
	{
		printf(argc == 1 ? "No arguments.\n" : "Too many arguments.\n");
		exit(1);
	}
	ft_bzero(&scn, sizeof(t_scn));
    scn.filename = argv[1];
	parse_file(&scn);
    scn.mlx = mlx_init();
	printf("\033[0;32mRendering miniRT...\n\033[0m");
    create_all_img(&scn);
	if (argc == 3 && !ft_strcmp(argv[2], "-save"))
	{
		printf("Saving to save.bmp ..\n");
		save_bmp("save.bmp", (unsigned char*)((t_cam*)scn.actualcam->content)->data.addr, &scn);
		exit_and_free(&scn);
	}
    else
	{
		if (argc == 3)
			printf("Second argument ignored.\n");
		create_window(&scn);
	}
}
