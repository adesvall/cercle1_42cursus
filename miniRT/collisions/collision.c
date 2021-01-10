/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:31:37 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/10 16:20:23 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_col	get_color(t_vect coli, t_rescl res, t_scn scn, t_ray ray, int rfi)
{
	t_vect	normale;
	t_col	color;
	t_vect	coef;
	double	c;
	double	reflect;
	t_col	reflectcol;
	int		i;

	normale = (t_vect){-1, 0, 0};
	if (res.type == 's')
	{
		normale = normalize(diff(coli, scn.sph[res.i].center));
		color = scn.sph[res.i].color;
		reflect = scn.sph[res.i].reflect;
	}
	if (res.type == 'p')
	{
		normale = normalize(scn.pln[res.i].normale);
		color = scn.pln[res.i].color;
		reflect = scn.pln[res.i].reflect;
	}
	if (res.type == 't')
	{
		normale = normalize(prod_vect(diff(scn.tri[res.i].p2, scn.tri[res.i].p1), diff(scn.tri[res.i].p3, scn.tri[res.i].p1)));
		color = scn.tri[res.i].color;
		reflect = scn.tri[res.i].reflect;
	}
	if (res.type == 'c')
	{
		normale = normalize(diff(coli, sum(scn.cyl[res.i].origin, mult(dot(scn.cyl[res.i].dir, diff(coli, scn.cyl[res.i].origin)), scn.cyl[res.i].dir))));
		color = scn.cyl[res.i].color;
		reflect = scn.cyl[res.i].reflect;
	}
	if (res.type == 'q')
	{
		normale = normalize(scn.car[res.i].normale);
		color = scn.car[res.i].color;
		reflect = scn.car[res.i].reflect;
	}
	else
		reflect = 0;
	i = 0;
	coef = mult(scn.ambI/255, scn.ambCol);
	if (dot(normale, ray.dir) > 0)
		normale = mult(-1, normale);
	if (scn.lum)
	{
		while (scn.lum[i].I >= EPSILON)
		{
			if (collision_any((t_ray){coli, normalize(diff(scn.lum[i].pos, coli))}, scn, 0, norm(diff(scn.lum[i].pos, coli))).i == -1)
			{
				c = scn.lum[i].I/255 * normed_dot(normale, diff(scn.lum[i].pos, coli)) * 100000 / pow(norm(diff(scn.lum[i].pos, coli)), 2);
				c = (c > 0) ? c : 0;
				coef = sum(coef, mult(c, scn.lum[i].color));
			}
			i++;
		}
	}
	color = mult_col(5, coef, color);
	if (reflect > EPSILON && rfi > 0)
	{
		ray = (t_ray){coli, normalize(sum(ray.dir, mult(-2 * dot(ray.dir, normale), normale)))};
		res = collision_any(ray, scn, &coli, -1);
		if (res.i != -1)
		{
			reflectcol = get_color(coli, res, scn, ray, rfi - 1);
			color = mixcolor(reflect, color, reflectcol);
		}
	}
	return (color);
}

void		find_col(t_targs *args)
{
	t_col	color;
	t_vect	closest;
	t_rescl	res;
	t_ray	ray;
	int j;
	int i;

	i=0;
	while (i + args->i < args->scn.resH && i < args->scn.resH/4)
	{
		j=0;
		while (j < args->scn.resW)
		{
			ray.dir = normalize(sum(args->cam.dir, sum(mult(tan(args->cam.fov * M_PI / 360) * (j - args->scn.resW / 2)/args->scn.resW, args->cam.right), mult(tan(args->cam.fov * M_PI / 360) * (i + args->i  - args->scn.resH / 2)/args->scn.resW, args->cam.down))));
			ray.origin = args->cam.origin;
			res = collision_any(ray, args->scn, &closest, -1);
			if (res.i == -1)
				color = (t_col){30, 30, 30};
			else
				color = get_color(closest, res, args->scn, ray, args->rfi);
			my_mlx_pixel_put(&args->cam.data, j, i + args->i , create_trgb(0, color.r, color.g, color.b));
			j++;
		}
		i++;
	}
	pthread_exit(NULL);
}

