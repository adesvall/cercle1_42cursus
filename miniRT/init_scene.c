/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 19:13:40 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/16 02:40:56 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
void	check_id(t_scene *scene)
{
	if (ft_strequ(scene->split[0], "R") && !scene->resH && !scene->resW)
		parse_res(scene);
	else if (ft_strequ(scene->split[0], "A") && !scene->ambI)
		parse_ambient(scene);
	else if (ft_strequ(scene->split[0], "c"))
		parse_camera(scene);
	else if (ft_strequ(scene->split[0], "l"))
		parse_light(scene);
	else if (ft_strequ(scene->split[0], "sp"))
		parse_sphere(scene);
	else if (ft_strequ(scene->split[0], "pl"))
		parse_plane(scene);
	else if (ft_strequ(scene->split[0], "sq"))
		parse_square(scene);
	else if (ft_strequ(scene->split[0], "cy"))
		parse_cylindre(scene);
	else if (ft_strequ(scene->split[0], "tr"))
		parse_triangle(scene);
	else if (scene->split[0][0] == '#' || ft_strequ(scene->split[0], "#"))
		;
	else if (check_id_bonus(scene))
		;
	else
		handle_error("parsing error", scene);
}

void	parse_rt_file(char *rt_file, t_scene *scene)
{
	int		fd;

	if ((fd = open(rt_file, O_RDONLY)) < 0)
		handle_error("fail to open scene file", scene);
	while (get_next_line(fd, scene->line) > 0)
	{
		scene->split = ft_split(scene->line, " \t\v\n\r\f");
		if (scene->split[0])
			check_id(scene);
		scene->split = free_split(scene->split);
		free(scene->line);
	}
	close(fd);
	if (scene->cam == 0)
		handle_error("no camera available", scene);
	if (!scene->resH || !scene->resH)
		handle_error("no resolution", scene);
}
*/
void	init_scene(t_scene *scene)
{
	scene->resW = 1920;
	scene->resH = 1080;
	scene->ambI = 0;
	scene->ambCol = (t_vect){255, 255, 255};

	scene->cam = malloc(2 * sizeof(t_cam));
	scene->cam[0].origin = (t_vect){0, 0, 0};
	scene->cam[0].dir = (t_vect){1, 0, 0};
	scene->cam[0].fov = 120;
	scene->cam[1].fov = 0;

	scene->sph = malloc(3 * sizeof(t_sph));
	scene->sph[0].center = (t_vect){100, 0, 20};
	scene->sph[0].radius = 20;
	scene->sph[0].color = (t_col){240, 240, 30};
	scene->sph[1].center = (t_vect){100, 0, -10};
	scene->sph[1].radius = 30;
	scene->sph[1].color = (t_col){30, 240, 240};
	scene->sph[2].radius = 0;

	scene->lum = malloc(2 * sizeof(t_lum));
	scene->lum[0].pos = (t_vect){0, -200, 0};
	scene->lum[0].I = 0.5;
	scene->lum[0].color = (t_vect){255, 255, 255};
	scene->lum[1].I = 0;
}

void	free_scene(t_scene scene)
{
	free(scene.cam);
	free(scene.sph);
	free(scene.lum);
}
