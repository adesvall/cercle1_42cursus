/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 19:13:40 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/17 00:12:49 by adesvall         ###   ########.fr       */
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
	scene->ambI = 0.05;
	scene->ambCol = (t_vect){255, 255, 255};

	scene->cam = malloc(2 * sizeof(t_cam));
	scene->cam[0].origin = (t_vect){-300, 0, 200};
	scene->cam[0].dir = (t_vect){1, 0, -0.5};
	scene->cam[0].fov = 90;
	scene->cam[1].fov = 0;

	scene->sph = malloc(4 * sizeof(t_sph));
	scene->sph[0].center = (t_vect){100, -50, 0};
	scene->sph[0].radius = 30;
	scene->sph[0].color = (t_col){0, 140, 140};
	scene->sph[0].exist = 1;
	scene->sph[1].center = (t_vect){100, 50, 0};
	scene->sph[1].radius = 30; //20
	scene->sph[1].color = (t_col){140, 0, 140};
	scene->sph[1].exist = 1;
	scene->sph[2].center = (t_vect){100, -150, 0};
	scene->sph[2].radius = 30; //20
	scene->sph[2].color = (t_col){140, 140, 0};
	scene->sph[2].exist = 1;
	scene->sph[3].exist = 0;

	scene->lum = malloc(3 * sizeof(t_lum));
	scene->lum[0].pos = (t_vect){-200, -300, 100};
	scene->lum[0].I = 0.5;
	scene->lum[0].color = (t_vect){255, 255, 255};
	scene->lum[1].pos = (t_vect){0, 250, 200};
	scene->lum[1].I = 0; //.3;
	scene->lum[1].color = (t_vect){255, 255, 255};
	scene->lum[2].I = 0;
	
	scene->pln = malloc(3 * sizeof(t_pln));
	scene->pln[0].origin = (t_vect){0, 0, -30};
	scene->pln[0].normale = (t_vect){0, 0, 1};
	scene->pln[0].color = (t_col){72, 31, 10};
	scene->pln[0].exist = 1;
	scene->pln[1].origin = (t_vect){200, 0, 0};
	scene->pln[1].normale = (t_vect){-1, 0, 0};
	scene->pln[1].color = (t_col){172, 131, 110};
	scene->pln[1].exist = 1;
	scene->pln[2].exist = 0;
}

void	free_scene(t_scene scene)
{
	free(scene.cam);
	free(scene.sph);
	free(scene.pln);
	free(scene.lum);
}
