#include <stdio.h>
#include "ft_printf.h"
#define ARGS "pt: %-*p.\n", 20, a

int 	main()
{
	char *a = "salut les potes";
	
	printf(ARGS);
	ft_printf(ARGS);

}