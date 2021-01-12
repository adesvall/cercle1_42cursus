/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:36:56 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/12 21:10:14 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int		set_res(char **split, t_scn *scn)
{
	scn->res.W = ft_atoi(split[1]);
	scn->res.H = ft_atoi(split[2]);
	return (0);
}

int		set_ambLum(char **split, t_scn *scn)
{
	char **splitcol;

	if (ft_tablen(split) != 3)
		return (1);
	scn->ambI = ft_atod(split[1]);
	if (scn->ambI < 0 || scn->ambI > 1)
		return (2);
	splitcol = ft_split(split[2], ',');
	if (ft_tablen(splitcol) != 3)
	{
		ft_abort(splitcol);
		return (2);
	}
	scn->ambCol = tabto_lumrgb(splitcol);
	ft_abort(splitcol);
	return (0);
}

int 	add_cam(char **split, t_scn *scn)
{
	char	**spos;
	char 	**sdir;
	t_cam	*cam;

	if (!(cam = malloc(sizeof(t_cam))))
		handle_error("Malloc failed", 10, scn);
	if (ft_tablen(split) != 4)
		return (1);
	spos = ft_split(split[1], ',');
	if (ft_tablen(spos) != 3)
	{
		ft_abort(spos);
		return (2);
	}
	cam->origin = tabto_vect(spos);
	ft_abort(spos);
	sdir = ft_split(split[2], ',');
	if (ft_tablen(sdir) != 3)
	{
		ft_abort(sdir);
		return (2);
	}
	cam->dir = normalize(tabto_vect(sdir));
	ft_abort(sdir);
	cam->fov = ft_atod(split[3]);
	ft_lstadd_front(&(scn->cams), ft_lstnew(cam));
	return (0);
}

int 	add_lum(char **split, t_scn *scn)
{
	char	**spos;
	char 	**srgb;
	t_lum	*lum;

	if (!(lum = malloc(sizeof(t_lum))))
		handle_error("Malloc failed", 10, scn);
	if (ft_tablen(split) != 4)
		return (1);
	spos = ft_split(split[1], ',');
	if (ft_tablen(spos) != 3)
	{
		ft_abort(spos);
		return (2);
	}
	lum->pos = tabto_vect(spos);
	ft_abort(spos);
	lum->I = ft_atod(split[2]);
	srgb = ft_split(split[3], ',');
	if (ft_tablen(srgb) != 3)
	{
		ft_abort(srgb);
		return (2);
	}
	lum->color = tabto_lumrgb(srgb);
	ft_abort(srgb);
	ft_lstadd_front(&(scn->lums), ft_lstnew(lum));
	return (0);
}

int 	add_sph(char **split, t_scn *scn)
{
	char	**spos;
	char 	**srgb;
	t_sph	*sph;

	if (!(sph = malloc(sizeof(t_sph))))
		handle_error("Malloc failed", 10, scn);
	if (ft_tablen(split) != 4)
		return (1);
	spos = ft_split(split[1], ',');
	if (ft_tablen(spos) != 3)
	{
		ft_abort(spos);
		return (2);
	}
	sph->center = tabto_vect(spos);
	ft_abort(spos);
	sph->radius = ft_atod(split[2]) / 2;
	srgb = ft_split(split[3], ',');
	if (ft_tablen(srgb) != 3)
	{
		ft_abort(srgb);
		return (2);
	}
	sph->color = tabto_rgb(srgb);
	ft_abort(srgb);
	ft_lstadd_front(&(scn->sphs), ft_lstnew(sph));
	return (0);
}

