/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:31:37 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/16 02:36:34 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_col	get_color(t_vect coli, t_rescl res, t_scene scene)
{
	t_vect	normale;
	t_col	color;
	t_vect	coef;
	int		i;

	if (res.type == 's')
	{
		normale = normalize(diff(coli, scene.sph[res.i].center));
		color = scene.sph[res.i].color;
	}
	if (res.type == 'p')
	{
		normale = normalize(scene.pln[res.i].normale);
		color = scene.pln[res.i].color;
	}
	i = 0;
	coef = mult(scene.ambI, scene.ambCol);
	if (scene.lum)
		while (scene.lum[i].I)
		{
			coef = sum(coef, mult(scene.lum[i].I * normed_dot(normale, diff(scene.lum[i].pos, coli))*10 / pow(norm(diff(scene.lum[i].pos, coli)), 2), scene.lum[i].color));
			i++;
		}
	color = mult_col(50, coef, color);
	return (color);
}

int		find_col(t_ray ray, t_scene scene)
{
	int		i;
	t_col	color;
	t_vect	closest;
	t_rescl	res;

	res = collision_any(ray, scene, &closest);
	if (res.i == -1)
		color = (t_col){50, 50, 50};
	else
	{
		color = get_color(closest, res, scene);
		//if (i == 0 || collision_anysph((t_ray){closest, normalize(diff(scene.lum[0].pos, closest))}, 0) == 0)
		//value = 200*normed_dot(diff(closest, scene.sph[i].center), diff(scene.lum[0].pos, closest));// pow(norm(diff(lum, col)), 2);
	}
	return (create_trgb(0, color.r, color.g, color.b));
}

t_rescl		collision_any(t_ray ray, t_scene scene, t_vect *closest)
{
	int		i;
	t_rescl	res;
	t_vect	col, best;

	res.i = -1;
	res.type = 0;
	if (i = collision_anysph(ray, scene, &col) >= 0)
	{
		best = col;
		res.i = i;
		res.type = 's';
	}
	if (i = collision_anypln(ray, scene, &col) >= 0 &&  norm(diff(ray.origin, col)) < norm(diff(ray.origin, *closest)))
	{
		best = col;
		res.i = i;
		res.type = 'p';
	}
	if (closest)
		*closest = best;
	return (res);
}

int		collision_anypln(t_ray ray, t_scene scene, t_vect *closest)
{
	t_vect	col;
	int		resi;
	int		i;
	
	resi = -1;
	if (scene.pln)
	{
		i = 0;
		while (scene.pln[i].exist)
		{
			if (collision_pln(ray, scene.pln[i], &col))
				if (resi == -1 || norm(diff(col, ray.origin)) < norm(diff(*closest, ray.origin)))
				{
					if (closest)
						*closest = col;
					resi = i;					
				}
			i++;
		}
	}
	return (resi);
}

int		collision_anysph(t_ray ray, t_scene scene, t_vect *closest)
{
	t_vect	col;
	int		resi;
	int		i;
	
	resi = -1;
	if (scene.sph)
	{
		i = 0;
		while (scene.sph[i].radius)
		{
			if (collision_sph(ray, scene.sph[i], &col))
				if (norm(diff(col, ray.origin)) < norm(diff(*closest, ray.origin)) || resi == -1)
				{
					if (closest)
						*closest = col;
					resi = i;					
				}
			i++;
		}
	}
	return (resi);
}

int		collision_pln(t_ray ray, t_pln pln, t_vect *coli)
{
	double	a;
	double	dt;

	a = dot(ray.dir, pln.normale);
	if (a > -EPSILON && a < EPSILON)
		return (0);
	dt = - dot(ray.origin, pln.normale) / a;
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

	a = pow(ray.dir.x, 2) + pow(ray.dir.y, 2) + pow(ray.dir.z, 2);
	b = 2 * (ray.dir.x * (ray.origin.x - sph.center.x) + ray.dir.y * (ray.origin.y - sph.center.y) + ray.dir.z * (ray.origin.z - sph.center.z));
	c = pow(ray.origin.x - sph.center.x, 2) + pow(ray.origin.y - sph.center.y, 2) + pow(ray.origin.z - sph.center.z, 2) - pow(sph.radius, 2);
	delta = pow(b, 2) - 4 * a * c;
	if (delta >= 0)
	{
		res = -(b + sqrt(delta))/(2*a);
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
    t_vect	vertex0 = tri.p1;
    t_vect	vertex1 = tri.p2;  
    t_vect	vertex2 = tri.p3;
    t_vect	edge1, edge2, h, s, q;
    double	a,f,u,v;

    edge1 = diff(vertex1, vertex0);
    edge2 = diff(vertex2, vertex0);
    h = prod_vect(ray.dir, edge2);
    a = dot(edge1, h);
    if (a > -EPSILON && a < EPSILON)
        return (0);    // Le rayon est parallèle au triangle.
    f = 1.0/a;
    s = diff(ray.origin, vertex0);
    u = f * dot(s, h);
    if (u < 0.0 || u > 1.0)
        return (0);
    q = prod_vect(s, edge1);
    v = f * dot(ray.dir, q);
    if (v < 0.0 || u + v > 1.0)
        return (0);

    // On calcule t pour savoir ou le point d'intersection se situe sur la ligne.
    float t = f * dot(edge2, q);
    if (t > EPSILON) // Intersection avec le rayon
    {
        if (coli)
			*coli = sum(ray.origin, mult(t, ray.dir));
        return (1);
    }
    // On a bien une intersection de droite, mais pas de rayon.
    return (0);
}
