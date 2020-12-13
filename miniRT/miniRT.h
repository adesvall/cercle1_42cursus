/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 20:40:00 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/13 23:24:25 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <math.h>
# include <fcntl.h>

typedef struct  s_data {
    void	*img;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
	double	resx;
	double	resy;
}               t_data;

typedef struct	s_vect
{
	double	x;
	double	y;
	double	z;
}				t_vect;

typedef struct	s_ray
{
	t_vect	origin;
	t_vect	dir;
}				t_ray;

typedef struct	s_sph
{
	t_vect	center;
	double	radius;
}				t_sph;

void			create_img(t_data img);
t_vect			newvect(double x, double y, double z);
t_vect			sum(t_vect v1, t_vect v2);
t_vect			diff(t_vect v1, t_vect v2);
t_vect			mult(double n, t_vect v);
t_vect			div(double n, t_vect v);
double			dot(t_vect v1, t_vect v2);
double			norm(t_vect v);

t_vect			collision_sph(t_ray ray, t_sph sphere);

#endif