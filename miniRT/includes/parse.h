/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 21:15:50 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/12 21:19:27 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "elems.h"

int		set_res(char **split, t_scn *scn);
int		set_ambLum(char **split, t_scn *scn);
int 	add_cam(char **split, t_scn *scn);
int 	add_lum(char **split, t_scn *scn);
int 	add_sph(char **split, t_scn *scn);
int 	add_pln(char **split, t_scn *scn);
int 	add_sqr(char **split, t_scn *scn);
int 	add_cyl(char **split, t_scn *scn);
int 	add_tri(char **split, t_scn *scn);

#endif