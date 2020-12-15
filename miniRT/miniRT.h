/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 20:40:00 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/15 03:44:12 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <math.h>
# include <fcntl.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846264338327950288419716939937510582
# endif


typedef struct  s_data
{
    void	*img;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
}               t_data;

typedef struct	s_vect
{
	double	x;
	double	y;
	double	z;
}				t_vect;

typedef	struct	s_col
{
	int	r;
	int	g;
	int b;
}				t_col;

typedef struct	s_ray
{
	t_vect	origin;
	t_vect	dir;
}				t_ray;

typedef struct	s_lum
{
	t_vect	pos;
	double	I;
	t_col	col;
}				t_lum;

typedef	struct	s_pln
{
	t_vect	origin;
	t_vect	normale;
	t_col	col;
}				t_pln;

typedef struct	s_sqr
{
	t_vect	origin;
	t_vect	normale;
	double	hauteur;
	t_col	col;
}				t_sqr;

typedef struct	s_cyl
{
	t_vect	origin;
	t_vect	dir;
	double	rayon;
	double	length;
}				t_cyl;

typedef struct	s_tri
{
	t_vect	p1;
	t_vect	p2;
	t_vect	p3;
	t_col	col;
}				t_tri;

typedef struct	s_sph
{
	t_vect	center;
	double	radius;
	t_col	color;
}				t_sph;

typedef struct	s_cam
{
	t_vect	origin;
	t_vect	dir;
	double 	fov;
}				t_cam;

typedef struct	s_scene
{
	char	*line;
	char	**split;
	int		resW;
	int		resH;
	double 	ambI;
	t_col	ambCol;
	t_cam	*cam;
	t_lum	*lum;
	t_sph	*sph;
	t_pln	*pln;
	t_sqr	*sqr;
	t_cyl	*cyl;
	t_tri	*tri;
}				t_scene;

void			create_img(t_data img, t_scene scene);
t_vect			newvect(double x, double y, double z);
t_vect			sum(t_vect v1, t_vect v2);
t_vect			diff(t_vect v1, t_vect v2);
t_vect			mult(double n, t_vect v);
t_vect			div(double n, t_vect v);
double			dot(t_vect v1, t_vect v2);
double			norm(t_vect v);
t_vect			prod_vect(t_vect v1, t_vect v2);
t_vect			normalize(t_vect v);
t_vect			turn_vect(t_vect dir0, double angw, double angh);



t_vect			collision_sph(t_ray ray, t_sph sphere);

#endif