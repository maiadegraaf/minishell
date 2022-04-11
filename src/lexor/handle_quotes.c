/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 14:04:32 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/04/08 10:45:47 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexor.h"

int	handle_quotes(int i, char *str, char del)
{
	int	j;

	j = 0;
	if (str[i + j] == del)
	{
		j++;
		while (str[i + j] != del && str[i + j])
			j++;
		j++;
	}
	return (j);
}

