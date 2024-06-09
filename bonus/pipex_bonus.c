/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:11:32 by nhimad            #+#    #+#             */
/*   Updated: 2024/06/09 18:49:58 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipe_exc(char *cmd, char **env, t_var *variable)
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		ft_exit(*variable);
	pid = fork();
	if (pid == -1)
		ft_exit(*variable);
	if (pid == 0)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		close(p_fd[1]);
		variable->cml = ft_split_p(cmd);
		if (!variable->cml)
			exit(1);
		child(variable->cml, variable->paths, env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
	}
}

void	here_doc_child(char *limiter, int *p_fd)
{
	char	*str;

	str = get_next_line(0);
	while (ft_strncmp(str, limiter, (ft_strlen(str) - 1)))
	{
		close(p_fd[0]);
		write(p_fd[1], str, ft_strlen(str));
		str = get_next_line(0);
	}
	exit(0);
}

void	here_doc(char *limiter, int ac, t_var variable)
{
	int	p_fd[2];
	int	pid;

	if (ac < 6)
	{
		ft_putendl_fd("Invalid number of arguments", 2);
		ft_exit(variable);
	}
	if (pipe(p_fd) == -1)
		ft_exit(variable);
	pid = fork();
	if (pid == -1)
		ft_exit(variable);
	if (pid == 0)
		here_doc_child(limiter, p_fd);
	else
	{
		close(p_fd[1]);
		ft_dup2(p_fd[0], 0);
		close(p_fd[0]);
	}
}

void	ft_pipex(int argc, char **argv, char **env, t_var variable)
{
	int	i;

	i = 2;
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
	{
		here_doc(argv[2], argc, variable);
		ft_open(argv[argc - 1], 3);
		i++;
	}
	else
	{
		if (ft_open(argv[1], 0) == -1)
			i += ft_open_error();
		ft_open(argv[argc - 1], 1);
	}
	while (i < argc - 2)
		pipe_exc(argv[i++], env, &variable);
	if (fork() == 0)
	{
		variable.cml = ft_split_p(argv[argc - 2]);
		if (!variable.cml)
			exit(1);
		child(variable.cml, variable.paths, env);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_var	variable;

	variable.paths = find_path(env);
	if (!variable.paths)
		return (1);
	if (argc >= 5)
		ft_pipex(argc, argv, env, variable);
	else
		ft_putendl_fd("Invalid number of arguments", 2);
	ft_exit(variable);
}
