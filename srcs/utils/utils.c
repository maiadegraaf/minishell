/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 11:17:26 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/02/21 11:17:31 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	count_quotes(char *line)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
			nb++;
		i++;
	}
	return (nb);
}