int 	add_pln(char **split, t_scn *scn)
{
	char	**spos;
	char	**sdir;
	char 	**srgb;
	t_pln	*pln;

	if (!(pln = malloc(sizeof(t_pln))))
		handle_error("Malloc failed", 10, scn);
	if (ft_tablen(split) != 4)
		return (1);
	spos = ft_split(split[1], ',');
	if (ft_tablen(spos) != 3)
	{
		ft_abort(spos);
		return (2);
	}
	pln->origin = tabto_vect(spos);
	ft_abort(spos);
	sdir = ft_split(split[2], ',');
	if (ft_tablen(sdir) != 3)
	{
		ft_abort(sdir);
		return (2);
	}
	pln->normale = normalize(tabto_vect(sdir));
	ft_abort(sdir);
	srgb = ft_split(split[3], ',');
	if (ft_tablen(srgb) != 3)
	{
		ft_abort(srgb);
		return (2);
	}
	pln->color = tabto_rgb(srgb);
	ft_abort(srgb);
	ft_lstadd_front(&(scn->plns), ft_lstnew(pln));
	return (0);
}

int 	add_sqr(char **split, t_scn *scn)
{
	char	**spos;
	char	**sdir;
	char 	**srgb;
	t_sqr	*sqr;

	if (!(sqr = malloc(sizeof(t_sqr))))
		handle_error("Malloc failed", 10, scn);
	if (ft_tablen(split) != 5)
		return (1);
	spos = ft_split(split[1], ',');
	if (ft_tablen(spos) != 3)
	{
		ft_abort(spos);
		return (2);
	}
	sqr->origin = tabto_vect(spos);
	ft_abort(spos);
	sdir = ft_split(split[2], ',');
	if (ft_tablen(sdir) != 3)
	{
		ft_abort(sdir);
		return (2);
	}
	sqr->normale = normalize(tabto_vect(sdir));
	ft_abort(sdir);
	sqr->hauteur = ft_atod(split[3]);
	srgb = ft_split(split[4], ',');
	if (ft_tablen(srgb) != 3)
	{
		ft_abort(srgb);
		return (2);
	}
	sqr->color = tabto_rgb(srgb);
	ft_abort(srgb);
	ft_lstadd_front(&(scn->sqrs), ft_lstnew(sqr));
	return (0);
}

int 	add_cyl(char **split, t_scn *scn)
{
	char	**spos;
	char	**sdir;
	char 	**srgb;
	t_cyl	*cyl;

	if (!(cyl = malloc(sizeof(t_cyl))))
		handle_error("Malloc failed", 10, scn);
	if (ft_tablen(split) != 6)
		return (1);
	spos = ft_split(split[1], ',');
	if (ft_tablen(spos) != 3)
	{
		ft_abort(spos);
		return (2);
	}
	cyl->origin = tabto_vect(spos);
	ft_abort(spos);
	sdir = ft_split(split[2], ',');
	if (ft_tablen(sdir) != 3)
	{
		ft_abort(sdir);
		return (2);
	}
	cyl->dir = normalize(tabto_vect(sdir));
	ft_abort(sdir);
	cyl->radius = ft_atod(split[3]) / 2;
	cyl->length = ft_atod(split[4]);
	srgb = ft_split(split[5], ',');
	if (ft_tablen(srgb) != 3)
	{
		ft_abort(srgb);
		return (2);
	}
	cyl->color = tabto_rgb(srgb);
	ft_abort(srgb);
	ft_lstadd_front(&(scn->cyls), ft_lstnew(cyl));
	return (0);
}

int 	add_tri(char **split, t_scn *scn)
{
	int		i;
	char	**spos;
	char 	**srgb;
	t_tri	*tri;

	if (!(tri = malloc(sizeof(t_tri))))
		handle_error("Malloc failed", 10, scn);
	if (ft_tablen(split) != 5)
		return (1);
	i = 0;
	while (i < 3)
	{
		spos = ft_split(split[1 + i], ',');
		if (ft_tablen(spos) != 3)
		{
			ft_abort(spos);
			return (2);
		}
		tri->p[i] = tabto_vect(spos);
		ft_abort(spos);
		i++;
	}
	srgb = ft_split(split[4], ',');
	if (ft_tablen(srgb) != 3)
	{
		ft_abort(srgb);
		return (2);
	}
	tri->color = tabto_rgb(srgb);
	ft_abort(srgb);
	ft_lstadd_front(&(scn->tris), ft_lstnew(tri));
	return (0);
}
