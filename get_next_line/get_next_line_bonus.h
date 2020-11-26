/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 02:40:13 by adesvall          #+#    #+#             */
/*   Updated: 2020/11/26 22:43:20 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

typedef struct  ssavefd
{
    int     		fd;
    char    		*ligne;
    struct ssavefd	*next;
}               savefd;

int		is_endofline(char *buf);
int		get_next_line(int fd, char **line);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*join_and_realloc(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
void    freeelem(savefd **lstbegin, int fd);

#endif
