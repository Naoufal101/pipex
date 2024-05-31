#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
// void    leck()
// {
//     system("leaks -q pipex");
// }

int     main(int argc, char **argv, char **env)
{
    (void) argc;
    char **cml = 0;
    char **paths = 0;
    char *valid_path = 0;
    int i = 0;
    int fd = 0;

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        perror(argv[1]);

    else
    {
        dup2(i, 0);
        close(i);

        //split here
        cml = ft_split(argv[2], ' ');
        valid_path = cml[0];
        if (cml[0][0] != '/')
        {
            valid_path = ft_strjoin("/", cml[0]);
            free(cml[0]);
            cml[0] = valid_path;

            //and split here
            paths = ft_split(&env[4][5], ':');
            while(paths[i])
            {
                valid_path = ft_strjoin(paths[i], cml[0]);
                if (access(valid_path, F_OK) != -1)
                    break ;
                free(valid_path);
                i++;
            }
            if (!paths[i])
                printf("command not found: %s\n", cml[0]+1);
            ft_free(paths);
            free(valid_path);
        }
        if (access(valid_path, X_OK) != -1)
            execve(valid_path, cml, env);
        else
            printf("No such file or directory: %s\n", cml[0]);
        ft_free(cml);
    }
}