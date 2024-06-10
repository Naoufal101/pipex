/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:11:09 by nhimad            #+#    #+#             */
/*   Updated: 2024/06/10 10:15:22 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_mini_copy(char **dp, char **ca)
{
	int	c;

	c = 0;
	while (ca[c])
	{
		dp[c] = ca[c];
		c++;
	}
	free(ca);
	return (c);
}

void	ft_copy(char **str, char **dp, int c)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j] && str[i][j] == ' ')
			j++;
		if (str[i][j])
		{
			dp[c] = str[i];
			c++;
		}
		else
			free(str[i]);
		i++;
	}
	free(str);
}

int	ft_counter(char **str)
{
	int	i;
	int	j;
	int	c;

	i = 1;
	j = 0;
	c = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] != ' ')
			{
				c++;
				break ;
			}
			j++;
		}
		i++;
	}
	return (c);
}

char	**clean(char **str)
{
	int		c;
	char	**dp;
	char	**ca;

	c = 0;
	ca = ft_split(str[0], ' ');
	if (!ca)
		return (NULL);
	free(str[0]);
	while (ca[c])
	{
		c++;
	}
	c += ft_counter(str);
	dp = malloc((c + 1) * sizeof(char *));
	if (!dp)
	{
		ft_free(ca);
		ft_free(str);
		return (NULL);
	}
	dp[c] = 0;
	c = ft_mini_copy(dp, ca);
	ft_copy(str, dp, c);
	return (dp);
}

char	**ft_split_p(char *str)
{
	char	**s;

	if (search_count(str, '\'') >= 2)
	{
		s = ft_split(str, '\'');
		if (!s)
			return (NULL);
		return (clean(s));
	}
	else if (search_count(str, '"') >= 2)
	{
		s = ft_split(str, '"');
		if (!s)
			return (NULL);
		return (clean(s));
	}
	return (ft_split(str, ' '));
}
