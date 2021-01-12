/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 20:40:00 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/12 21:33:45 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libftutils.h"
# include "elems.h"
# include "../get_next_line/get_next_line.h"
# include "parse.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

# ifndef M_PI
#  define M_PI 3.1415926535897932384626
# endif
# define EPSILON 0.0000001

/*
typedef union	u_elmt
{
	t_sph	*sph;
	t_pln	*pln;
	t_sqr	*sqr;
	t_cyl	*cyl;
	t_tri	*tri;
}				t_elmt;
*/

void			init_scn(t_scn *scn);
void			parse_file(char *rt_file, t_scn *scn);
t_vect			tabto_vect(char **s);
t_vect			tabto_lumrgb(char **s);
t_rgb			tabto_rgb(char **s);

int				exit_and_free(t_scn *scn);
int				handle_error(char *msg, int err, t_scn *scn);
int				get_keypress(int key, t_scn *scn);

int				create_trgb(int t, int r, int g, int b);
void			create_img(t_cam cam, t_scn *scn);

void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			save_bmp(const char *filename, const unsigned char *data, t_scn *scn);

double			limit_color(double n);
t_rgb			mult_col(double n, t_vect coef, t_rgb color);
t_rgb			mixcolor(double reflect, t_rgb color, t_rgb reflectcol);
int				egal_vect(t_vect v1, t_vect v2);
t_vect			sum(t_vect v1, t_vect v2);
t_vect			diff(t_vect v1, t_vect v2);
t_vect			mult(double n, t_vect v);
t_vect			divn(double n, t_vect v);
double			dot(t_vect v1, t_vect v2);
double			norm(t_vect v);
double			normed_dot(t_vect v1, t_vect v2);
t_vect			prod_vect(t_vect v1, t_vect v2);
t_vect			normalize(t_vect v);
t_vect			turn_vect(t_vect dir0, double angw, double angh);


void			find_col(t_targs *args);
t_rescl			collision_any(t_ray ray, t_scn *scn, t_vect *closest, double max);
int				collision_sph(t_ray ray, void *elem, t_vect *coli);
int				collision_pln(t_ray ray, void *elem, t_vect *coli);
int				collision_tri(t_ray ray, void *elem, t_vect *coli);
int				collision_cyl(t_ray ray, void *elem, t_vect *coli);
int				collision_sqr(t_ray ray, void *elem, t_vect *coli);
int				in_square(t_vect coli, t_sqr car);


#endif