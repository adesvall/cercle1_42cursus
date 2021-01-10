/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisionany.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 23:27:39 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/04 13:08:28 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_rescl		collision_any(t_ray ray, t_scn scn, t_vect *closest, double dmax)
{
	int		i;
	t_rescl	res;
	t_vect	col, best;

	res.i = -1;
	res.type = 0;
	if ((i = collision_anysph(ray, scn, &col)) >= 0)
	{
		best = col;
		res.i = i;
		res.type = 's';
	}
	if ((i = collision_anypln(ray, scn, &col)) >= 0 && (res.i == -1 || norm(diff(ray.origin, col)) < norm(diff(ray.origin, best))))
	{
		best = col;
		res.i = i;
		res.type = 'p';
	}
	if ((i = collision_anytri(ray, scn, &col)) >= 0 && (res.i == -1 || norm(diff(ray.origin, col)) < norm(diff(ray.origin, best))))
	{
		best = col;
		res.i = i;
		res.type = 't';
	}
	if ((i = collision_anycyl(ray, scn, &col)) >= 0 && (res.i == -1 || norm(diff(ray.origin, col)) < norm(diff(ray.origin, best))))
	{
		best = col;
		res.i = i;
		res.type = 'c';
	}
	if ((i = collision_anycar(ray, scn, &col)) >= 0 && (res.i == -1 || norm(diff(ray.origin, col)) < norm(diff(ray.origin, best))))
	{
		best = col;
		res.i = i;
		res.type = 'q';
	}
	if (res.i == -1 || (dmax != -1 && norm(diff(best, ray.origin)) > dmax))
		return ((t_rescl){0, -1});
	if (res.i >= 0 && closest)
		*closest = best;
	return (res);
}

int		collision_anycyl(t_ray ray, t_scn scn, t_vect *closest)
{
	t_vect	col, best;
	int		resi;
	int		i;
	
	resi = -1;
	if (scn.cyl)
	{
		i = 0;
		while (scn.cyl[i].radius)
		{
			if (collision_cyl(ray, scn.cyl[i], &col))
				if (resi == -1 || norm(diff(col, ray.origin)) < norm(diff(best, ray.origin)))
				{
					best = col;
					resi = i;					
				}
			i++;
		}
		if (resi >= 0 && closest)
			*closest = best;
	}
	return (resi);
}

int		collision_anytri(t_ray ray, t_scn scn, t_vect *closest)
{
	t_vect	col, best;
	int		resi;
	int		i;
	
	resi = -1;
	if (scn.tri)
	{
		i = 0;
		while (scn.tri[i].exist)
		{
			if (collision_tri(ray, scn.tri[i], &col))
				if (resi == -1 || norm(diff(col, ray.origin)) < norm(diff(best, ray.origin)))
				{
					best = col;
					resi = i;					
				}
			i++;
		}
		if (resi >= 0 && closest)
			*closest = best;
	}
	return (resi);
}

int		collision_anypln(t_ray ray, t_scn scn, t_vect *closest)
{
	t_vect	col, best;
	int		resi;
	int		i;
	
	resi = -1;
	if (scn.pln)
	{
		i = 0;
		while (scn.pln[i].exist)
		{
			if (collision_pln(ray, scn.pln[i], &col))
				if (resi == -1 || norm(diff(col, ray.origin)) < norm(diff(best, ray.origin)))
				{
					best = col;
					resi = i;					
				}
			i++;
		}
		if (resi >= 0 && closest)
			*closest = best;
	}
	return (resi);
}

int		collision_anysph(t_ray ray, t_scn scn, t_vect *closest)
{
	t_vect	col, best;
	int		resi;
	int		i;
	
	resi = -1;
	best = (t_vect){0, 0, 0};
	if (scn.sph)
	{
		i = 0;
		while (scn.sph[i].exist)
		{
			if (collision_sph(ray, scn.sph[i], &col))
			{
				if (resi == -1 || (norm(diff(col, ray.origin)) < norm(diff(best, ray.origin))))
				{
					best = col;
					resi = i;
				}
			}
			i++;
		}
		if (resi >= 0 && closest)
			*closest = best;
	}
	return (resi);
}

int		collision_anycar(t_ray ray, t_scn scn, t_vect *closest)
{
	t_vect	col, best;
	int		resi;
	int		i;
	
	resi = -1;
	best = (t_vect){0, 0, 0};
	if (scn.car)
	{
		i = 0;
		while (scn.car[i].hauteur)
		{
			if (collision_car(ray, scn.car[i], &col))
			{
				if (resi == -1 || (norm(diff(col, ray.origin)) < norm(diff(best, ray.origin))))
				{
					best = col;
					resi = i;
				}
			}
			i++;
		}
		if (resi >= 0 && closest)
			*closest = best;
	}
	return (resi);
}