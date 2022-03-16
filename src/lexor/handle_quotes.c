/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 14:04:32 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/03/15 16:56:35 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexor.h"

int	handle_quotes_inside_word(int i, char *str, char del)
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

int	handle_quotes(int i, char *str, char del, t_lexor **lexor_list)
{
	int	j;

	j = 0;
	if (str[i + j] == del)
	{
		j++;
		while (str[i + j] != del && str[i + j])
			j++;
		if (!add_node(ft_substr(str, i, j + 1), 0, lexor_list))
			printf("EMERGENCY!\n");
		j++;
	}
	return (j + 1);
}
