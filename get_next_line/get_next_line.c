/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 02:38:25 by adesvall          #+#    #+#             */
/*   Updated: 2020/11/25 13:47:11 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static int	linenu;
	char		*buf;
	int			resread;
	char		*ligne;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!is_endofline(buf) && resread != 0)
	{
		if ((resread = read(fd, buf, BUFFER_SIZE)) == -1)
		{
			free(buf);
			return (-1);
		}
		buf[resread] = '\0';
		ligne = join_and_realloc(ligne, buf);
	}

	
	free(buf);
	if (resread == 0)
		return (0);
	return (1);
	
}