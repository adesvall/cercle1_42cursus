#include <stdio.h>
#include "ft_printf.h"
#define ARGS "\"%-5.0i.\"\n", 0

int 	main()
{
	char *a = "salut les potes";
	int b = 147483648;
	a = 0;
	printf(ARGS);
	ft_printf(ARGS);

}