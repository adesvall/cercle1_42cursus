/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisionany.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 23:27:39 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/12 21:34:50 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"


void	*collision_list_elem(t_ray ray, t_list *elem, t_vect *closest, int (*collision) (t_ray ray, void *elem, t_vect *coli))
{
	t_vect	col, best;
	t_cam	*res;
	t_list	*ite;
	
	res = NULL;
	best = (t_vect){0, 0, 0};
	ite = elem;
	while(ite)
	{
		if (collision(ray, ite->content, &col))
		{
			if (res == NULL || (norm(diff(col, ray.origin)) < norm(diff(best, ray.origin))))
			{
				best = col;
				res = ite->content;
			}
		}
		ite = ite->next;
	}
	if (res != 0 && closest)
		*closest = best;
	return (res);
}

t_rescl		collision_any(t_ray ray, t_scn *scn, t_vect *closest, double dmax)
{
	void	*elem;
	t_rescl	res;
	t_vect	col, best;

	res.elem = NULL;
	res.type = 0;
	res.normale = (t_vect){-1, 0, 0};
	res.reflect = 0;
	if ((elem = collision_list_elem(ray, scn->sphs, &col, &collision_sph)) != NULL)
	{
		best = col;
		res.elem = elem;
		res.type = 's';
		res.normale = normalize(diff(col, ((t_sph*)elem)->center));
		res.color = ((t_sph*)elem)->color;
		res.reflect = ((t_sph*)elem)->reflect;
	}
	if ((elem = collision_list_elem(ray, scn->plns, &col, &collision_pln)) != NULL && (res.elem == NULL || norm(diff(ray.origin, col)) < norm(diff(ray.origin, best))))
	{
		best = col;
		res.elem = elem;
		res.type = 'p';
		res.normale = ((t_pln*)elem)->normale;
		res.color = ((t_pln*)elem)->color;
		res.reflect = ((t_pln*)elem)->reflect;
	}
	if ((elem = collision_list_elem(ray, scn->tris, &col, &collision_tri)) != NULL && (res.elem == NULL || norm(diff(ray.origin, col)) < norm(diff(ray.origin, best))))
	{
		best = col;
		res.elem = elem;
		res.type = 't';
		res.normale = normalize(prod_vect(diff(((t_tri*)elem)->p[1], ((t_tri*)elem)->p[0]), diff(((t_tri*)elem)->p[2], ((t_tri*)elem)->p[0])));
		res.color = ((t_tri*)elem)->color;
		res.reflect = ((t_tri*)elem)->reflect;
	}
	if ((elem = collision_list_elem(ray, scn->cyls, &col, &collision_cyl)) != NULL && (res.elem == NULL || norm(diff(ray.origin, col)) < norm(diff(ray.origin, best))))
	{
		best = col;
		res.elem = elem;
		res.type = 'c';
		res.normale = normalize(diff(col, sum(((t_cyl*)elem)->origin, mult(dot(((t_cyl*)elem)->dir, diff(col, ((t_cyl*)elem)->origin)), ((t_cyl*)elem)->dir))));
		res.color = ((t_cyl*)elem)->color;
		res.reflect = ((t_cyl*)elem)->reflect;
	}
	if ((elem = collision_list_elem(ray, scn->sqrs, &col, &collision_sqr)) != NULL && (res.elem == NULL || norm(diff(ray.origin, col)) < norm(diff(ray.origin, best))))
	{
		best = col;
		res.elem = elem;
		res.type = 'q';
		res.normale = ((t_sqr*)elem)->normale;
		res.color = ((t_sqr*)elem)->color;
		res.reflect = ((t_sqr*)elem)->reflect;
	}
	if (dmax != -1 && norm(diff(best, ray.origin)) > dmax)
		res.elem = NULL;
	if (res.elem != NULL && closest)
		*closest = best;
	if (dot(res.normale, ray.dir) > 0)
		res.normale = mult(-1, res.normale);
	return (res);
}
