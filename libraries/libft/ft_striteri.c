/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 14:24:06 by mgraaf        #+#    #+#                 */
/*   Updated: 2021/12/16 14:24:09 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		i;

	i = 0;
	if ((!s || !f) || (!s && !f))
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
	s[i] = '\0';
}
