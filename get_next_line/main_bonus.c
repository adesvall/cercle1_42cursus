/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 03:02:21 by adesvall          #+#    #+#             */
/*   Updated: 2020/11/30 18:49:30 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line_bonus.h"

int	main(int argc, char **argv)
{
	int		fd;
	int		fd2;
	int code = 1;
	int code2 = 1;
	char	**line;

	line = malloc(sizeof(char*));
	(void)argc;
	fd = open(argv[1], O_RDWR);
	/*get_next_line(fd, line);
	printf("Lfd1:%s\n", *line);*/
	fd2 = open(argv[2], O_RDWR);
	while (code==1 && code2==1)
	{
		code = get_next_line(fd, line);
		printf("code: %d, Lfd1:%s\n", code, *line);
		free(*line);
		code2 = get_next_line(fd2, line);
		printf("code2: %d, Lfd2:%s\n", code2, *line);
		free(*line);
/*		get_next_line(fd2, line);
		printf("Lfd2:%s\n", *line);
		free(*line);*/
	}
	code=1;
	code2=1;
	while (code==1 && code2==1)
	{
		code = get_next_line(fd, line);
		printf("code: %d, Lfd1:%s\n", code, *line);
		free(*line);
		code2 = get_next_line(fd2, line);
		printf("code2: %d, Lfd2:%s\n", code2, *line);
		free(*line);
/*		get_next_line(fd2, line);
		printf("Lfd2:%s\n", *line);
		free(*line);*/
	}
	printf("Error or EOF\n");
	free(line);
}
