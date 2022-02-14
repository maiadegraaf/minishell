/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 10:52:13 by fpolycar      #+#    #+#                 */
/*   Updated: 2021/12/15 13:43:39 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "libft/libft.h"

typedef struct s_msg
{
	char		c;
	size_t		size;
}				t_msg;

#endif