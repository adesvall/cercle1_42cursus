/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 03:02:21 by adesvall          #+#    #+#             */
/*   Updated: 2020/11/26 23:06:18 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	**line;

	line = malloc(sizeof(char*));
	(void)argc;
	fd = open(argv[1], O_RDWR);
	while (get_next_line(fd, line))
	{
		printf("Lfd1:%s\n", *line);
		free(*line);
	}
	free(*line);
	free(line);
	printf("Error or EOF\n");
}
