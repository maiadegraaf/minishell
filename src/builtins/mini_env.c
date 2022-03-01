/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 12:09:05 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/02/17 12:19:23 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	mini_env(t_tools *tools)
{
	int	i;

	i = 0;
	printf("HELLO\n");
	while (tools->envp[i])
	{
		if (!ft_strncmp(tools->envp[i], "PWD=", 4))
			printf("PWD=%s\n", tools->pwd);
		else if (!ft_strncmp(tools->envp[i], "OLDPWD=", 7))
			printf("OLDPWD=%s\n", tools->old_pwd);
		else
			printf("%s\n", tools->envp[i]);
		i++;
	}
	return (1);
}