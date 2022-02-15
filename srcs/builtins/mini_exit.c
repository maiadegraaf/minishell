#include "builtins.h"

int		mini_exit(t_tools *tools)
{
	printf("%s\n", tools->pwd);
	return (1);
}