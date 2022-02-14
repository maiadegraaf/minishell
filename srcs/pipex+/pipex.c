/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 14:58:07 by mgraaf        #+#    #+#                 */
/*   Updated: 2021/12/23 15:26:26 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1_process(t_pipex *info, int *end)
{
	int		i;
	char	*mycmd;

	if (dup2(info->f1, STDIN_FILENO) < 0)
		return (perror("Dup "));
	if (dup2(end[1], STDOUT_FILENO) < 0)
		return (perror("Dup "));
	close(end[0]);
	close(info->f1);
	i = 0;
	while ((info->paths)[i])
	{
		mycmd = ft_strjoin((info->paths)[i], (info->cmds1)[0]);
		if (!access(mycmd, F_OK && X_OK))
			execve(mycmd, info->cmds1, info->envp);
		free(mycmd);
		i++;
	}
	perror("Cmd not found ");
	exit(EXIT_FAILURE);
}

void	child2_process(t_pipex *info, int *end)
{
	int		i;
	char	*mycmd;

	if (dup2(info->f2, STDOUT_FILENO) < 0)
		return (perror("Dup "));
	if (dup2(end[0], STDIN_FILENO) < 0)
		return (perror("Dup "));
	close(end[1]);
	close(info->f2);
	i = 0;
	while ((info->paths)[i])
	{
		mycmd = ft_strjoin((info->paths)[i], (info->cmds2)[0]);
		if (!access(mycmd, F_OK && X_OK))
			execve(mycmd, info->cmds2, info->envp);
		free(mycmd);
		i++;
	}
	perror("Cmd not found ");
	exit(EXIT_FAILURE);
}

void	pipex(t_pipex *info)
{
	int		end[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	pipe(end);
	child1 = fork();
	if (child1 < 0)
		return (perror("Fork: "));
	if (child1 == 0)
		child1_process(info, end);
	child2 = fork();
	if (child2 < 0)
		return (perror("Fork: "));
	if (child2 == 0)
		child2_process(info, end);
	close(end[0]);
	close(end[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	info;

	if (argc != 5)
	{
		perror("Invalid number of arguments");
		exit(EXIT_FAILURE);
	}
	info.f1 = open(argv[1], O_RDONLY);
	info.f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (info.f1 < 0 || info.f2 < 0)
	{
		perror("Open ");
		exit(EXIT_FAILURE);
	}
	info.envp = envp;
	info.cmds1 = ft_split(argv[2], ' ');
	info.cmds2 = ft_split(argv[3], ' ');
	info.paths = parse_envp(argv, envp);
	pipex(&info);
	return (0);
}
