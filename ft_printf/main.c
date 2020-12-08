#include <stdio.h>
#include "ft_printf.h"
#define ARGS "pt: %*.16d.\n", 30, b

int 	main()
{
	char *a = "salut les potes";
	int b = 147483648;
	
	printf(ARGS);
	ft_printf(ARGS);

}