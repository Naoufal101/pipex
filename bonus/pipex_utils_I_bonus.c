/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_I_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:35:01 by nhimad            #+#    #+#             */
/*   Updated: 2024/06/07 11:35:04 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	command_search(char **cml, char **paths, char **valid_path)
{
	int	i;

	i = 0;
	valid_path[0] = ft_strjoin("/", cml[0]);
	free(cml[0]);
	cml[0] = valid_path[0];
	while (paths[i])
	{
		valid_path[0] = ft_strjoin(paths[i], cml[0]);
		if (access(valid_path[0], F_OK) != -1)
			break ;
		free(valid_path[0]);
		i++;
	}
	return (i);
}

void	path_exec(char **cml, char **env)
{
	if (access(cml[0], F_OK) != -1)
	{
		execve(cml[0], cml, env);
		perror(cml[0]);
	}
	else
	{
		ft_putstr_fd(cml[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
}

void	child_error(char **cml, char **paths)
{
	ft_free(cml);
	ft_free(paths);
	exit(1);
}

void	child(char **cml, char **paths, char **valid_path, char **env)
{
	int	i;

	i = 0;
	if (access(cml[0], F_OK) == -1 && cml[0][0] != '/' && paths[i])
	{
		i = command_search(cml, paths, valid_path);
		if (!paths[i])
		{
			ft_putstr_fd(cml[0] + 1, 2);
			ft_putendl_fd(": command not found", 2);
		}
		else
		{
			execve(valid_path[0], cml, env);
			perror(valid_path[0]);
			free(valid_path[0]);
		}
		child_error(cml, paths);
	}
	path_exec(cml, env);
	child_error(cml, paths);
}
