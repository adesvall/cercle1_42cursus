/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 03:02:21 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/01 15:45:44 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line_bonus.h"

int	main(int argc, char **argv)
{
/*	int		fd;
	int		fd2;
	int		fd3;*/
	int code = 1;
/*	int code2 = 1;
	int code3 = 1;*/
	char	*line;

	(void)argc;
	(void)argv;
	while (code >= 0)
	{
		code = get_next_line(0, &line);
		printf("%d: %s\n", code, line);
		free(line);
	}
/*	fd = open(argv[1], O_RDWR);
	fd2 = open(argv[2], O_RDWR);
	fd3 = open(argv[3], O_RDWR);
	while (code==1)
	{
		code = get_next_line(fd, &line);
		if (code >= 0)
		{
			printf("code: %d, Lfd1:%s\n", code, line);
			free(line);
		}
		code2 = get_next_line(fd2, &line);
		if (code2 >= 0)
		{
			printf("code2: %d, Lfd2:%s\n", code2, line);
			free(line);
		}
		code3 = get_next_line(fd3, &line);
		if (code3 >= 0)
		{
			printf("code3: %d, Lfd2:%s\n", code3, line);
			free(line);
		}
	}*/
	printf("Error or EOF\n");
}
