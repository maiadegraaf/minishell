/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 10:49:04 by fpolycar      #+#    #+#                 */
/*   Updated: 2021/12/17 15:17:43 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_binary(int pid, int *bin)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (bin[i] == 1)
		{
			kill(pid, SIGUSR2);
		}
		if (bin[i] == 0)
		{
			kill(pid, SIGUSR1);
		}
		usleep(100);
		i--;
	}
}

int	*char_to_bin(char c)
{
	int	*binary;
	int	i;
	int	n;

	binary = ft_calloc(8, sizeof(int));
	if (!binary)
		return (NULL);
	n = (unsigned int)c;
	i = 7;
	while (i >= 0)
	{
		binary[i] = n & 1;
		i--;
		n >>= 1;
	}
	return (binary);
}

int	main(int argc, char **argv)
{	
	int	pid;
	int	i;
	int	*bin;

	if (argc == 3)
	{
		i = 0;
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != 0)
		{
			bin = char_to_bin(argv[2][i]);
			send_binary(pid, bin);
			i++;
			free(bin);
		}
	}
	else
		write(1, "\nERROR expected: ./execute [pid] [str]\n\n", 43);
}
