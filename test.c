#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"

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
void    leck()
{
    system("leaks -q pipex");
}

// void collect(char **cml)
// {
//     int i;
//     int first;
//     int last;
//     char *temp;

//     i = 0;
//     first = 0;
//     while (cml[i+1])
//     {
//         last = ft_strlen(cml[i+1]) - 1;
//         if (cml[i][first] == '{' && cml[i+1][last] == '}')
//         {
//             temp = ft_strjoin(cml[i], " ");
//             free(cml[i]);
//             cml[i] = temp;
//             temp = ft_strjoin(cml[i], cml[i+1]);
//             free(cml[i]);
//             cml[i] = temp;
//             free(cml[i+1]);
//             cml[i+1] = 0;
//         }
//         i++;
//     }
// }

////////////////
void    child(char **cml, char **paths,char **valid_path, char **env)
{
    int i;
    
    i = 0;
    if (access(cml[0], F_OK) == -1 && cml[0][0] != '/')
    {
        valid_path[0] = ft_strjoin("/", cml[0]);
        free(cml[0]);
        cml[0] = valid_path[0];
        while(paths[i])
        {
            valid_path[0] = ft_strjoin(paths[i], cml[0]);
            if (access(valid_path[0], F_OK) != -1)
                break ;
            free(valid_path[0]);
            i++;
        }
        if (!paths[i])
        {
            ft_putstr_fd("command not found: ", 2);
            ft_putendl_fd(cml[0]+1, 2);
            exit (1);
        }
        else
        {
            if (execve(valid_path[0], cml, env) == -1)
                perror(valid_path[0]);
            exit (1); 
        }
    }
    if (access(cml[0], X_OK) != -1)
    {
        if (execve(cml[0], cml, env) == -1)
            perror(cml[0]);
    }
    else
    {
        ft_putstr_fd("No such file or directory: ", 2);
        ft_putendl_fd(cml[0], 2);
    }
}
int     search_count(char *str, char c)
{
    int counter;

    counter = 0;
    while (*str)
    {
        if (*str == c)
            counter++;
        str++;
    }
    return (counter);
}

char    **clean(char **str)
{
    int j;
    int i;
    int c;
    char **dp;
    char **ca;

    i = 0;
    c = 0;

    ca = ft_split(str[0], ' ');
    while (ca[c])
    {
        c++;
    }
    free(str[0]);

    i = 1;
    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            if (str[i][j] != ' ')
            {
                c++;
                break;
            }
            j++;
        }
        i++;
    }

    dp = malloc((c+1) * sizeof(char *));
    if (!dp)
    {
        ft_free(str);
        return (NULL);
    }
    dp[c] = 0;
    i = 0;
    c = 0;
    while(ca[i])
    {
        dp[c] = ca[i];
        c++;
        i++;
    }

    free(ca);
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
            free (str[i]);
        i++;
    }
    free (str);
    return (dp);
}
char    **ft_split_p(char *str)
{
    char **s;

    if (search_count(str, '\'') >= 2)
    {
        s = ft_split(str, '\'');
        //s[0][ft_strlen(s[0]) - 1] = 0;
        return (clean(s));
    }
    else if (search_count(str, '"') >= 2)
    {
        s = ft_split(str, '"');
        //s[0][ft_strlen(s[0]) - 1] = 0;
        return (clean(s));
    }
    return (ft_split(str, ' '));
}
char    **find_path(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (!ft_strncmp(env[i], "PATH=", 5))
            return (ft_split(env[i]+5, ':'));
        i++;
    }
    return (ft_split("", ':'));
}
int     main(int argc, char **argv, char **env)
{
    char **cml = 0;
    char **paths = 0;
    char *valid_path = 0;
    int pipes[2];
    int fd;
    int i;
    int exit;

    int pid = 0;
    exit = 1;
    i = 0;
    fd = 0;
    paths = find_path(env);
    //atexit(leck);
    while (argv[i])
    {
        printf("%s.\n", argv[i]);
        i++;
    }

    if (argc == 5)
    {

        if (pipe(pipes) == -1)
        {
            printf("the pipe fail\n");
            return (1);
        } 
        if (fork() == 0)
        {
            fd = open(argv[1], O_RDONLY);
            if (fd == -1)
                perror(argv[1]);
            else
            {
                cml = ft_split_p(argv[2]);
                dup2(fd, 0);
                close(fd);
                close(pipes[0]);
                dup2(pipes[1], 1);
                close(pipes[1]);
                child(cml, paths, &valid_path, env);
            }
        }
        else
        {
            if (fork() == 0)
            {
                fd = open(argv[4], O_RDWR | O_CREAT | O_TRUNC , 0644);
                if (fd == -1)
                    perror("");
                else
                {
                    cml = ft_split_p(argv[3]);
                    i = 0;
                    while (cml[i])
                    {
                        printf("\n%s.\n", cml[i]);
                        i++;
                    }
                    dup2(fd, 1);
                    close(fd);
                    close(pipes[1]);
                    dup2(pipes[0], 0);
                    close(pipes[0]);
                    child(cml, paths, &valid_path, env); 
                }
            }

        }
    }
    close(pipes[0]);
    close(pipes[1]);
    while (wait(&pid) > 0)
        if (pid == 0)
            exit = 0;
    ft_free(cml);
    ft_free(paths);
    free(valid_path);
    return (exit);
}
