/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisionutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:00:18 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/12 21:11:31 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	in_square(t_vect col, t_sqr car)
{
	double X, Y;
	t_vect right, down, v;

	v = diff(col, car.origin);
	if (car.normale.x == 0 && car.normale.y == 0)
		right = (t_vect){1, 0, 0};
	else
		right = normalize((t_vect){100 * car.normale.y, -100 * car.normale.x, 0});
	down = normalize(prod_vect(car.normale, right));
	X = dot(v, right);
	Y = dot(v, down);
	return (fabs(X) <= car.hauteur / 2 && fabs(Y) <= car.hauteur / 2);
}