/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:34:43 by nhimad            #+#    #+#             */
/*   Updated: 2024/06/07 11:37:46 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_child(t_var *variable, char **argv, char **env)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror(argv[1]);
		exit (1);
	}
	else
	{
		ft_dup2(fd, 0);
		close(fd);
		close(variable->pipes[0]);
		ft_dup2(variable->pipes[1], 1);
		close(variable->pipes[1]);
		variable->cml = ft_split_p(argv[2]);
		if (!variable->cml)
			exit(1);
		child(variable->cml, variable->paths, &(variable->valid_path), env);
	}
}

void	second_child(t_var *variable, char **argv, char **env)
{
	int	fd;

	fd = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(argv[4]);
		exit (1);
	}
	else
	{
		ft_dup2(fd, 1);
		close(fd);
		close(variable->pipes[1]);
		ft_dup2(variable->pipes[0], 0);
		close(variable->pipes[0]);
		variable->cml = ft_split_p(argv[3]);
		if (!variable->cml)
			exit(1);
		child(variable->cml, variable->paths, &(variable->valid_path), env);
	}
}

int	ft_exit(t_var variable)
{
	close(variable.pipes[0]);
	close(variable.pipes[1]);
	variable.exit = 127;
	while (wait(&variable.status) > 0)
		if (variable.status == 0)
			variable.exit = 0;
	ft_free(variable.paths);
	return (variable.exit);
}

void	ft_pipe(t_var *variable)
{
	if (pipe(variable->pipes) == -1)
	{
		ft_free(variable->paths);
		ft_putendl_fd("the pipe fail", 2);
		exit(1);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_var	variable;
	int		fork_s;

	variable.cml = 0;
	variable.valid_path = 0;
	variable.paths = find_path(env);
	if (!variable.paths)
		return (1);
	if (argc == 5)
	{
		ft_pipe(&variable);
		fork_s = fork();
		if (fork_s == -1)
		{
			perror("");
			ft_free(variable.paths);
			return (1);
		}
		else if (fork_s == 0)
			first_child(&variable, argv, env);
		else if (fork() == 0)
			second_child(&variable, argv, env);
	}
	return (ft_exit(variable));
}
