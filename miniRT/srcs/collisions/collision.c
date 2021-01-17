/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:31:37 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/15 19:08:34 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_rgb	get_color(t_scn *scn, t_ray ray, int rfi)
{
	t_vect	coli;
	t_rgb	color;
	t_vect	coef;
	double	c;
	t_rescl	res;
	t_list	*ite;
	t_lum	*lum;

	res = collision_any(ray, scn, &coli, -1);
	if (res.elem == NULL)
		return ((t_rgb){0, 0, 0});
	color = res.color;
	coef = mult(scn->ambI/255, scn->ambCol);
	ite = scn->lums;
	while (ite)
	{
		lum = (t_lum*)ite->content;
		if (collision_any((t_ray){coli, normalize(diff(lum->pos, coli))}, scn, 0, norm(diff(lum->pos, coli))).elem == NULL)
		{
			c = lum->I/255 * normed_dot(res.normale, diff(lum->pos, coli)) * 1000 / pow(norm(diff(lum->pos, coli)), 2);
			c = (c > 0) ? c : 0;
			coef = sum(coef, mult(c, lum->color));
		}
		ite = ite->next;
	}
	color = mult_col(5, coef, color);
	if (REFLECT > EPSILON && rfi > 0)
	{
		ray = (t_ray){coli, normalize(sum(ray.dir, mult(-2 * dot(ray.dir, res.normale), res.normale)))};
		color = mixcolor(REFLECT, color, get_color(scn, ray, rfi - 1));
	}
	return (color);
}

void		fill_img(t_targs *args)
{
	t_rgb	color;
	t_ray	ray;
	int j;
	int i;

	i=0;
	while (i + args->i < args->scn->res.H && i < args->scn->res.H/4)
	{
		j=0;
		while (j < args->scn->res.W)
		{
			ray = find_ray(args->cam, i + args->i, j, args->scn);
			color = get_color(args->scn, ray, R_DEPTH);
			my_mlx_pixel_put(&args->cam->data, j, i + args->i , create_trgb(0, color.r, color.g, color.b));
			j++;
		}
		i++;
	}
	pthread_exit(NULL);
}

int		collision_pln(t_ray ray, void *elem, t_vect *coli)
{
	double	a;
	double	dt;
	t_pln	*pln;

	pln = (t_pln*)elem;
	a = dot(ray.dir, pln->normale);
	if (a > -EPSILON && a < EPSILON)
		return (0);
	dt = - dot(diff(ray.origin, pln->origin), pln->normale) / a;
	if (dt > EPSILON)
	{
		if (coli)
			*coli = sum(ray.origin, mult(dt, ray.dir));
		return (1);
	}
	return (0);
}

int		collision_sph(t_ray ray, void *elem, t_vect *coli)
{
	double	a, b, c, delta, res;
	t_sph	*sph;

	sph = (t_sph*)elem;
	a = dot(ray.dir, ray.dir);
	b = 2 * dot(ray.dir, diff(ray.origin, sph->center));
	c = pow(ray.origin.x - sph->center.x, 2) + pow(ray.origin.y - sph->center.y, 2) + pow(ray.origin.z - sph->center.z, 2) - pow(sph->radius, 2);
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

int		collision_tri(t_ray ray, void *elem, t_vect *coli)
{
    t_vect	h, s, q;
    double	a,u,v,t;
	t_tri	*tri;

	tri = (t_tri*)elem;
    h = prod_vect(ray.dir, tri->p[1]);
    a = dot(tri->p[0], h);
    if (a > -EPSILON && a < EPSILON)
        return (0);
    s = diff(ray.origin, tri->origin);
    u = 1.0 / a * dot(s, h);
    if (u < 0.0 || u > 1.0)
        return (0);
    q = prod_vect(s, tri->p[0]);
    v = 1.0 / a * dot(ray.dir, q);
    if (v < 0 || u + v > 1.0)
        return (0);
    t = 1.0 / a * dot(tri->p[1], q);
    if (t > EPSILON)
    {
        if (coli)
			*coli = sum(ray.origin, mult(t, ray.dir));
        return (1);
    }
    return (0);
}

int		collision_cyl(t_ray ray, void *elem, t_vect *coli)
{
	t_vect	u, v, col;
	t_abc	res;
	t_cyl	*cyl;

	cyl = (t_cyl*)elem;
	u = diff(ray.dir, mult(dot(cyl->dir, ray.dir), cyl->dir));
	v = diff(diff(ray.origin, cyl->origin), mult(dot(cyl->dir, diff(ray.origin, cyl->origin)), cyl->dir));
	if ((res = abc_solve(dot(u, u), 2 * dot(u, v), dot(v, v) - pow(cyl->radius, 2))).delta > EPSILON)
	{
		if (res.x1 <= EPSILON || fabs(dot(cyl->dir, diff(sum(ray.origin, mult(res.x1, ray.dir)), cyl->origin))) > cyl->length / 2)
			res.x1 += res.x2_x1;
		if (res.x1 > EPSILON && fabs(dot(cyl->dir, diff(col = sum(ray.origin, mult(res.x1, ray.dir)), cyl->origin))) < cyl->length / 2)
		{
			if (coli)
				*coli = col;
			return (1);
		}
	}
	return (0);
}

int		collision_dsk(t_ray ray, void *elem, t_vect *coli)
{
	t_vect	col;
	double	a;
	double	dt;
	t_dsk	*dsk;

	dsk = (t_dsk*)elem;
	a = dot(ray.dir, dsk->normale);
	if (a > -EPSILON && a < EPSILON)
		return (0);
	dt = - dot(diff(ray.origin, dsk->origin), dsk->normale) / a;
	if (dt > EPSILON)
	{
		col = sum(ray.origin, mult(dt, ray.dir));
		if (norm(diff(col, dsk->origin)) < dsk->radius)
		{
			if (coli)
				*coli = col;
			return (1);
		}
	}
	return (0);
}

int		collision_sqr(t_ray ray, void *elem, t_vect *coli)
{
	t_vect	col;
	double	a;
	double	dt;
	t_sqr	*sqr;

	sqr = (t_sqr*)elem;
	a = dot(ray.dir, sqr->normale);
	if (a > -EPSILON && a < EPSILON)
		return (0);
	dt = - dot(diff(ray.origin, sqr->origin), sqr->normale) / a;
	if (dt > EPSILON)
	{
		col = sum(ray.origin, mult(dt, ray.dir));
		if (in_square(col, *sqr))
		{
			if (coli)
				*coli = col;
			return (1);
		}
	}
	return (0);
}