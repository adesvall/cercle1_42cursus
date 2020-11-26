/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 02:38:25 by adesvall          #+#    #+#             */
/*   Updated: 2020/11/26 22:43:43 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

savefd	*ft_lstfind_fd(int fd, savefd **lst)
{
	savefd	*res;

	if (!lst)
		return (0);
	res = *lst;
	while (res)
	{
		if (res->fd == fd)
			return (res);
		res = res->next;
	}
	if (!(res = malloc(sizeof(savefd))))
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
	if (!ligne[i])
	{
		free(ligne);
		return (0);
	}
	if (!(res = malloc(sizeof(char) * ((ft_strlen(ligne) - i) + 1))))
		return (0);
	i++;
	j = 0;
	while (ligne[i])
		res[j++] = ligne[i++];
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
	char			*buf;
	int				resread;
	static savefd	**savebegin = 0;
	savefd			*save;

	resread = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (savebegin == 0)
	{
		savebegin = malloc(sizeof(savefd*));
		*savebegin = 0;
	}
	save = ft_lstfind_fd(fd, savebegin);
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!is_endofline(save->ligne) && resread != 0)
	{
		if ((resread = read(fd, buf, BUFFER_SIZE)) == -1)
		{
			free(buf);
			return (-1);
		}
		buf[resread] = '\0';
		save->ligne = join_and_realloc(save->ligne, buf);
	}
	free(buf);
	*line = trimend(save->ligne);
	save->ligne = trimstart(save->ligne);
	if (resread == 0 && !is_endofline(save->ligne))
	{
		freeelem(savebegin, fd);
		return (0);
	}
	return (1);
}
