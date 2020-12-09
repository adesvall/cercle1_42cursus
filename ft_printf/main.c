#include <stdio.h>
#include "ft_printf.h"
#define ARGS "%.5p", a

int 	main()
{
	char *a = "salut les potes";
	int b = 147483648;
	int a1, a2, a3, a4;

	a = 0;
	//printf(ARGS);
	ft_printf(ARGS);

}