/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:35:50 by nhimad            #+#    #+#             */
/*   Updated: 2024/06/07 11:37:11 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
// fork
# include <unistd.h>

typedef struct s_var
{
	char	**cml;
	char	**paths;
	char	*valid_path;
	int		pipes[2];
	int		status;
	int		exit;
}			t_var;

void		ft_free(char **str);
int			search_count(char *str, char c);
char		**find_path(char **env);
char		**clean(char **str);
char		**ft_split_p(char *str);
int			search_count(char *str, char c);
void		child(char **cml, char **paths, char **valid_path, char **env);
void		ft_dup2(int cfd, int fd);
#endif