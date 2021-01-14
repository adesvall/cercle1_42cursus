/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:36:56 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/14 02:12:08 by adesvall         ###   ########.fr       */
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
		return (WRONG_LINE);
	scn->ambI = ft_atod(split[1]);
	if (scn->ambI < 0 || scn->ambI > 1)
		return (WRONG_ARG);
	splitcol = ft_split(split[2], ",");
	if (ft_tablen(splitcol) != 3)
	{
		ft_abort(splitcol);
		return (WRONG_ARG);
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

	if (ft_tablen(split) != 4)
		return (WRONG_LINE);
	if (!(cam = malloc(sizeof(t_cam))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	spos = ft_split(split[1], ",");
	if (ft_tablen(spos) != 3)
	{
		ft_abort(spos);
		free(cam);
		return (WRONG_ARG);
	}
	cam->origin = tabto_vect(spos);
	ft_abort(spos);
	sdir = ft_split(split[2], ",");
	if (ft_tablen(sdir) != 3)
	{
		ft_abort(sdir);
		free(cam);
		return (WRONG_ARG);
	}
	cam->dir = tabto_vect(sdir);
	ft_abort(sdir);
	if (norm(cam->dir) < EPSILON)
	{
		free(cam);
		return (WRONG_ARG);
	}
	cam->fov = ft_atod(split[3]);
	ft_lstadd_front(&(scn->cams), ft_lstnew(cam));
	return (0);
}

int 	add_lum(char **split, t_scn *scn)
{
	char	**spos;
	char 	**srgb;
	t_lum	*lum;

	if (ft_tablen(split) != 4)
		return (WRONG_LINE);
	if (!(lum = malloc(sizeof(t_lum))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	spos = ft_split(split[1], ",");
	if (ft_tablen(spos) != 3)
	{
		ft_abort(spos);
		free(lum);
		return (WRONG_ARG);
	}
	lum->pos = tabto_vect(spos);
	ft_abort(spos);
	lum->I = ft_atod(split[2]);
	srgb = ft_split(split[3], ",");
	if (ft_tablen(srgb) != 3)
	{
		free(lum);
		ft_abort(srgb);
		return (WRONG_ARG);
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

	if (ft_tablen(split) != 4)
		return (WRONG_LINE);
	if (!(sph = malloc(sizeof(t_sph))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	spos = ft_split(split[1], ",");
	sph->radius = ft_atod(split[2]) / 2;
	srgb = ft_split(split[3], ",");
	if (ft_tablen(spos) != 3 || ft_tablen(srgb) != 3)
	{
		ft_abort(spos);
		ft_abort(srgb);
		free(sph);
		return (WRONG_ARG);
	}
	sph->center = tabto_vect(spos);
	sph->color = tabto_rgb(srgb);
	ft_abort(spos);
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

	if (ft_tablen(split) != 4)
		return (WRONG_LINE);
	if (!(pln = malloc(sizeof(t_pln))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	spos = ft_split(split[1], ",");
	if (ft_tablen(spos) != 3)
	{
		free(pln);
		ft_abort(spos);
		return (WRONG_ARG);
	}
	pln->origin = tabto_vect(spos);
	ft_abort(spos);
	sdir = ft_split(split[2], ",");
	if (ft_tablen(sdir) != 3)
	{
		ft_abort(sdir);
		free(pln);
		return (WRONG_ARG);
	}
	pln->normale = normalize(tabto_vect(sdir));
	ft_abort(sdir);
	srgb = ft_split(split[3], ",");
	if (ft_tablen(srgb) != 3)
	{
		ft_abort(srgb);
		free(pln);
		return (WRONG_ARG);
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

	if (ft_tablen(split) != 5)
		return (WRONG_LINE);
	if (!(sqr = malloc(sizeof(t_sqr))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	spos = ft_split(split[1], ",");
	if (ft_tablen(spos) != 3)
	{
		ft_abort(spos);
		free(sqr);
		return (WRONG_ARG);
	}
	sqr->origin = tabto_vect(spos);
	ft_abort(spos);
	sdir = ft_split(split[2], ",");
	if (ft_tablen(sdir) != 3)
	{
		ft_abort(sdir);
		free(sqr);
		return (WRONG_ARG);
	}
	sqr->normale = normalize(tabto_vect(sdir));
	ft_abort(sdir);
	sqr->hauteur = ft_atod(split[3]);
	srgb = ft_split(split[4], ",");
	if (ft_tablen(srgb) != 3)
	{
		ft_abort(srgb);
		free(sqr);
		return (WRONG_ARG);
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

	if (ft_tablen(split) != 6)
		return (WRONG_LINE);
	if (!(cyl = malloc(sizeof(t_cyl))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	spos = ft_split(split[1], ",");
	if (ft_tablen(spos) != 3)
	{
		ft_abort(spos);
		free(cyl);
		return (WRONG_ARG);
	}
	cyl->origin = tabto_vect(spos);
	ft_abort(spos);
	sdir = ft_split(split[2], ",");
	if (ft_tablen(sdir) != 3)
	{
		ft_abort(sdir);
		free(cyl);
		return (WRONG_ARG);
	}
	cyl->dir = normalize(tabto_vect(sdir));
	ft_abort(sdir);
	cyl->radius = ft_atod(split[3]) / 2;
	cyl->length = ft_atod(split[4]);
	srgb = ft_split(split[5], ",");
	if (ft_tablen(srgb) != 3)
	{
		ft_abort(srgb);
		free(cyl);
		return (WRONG_ARG);
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

	if (ft_tablen(split) != 5)
		return (WRONG_LINE);
	if (!(tri = malloc(sizeof(t_tri))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	spos = ft_split(split[1], ",");
	if (ft_tablen(spos) != 3)
	{
		ft_abort(spos);
		free(tri);
		return (WRONG_ARG);
	}
	tri->origin = tabto_vect(spos);
	ft_abort(spos);
	i = 0;
	while (i < 2)
	{
		spos = ft_split(split[2 + i], ",");
		if (ft_tablen(spos) != 3)
		{
			ft_abort(spos);
			free(tri);
			return (WRONG_ARG);
		}
		tri->p[i] = diff(tabto_vect(spos), tri->origin);
		ft_abort(spos);
		i++;
	}
	srgb = ft_split(split[4], ",");
	if (ft_tablen(srgb) != 3)
	{
		ft_abort(srgb);
		free(tri);
		return (WRONG_ARG);
	}
	tri->color = tabto_rgb(srgb);
	ft_abort(srgb);
	ft_lstadd_front(&(scn->tris), ft_lstnew(tri));
	return (0);
}
