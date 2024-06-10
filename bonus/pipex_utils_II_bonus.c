/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_II_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:10:38 by nhimad            #+#    #+#             */
/*   Updated: 2024/06/10 11:56:28 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	search_count(char *str, char c)
{
	int	counter;

	counter = 0;
	while (*str)
	{
		if (*str == c)
			counter++;
		str++;
	}
	return (counter);
}

char	**find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (ft_split("", ':'));
}

void	ft_dup2(int cfd, int fd)
{
	if (dup2(cfd, fd) < 0)
	{
		perror("");
		exit(1);
	}
}

int	ft_exit(t_var variable)
{
	int	s;
	int	status;

	s = 127;
	close(0);
	while (wait(&status) > 0)
		if (status == 0)
			s = 0;
	ft_free(variable.paths);
	exit(s);
}
