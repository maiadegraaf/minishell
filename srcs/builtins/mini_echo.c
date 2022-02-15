#include "builtins.h"

int		mini_echo(t_tools *tools)
{
	printf("%s\n", tools->pwd);
	return (1);
}