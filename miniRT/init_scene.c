/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 19:13:40 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/15 00:12:22 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


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

void	init_scene(t_scene *scene)
{
	scene->sph = malloc(sizeof(t_sph));
	scene->lum = malloc(sizeof(t_lum));
	scene->lum->pos = newvect(-100, 0, 0);
	scene->lum->I = 1;
	scene->sph->center = newvect(0, 0, 100);
	scene->sph->radius = 20;
}