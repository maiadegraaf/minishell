/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 13:35:26 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/03/30 16:20:30 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

size_t	dollar_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i + 1);
		i++;
	}
	return (0);
}

int	arg_length(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

	

// }

// size_t str_replace_with_var_lenght(char *str, t_tools *tools, t_simple_cmds *tmp)
// {
// 	size_t	len;
// 	int		i;
// 	int		k;
// 	int		process;

// 	len = 0;
// 	i = 0;
// 	process = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			k = 0;
// 			while (tools->envp[k])
// 			{
// 				if (ft_strncmp(str + i + 1,
// 						tools->envp[k], equal_sign(tools->envp[k]) - 1) == 0
// 					&& (str[equal_sign(tools->envp[k]) + i] == '\0'
// 						|| str[equal_sign(tools->envp[k]) + i] == '$'
// 						|| str[equal_sign(tools->envp[k]) + i] == ' '
// 						|| str[equal_sign(tools->envp[k]) + i] == '\"'))
// 				{
// 					// len += ft_strlen(tools->envp[k] + equal_sign(tools->envp[k]));
// 					i += equal_sign(tools->envp[k]);
// 					process = 1;
// 				}
// 				if (process == 0 && k == arg_length(tools->envp) - 1)
// 					i += ft_strlen(str + i);
// 				k++;
// 			}
// 		}
// 		else
// 		{
// 			len++;
// 			i++;
// 		}
// 	}
// 	return(len);
// }

void	expander_loop(t_tools *tools, t_simple_cmds *tmp, int i)
{
	int		j;
	int		k;
	int		len_non_var;
	char	*arr_tmp;
	char	*tmp_transformed = NULL;
	char	*tmp_tmp;

	j = 0;
	arr_tmp = tmp->str[i];
	while (arr_tmp[j])
	{
		if (arr_tmp[j] == '$')
		{
			k = 0;
			while (tools->envp[k])
			{
				if (ft_strncmp(arr_tmp + j + 1,
						tools->envp[k], equal_sign(tools->envp[k]) - 1) == 0
					&& (arr_tmp[equal_sign(tools->envp[k]) + j] == '\0'
						|| arr_tmp[equal_sign(tools->envp[k]) + j] == '$'
						|| arr_tmp[equal_sign(tools->envp[k]) + j] == ' '
						|| arr_tmp[equal_sign(tools->envp[k]) + j] == '\"'))
				{
					if (!tmp_transformed)
						tmp_transformed = ft_substr(tools->envp[k],
								equal_sign(tools->envp[k]),
								ft_strlen(tools->envp[k]));
					else
					{
						tmp_tmp = tmp_transformed;
						free(tmp_transformed);
						tmp_transformed = ft_strjoin(tmp_tmp, ft_substr(tools->envp[k],
								equal_sign(tools->envp[k]),
								ft_strlen(tools->envp[k])));	
					}
					j += equal_sign(tools->envp[k]);
				}
				k++;
			}
		}
		else
		{
			if (!tmp_transformed)
			{
				tmp_transformed = ft_strdup(arr_tmp);
				ft_strlcpy(tmp_transformed, tmp_transformed, 2);
			}
			else
			{
				tmp_tmp = tmp_transformed;
				free(tmp_transformed);
				tmp_transformed = ft_strjoin(tmp_transformed, tmp_tmp);	
			}
			j++;
		printf("tmp_transformed = %s\n\n", tmp_transformed);
		}
	}
	// free(tmp->str[i]);
	// tmp->str[i] = tmp_transformed;
}

void	expander(t_tools *tools, t_simple_cmds *simple_cmds)
{
	t_simple_cmds	*tmp;
	int				i;

	i = 0;
	tmp = simple_cmds;
	while (tmp)
	{
		while (tmp->str[i] && dollar_sign(tmp->str[i]) != 0)
		{
			if (tmp->str[i][0] != '\'' && tmp->str[i][ft_strlen(tmp->str[i])] != '\'')
			{
				// printf("%zu\n", str_replace_with_var_lenght(tmp->str[i], tools, tmp));
				expander_loop(tools, tmp, i);
			}
			i++;
		}
		tmp = tmp->next;
	}
}
