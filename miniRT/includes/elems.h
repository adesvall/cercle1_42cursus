/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elems.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:48:36 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/14 16:48:36 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ELEMS_H
# define ELEMS_H

# include "basics.h"

typedef struct	s_lum
{
	t_vect	pos;
	double	I;
	t_vect	color;
}				t_lum;

typedef	struct	s_pln
{
	t_vect	origin;
	t_vect	normale;
	t_rgb	color;
}				t_pln;

typedef struct	s_sqr
{
	t_vect	origin;
	t_vect	normale;
	double	hauteur;
	t_rgb	color;
}				t_sqr;

typedef struct	s_cyl
{
	t_vect	origin;
	t_vect	dir;
	double	radius;
	double	length;
	t_rgb	color;
}				t_cyl;

typedef struct	s_tri
{
	t_vect	origin;
	t_vect	p[2];
	t_rgb	color;
}				t_tri;

typedef struct	s_sph
{
	t_vect	center;
	double	radius;
	t_rgb	color;
}				t_sph;

typedef struct	s_cam
{
	t_data	data;
	t_vect	origin;
	t_vect	dir;
	t_vect	right;
	t_vect	down;
	double 	fov;
}				t_cam;

typedef struct	s_sel
{
	t_vect	*pos;
	t_vect	*dir;
}				t_sel;


typedef struct	s_scn
{
	void    	*mlx;
    void    	*mlx_win;
	char		*filename;
	t_couple	res;
	double 		ambI;
	t_vect		ambCol;
	int			ncam;
	t_list		*actualcam;
	t_list		*actuallum;
	t_sel		sl_obj;
	t_list		*cams;
	t_list		*lums;
	t_list		*sphs;
	t_list		*plns;
	t_list		*sqrs;
	t_list		*cyls;
	t_list		*tris;
}				t_scn;

typedef struct	s_targs
{
	int 	i;
	t_cam	*cam;
	t_scn	*scn;
}				t_targs;

#endif