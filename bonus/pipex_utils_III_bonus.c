/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_III_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:49:12 by nhimad            #+#    #+#             */
/*   Updated: 2024/06/10 15:59:51 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_error(char *str, int fd, int d_fd)
{
	if (fd == -1)
	{
		perror(str);
		return (fd);
	}
	ft_dup2(fd, d_fd);
	close(fd);
	return (0);
}

int	ft_open_error(void)
{
	int	pp[2];

	if (pipe(pp) == -1)
		exit(1);
	close(pp[1]);
	ft_dup2(pp[0], 0);
	close(pp[0]);
	return (1);
}

int	ft_open(char *str, int key)
{
	int	fd;

	if (key == 0)
	{
		fd = open(str, O_RDONLY);
		return (open_error(str, fd, 0));
	}
	else if (key == 1)
	{
		fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (open_error(str, fd, 1))
			exit(1);
	}
	else if (key == 3)
	{
		fd = open(str, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (open_error(str, fd, 1))
			exit(1);
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s2[i] == s1[i])
		i++;
	return ((int)(s1[i] - s2[i]));
}
