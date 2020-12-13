/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:01:38 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/13 23:24:59 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int             main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;
    int i,j;

    img.resx = 1920;
	img.resy = 1080;
	mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, img.resx, img.resy, "MiniRT");
    img.img = mlx_new_image(mlx, img.resx, img.resy);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    create_img(img);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}
