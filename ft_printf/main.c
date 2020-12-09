#include <stdio.h>
#include "ft_printf.h"
#define ARGS "%-20p%-20p%-20p%-20p\n",&a1,&a2,&a3,&a4

int 	main()
{
	char *a = "salut les potes";
	int b = 147483648;
	int a1, a2, a3, a4;

	a = 0;
	printf(ARGS);
	ft_printf(ARGS);

}