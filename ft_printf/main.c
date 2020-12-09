#include <stdio.h>
#include "ft_printf.h"
#define ARGS "%0*.*i\n", 4, -1, 8

int 	main()
{
	printf(ARGS);
	ft_printf(ARGS);
}