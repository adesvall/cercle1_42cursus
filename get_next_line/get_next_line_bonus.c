/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 02:38:25 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/01 14:13:56 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_save	*ft_lstfind_fd(int fd, t_save **lst)
{
	t_save	*res;

	if (!lst)
		return (0);
	res = *lst;
	while (res)
	{
		if (res->fd == fd)
			return (res);
		res = res->next;
	}
	if (!(res = malloc(sizeof(t_save))))
		return (0);
	res->fd = fd;
	res->ligne = 0;
	res->next = *lst;
	*lst = res;
	return (res);
}

char	*trimstart(char *ligne)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	if (!ligne)
		return (0);
	while (ligne[i] && ligne[i] != '\n')
		i++;
	if (!(res = malloc(sizeof(char) * ((ft_strlen(ligne) - i) + 1))))
	{
		free(ligne);
		return (0);
	}
	j = 0;
	if (ligne[i])
	{
		i++;
		while (ligne[i])
			res[j++] = ligne[i++];
	}
	res[j] = '\0';
	free(ligne);
	return (res);
}

char	*trimend(char *str)
{
	int		i;
	char	*rtn;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!(rtn = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		rtn[i] = str[i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

int		get_next_line(int fd, char **line)
{
	static t_save	*savebegin = 0;
	t_save			*save;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(save = ft_lstfind_fd(fd, &savebegin)))
		return (ft_clean(&savebegin, -1));
	return (get_next_line2(&savebegin, save, line, fd));
}

int		get_next_line2(t_save **lstbegin, t_save *save, char **line, int fd)
{
	char	*buf;
	int		resread;

	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (ft_clean(lstbegin, -1));
	resread = 1;
	while (!is_endofline(save->ligne) && resread != 0)
	{
		if ((resread = read(fd, buf, BUFFER_SIZE)) == -1)
		{
			free(buf);
			return (ft_clean(lstbegin, -1));
		}
		buf[resread] = '\0';
		if (!(save->ligne = join_and_realloc(save->ligne, buf)))
			return (ft_clean(lstbegin, -1));
	}
	free(buf);
	if (!(*line = trimend(save->ligne)))
		return (ft_clean(lstbegin, -1));
	if (!(save->ligne = trimstart(save->ligne)))
		return (ft_clean(lstbegin, -1));
	if (resread == 0)
		return (ft_clean(lstbegin, fd));
	return (1);
}
