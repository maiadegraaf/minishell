/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_token.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/18 10:27:43 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/14 18:41:33 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "lexor.h"

t_tokens	check_token(int c)
{
	static int	token_arr[5][2] = {
	{'|', PIPE},
	{'\n', NEW_LINE},
	{'>', GREAT},
	{'<', LESS},
	};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (token_arr[i][0] == c)
			return (token_arr[i][1]);
		i++;
	}
	return (0);
}

int	handle_token(char *str, int i, t_lexor **lexor_list)
{
	t_tokens	token;
	int	j;

	j = 0;
	while (str[i + j + 1] != ' ' && str[i + j + 1] && !(check_token(str[i + j + 1]))
		&& !(str[i + j + 1] == 34 && str[i + j + 1] == 39))
		j++;
	token = check_token(str[i]);
	if (token == DOLLAR)
	{
		if (!add_node(ft_substr(str, i + 1, j), DOLLAR, lexor_list))
			printf("EMERGENCY!\n");
		return (j + 1);
	}
	else if (token == GREAT && check_token(str[i + 1]) == GREAT)
	{
		if (!add_node(NULL, GREAT_GREAT, lexor_list))
			printf("EMERGENCY!\n");
		return (2);
	}
	else if (token == LESS && check_token(str[i + 1]) == LESS)
	{
		if (!add_node(NULL, LESS_LESS, lexor_list))
			printf("EMERGENCY!\n");
		return (2);
	}
	else if (token)
	{
		if (!add_node(NULL, token, lexor_list))
			printf("EMERGENCY!\n");
		return (1);
	}	
	return (0);
}
