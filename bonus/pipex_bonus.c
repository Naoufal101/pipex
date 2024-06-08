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

void	pipe_exc(char *cmd, char **env)
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		variable->cml = ft_split_p(argv[2]);
		if (!variable->cml)
			exit(1);
		child(variable->cml, variable->paths, &(variable->valid_path), env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_var	variable;
	int		fork_s;
	int i;
	int fd;

	variable.cml = 0;
	variable.valid_path = 0;
	variable.paths = find_path(env);
	if (!variable.paths)
		return (1);
	if (argc >= 5)
	{
		i = 2;
		fd_in = open_file(av[1], 0);
		fd_out = open_file(av[ac - 1], 1);
		dup2(fd_in, 0);
	
		while (i < ac - 2)
			pipe_exc(av[i++], env);
		dup2(fd_out, 1);
		exec(av[ac - 2], env);
	}
	return (ft_exit(variable));
}
