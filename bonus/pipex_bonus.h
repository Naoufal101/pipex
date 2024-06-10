/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:35:50 by nhimad            #+#    #+#             */
/*   Updated: 2024/06/10 16:21:02 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include "gnl/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct s_var
{
	char	**cml;
	char	**paths;
}			t_var;

void		ft_free(char **str);
int			search_count(char *str, char c);
char		**find_path(char **env);
char		**clean(char **str);
char		**ft_split_p(char *str);
int			search_count(char *str, char c);
void		child(char **cml, char **paths, char **env);
void		ft_dup2(int cfd, int fd);

int			open_error(char *str, int fd, int d_fd);
int			ft_open_error(void);
int			ft_open(char *str, int key);

int			ft_strcmp(const char *s1, const char *s2);

int			ft_exit(t_var variable);
#endif