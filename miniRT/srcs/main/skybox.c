/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:37:30 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/15 19:46:52 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_data	create_sky(t_scn *scn, char *file_path)
{
	t_data tex;

	if (!(tex.img = mlx_xpm_file_to_image(scn->mlx, file_path,
		&tex.W, &tex.H)))
		handle_error("fail creating skybox", IMG_FAIL, scn);
	if (!(tex.addr = mlx_get_data_addr(tex.img, &tex.bits_per_pixel,
		&tex.line_length, &tex.endian)))
		handle_error("fail creating skybox", IMG_FAIL, scn);
	return (tex);
}

t_rgb		get_sky_color(t_data sky, float x, float y, float max)
{
	int		i;
	int		column;
	int		row;
	t_rgb	color;

	max = fabs(max);
	column = (int)(sky.width * (0.5 * (x / max + 1)));
	row = (int)(sky.height * (0.5 * (y / max + 1)));
	i = row * sky.size_line + sky.bpp / 8 * column;
	color.b = (float)(unsigned char)sky.img[i] / 255;
	color.g = (float)(unsigned char)sky.img[i + 1] / 255;
	color.r = (float)(unsigned char)sky.img[i + 2] / 255;
	return (color);
}

void		free_sky(t_scn *rt)
{
	int		i;

	i = 0;
	while (rt->sky[i].img)
	{
		if (rt->sky[i].img)
			mlx_destroy_image(rt->mlx_ptr, rt->sky[i].ptr);
		i++;
	}
	free(rt->sky);
}

t_rgb		get_sky_coord(t_scn *rt)
{
	t_rgb	color;
	float	m;

	ft_bzero(&color, sizeof(t_rgb));
	rt->ray.dir = vec_normalize(rt->ray.dir);
	if (fabs(rt->ray.dir.z) >= fabs(rt->ray.dir.y) && fabs(rt->ray.dir.z)
	>= fabs(rt->ray.dir.x) && rt->ray.dir.z < 0 && (m = rt->ray.dir.z) > -10)
		color = get_sky_color(rt->sky[0], -rt->ray.dir.x, -rt->ray.dir.y, m);
	else if (fabs(rt->ray.dir.z) >= fabs(rt->ray.dir.y) && fabs(rt->ray.dir.z)
	>= fabs(rt->ray.dir.x) && rt->ray.dir.z > 0 && (m = rt->ray.dir.z) > -10)
		color = get_sky_color(rt->sky[1], rt->ray.dir.x, -rt->ray.dir.y, m);
	else if (fabs(rt->ray.dir.x) > fabs(rt->ray.dir.z) && fabs(rt->ray.dir.x)
	> fabs(rt->ray.dir.y) && rt->ray.dir.x < 0 && (m = rt->ray.dir.x) > -10)
		color = get_sky_color(rt->sky[2], rt->ray.dir.z, -rt->ray.dir.y, m);
	else if (fabs(rt->ray.dir.x) > fabs(rt->ray.dir.z) && fabs(rt->ray.dir.x)
	> fabs(rt->ray.dir.y) && rt->ray.dir.x > 0 && (m = rt->ray.dir.x) > -10)
		color = get_sky_color(rt->sky[3], -rt->ray.dir.z, -rt->ray.dir.y, m);
	else if (fabs(rt->ray.dir.y) >= fabs(rt->ray.dir.z) && fabs(rt->ray.dir.y)
	>= fabs(rt->ray.dir.x) && rt->ray.dir.y < 0 && (m = rt->ray.dir.y) > -10)
		color = get_sky_color(rt->sky[4], -rt->ray.dir.x, rt->ray.dir.z, m);
	else if (fabs(rt->ray.dir.y) >= fabs(rt->ray.dir.z) && fabs(rt->ray.dir.y)
	>= fabs(rt->ray.dir.x) && rt->ray.dir.y > 0 && (m = rt->ray.dir.y) > -10)
		color = get_sky_color(rt->sky[5], rt->ray.dir.x, rt->ray.dir.z, m);
	return (color);
}
