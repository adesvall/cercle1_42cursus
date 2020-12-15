/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:01:38 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/15 02:25:00 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int             main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;
    t_scene scene;
    int		i,j;

    scene = (t_scene){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    scene.resW = 1600;
	scene.resH = 900;

	mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, scene.resW, scene.resH, "MiniRT");
    img.img = mlx_new_image(mlx, scene.resW, scene.resH);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    create_img(img, scene);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}
