/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:01:38 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/15 19:39:21 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int             main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_scene scene;
    int		i;

    scene = (t_scene){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    init_scene(&scene);

	mlx = mlx_init();
    i = 0;
    while (scene.cam[i].fov)
    {
        mlx_win = mlx_new_window(mlx, scene.resW, scene.resH, "MiniRT");
        scene.cam[i].data.img = mlx_new_image(mlx, scene.resW, scene.resH);
        scene.cam[i].data.addr = mlx_get_data_addr(scene.cam[i].data.img, &scene.cam[i].data.bits_per_pixel, &scene.cam[i].data.line_length,
                                 &scene.cam[i].data.endian);
        create_img(scene.cam[i], scene.cam[i].data, scene);
        mlx_put_image_to_window(mlx, mlx_win, scene.cam[i].data.img, 0, 0);
        i++;
    }
    free_scene(scene);
    mlx_loop(mlx);
}
