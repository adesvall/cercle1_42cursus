/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 02:40:13 by adesvall          #+#    #+#             */
/*   Updated: 2020/11/30 17:53:16 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

typedef struct	s_save
{
	int				fd;
	char			*ligne;
	struct s_save	*next;
}				t_save;

int				is_endofline(char *buf);
int				get_next_line(int fd, char **line);
void			*ft_memmove(void *dest, const void *src, size_t n);
char			*join_and_realloc(char *s1, char *s2);
int				ft_strlen(const char *s);
int				ft_clean(t_save **lstbegin, int fd);

#endif