int		collision_pln(t_ray ray, t_pln pln, t_vect *coli)
{
	double	a;
	double	dt;

	a = dot(ray.dir, pln.normale);
	if (a > -EPSILON && a < EPSILON)
		return (0);
	dt = - dot(diff(ray.origin, pln.origin), pln.normale) / a;
	if (dt > EPSILON)
	{
		if (coli)
			*coli = sum(ray.origin, mult(dt, ray.dir));
		return (1);
	}
	return (0);
}

int		collision_sph(t_ray ray, t_sph sph, t_vect *coli)
{
	double	a, b, c, delta, res;

	a = dot(ray.dir, ray.dir);
	b = 2 * dot(ray.dir, diff(ray.origin, sph.center));
	c = pow(ray.origin.x - sph.center.x, 2) + pow(ray.origin.y - sph.center.y, 2) + pow(ray.origin.z - sph.center.z, 2) - pow(sph.radius, 2);
	delta = pow(b, 2) - 4 * a * c;
	if (delta > EPSILON)
	{
		res = -(b + sqrt(delta))/(2*a);
		if (res <= EPSILON)
			res += sqrt(delta)/a;
		if (res > EPSILON)
		{
			if (coli)
				*coli = sum(ray.origin, mult(res, ray.dir));
			return (1);
		}
	}
	return (0);
}

int		collision_tri(t_ray ray, t_tri tri, t_vect *coli)
{
    t_vect	edge1, edge2, h, s, q;
    double	a,u,v,t;

    edge1 = diff(tri.p2, tri.p1);
    edge2 = diff(tri.p3, tri.p1);
    h = prod_vect(ray.dir, edge2);
    a = dot(edge1, h);
    if (a > -EPSILON && a < EPSILON)
        return (0);
    s = diff(ray.origin, tri.p1);
    u = 1.0 / a * dot(s, h);
    if (u < 0.0 || u > 1.0)
        return (0);
    q = prod_vect(s, edge1);
    v = 1.0 / a * dot(ray.dir, q);
    if (v < 0 || u + v > 1.0)
        return (0);
    t = 1.0 / a * dot(edge2, q);
    if (t > EPSILON)
    {
        if (coli)
			*coli = sum(ray.origin, mult(t, ray.dir));
        return (1);
    }
    return (0);
}

int		collision_cyl(t_ray ray, t_cyl cyl, t_vect *coli)
{
	t_vect	u, v, col;
	double	a, b, c, delta, res;

	u = diff(ray.dir, mult(dot(cyl.dir, ray.dir), cyl.dir));
	v = diff(diff(ray.origin, cyl.origin), mult(dot(cyl.dir, diff(ray.origin, cyl.origin)), cyl.dir));
	a = dot(u, u);
	b = 2 * dot(u, v);
	c = dot(v, v) - pow(cyl.radius, 2);
	delta = pow(b, 2) - 4 * a * c;
	if (delta > EPSILON)
	{
		res = -(b + sqrt(delta))/(2*a);
		if (res <= EPSILON || fabs(dot(cyl.dir, diff(sum(ray.origin, mult(res, ray.dir)), cyl.origin))) > cyl.length / 2)
			res += sqrt(delta)/a;
		if (res > EPSILON && fabs(dot(cyl.dir, diff(col = sum(ray.origin, mult(res, ray.dir)), cyl.origin))) < cyl.length / 2)
		{
			if (coli)
				*coli = col;
			return (1);
		}
	}
	return (0);
}

int		collision_car(t_ray ray, t_car car, t_vect *coli)
{
	t_vect	col;
	double	a;
	double	dt;

	a = dot(ray.dir, car.normale);
	if (a > -EPSILON && a < EPSILON)
		return (0);
	dt = - dot(diff(ray.origin, car.origin), car.normale) / a;
	if (dt > EPSILON)
	{
		col = sum(ray.origin, mult(dt, ray.dir));
		if (in_square(col, car))
		{
			if (coli)
				*coli = col;
			return (1);
		}
	}
	return (0);
}
