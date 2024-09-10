#include "stdio.h"

int main (int ac, char **av)
{
	if (ac == 5 || ac == 6)
		printf ("ok\n");
	else
		printf ("non\n");
	(void) av;
}
