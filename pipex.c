/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:53:49 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/10 12:45:41 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* 
After fork:
Parent id = (random)
Child id = 0 

*/

void free_arr(char **arr)
{
	int i;

	i = 0;
	while(arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int main(int argc, char **argv)
{
	if (argc < 5)
		return(perror("Insufficient args"), -1);
	char *path = "/usr/bin/";
	char *temparg = ft_calloc(ft_strlen(argv[2]) + ft_strlen(argv[1]) + 2, sizeof(char));
	ft_strlcpy(temparg, argv[2], ft_strlen(argv[2]) + ft_strlen(argv[1]) + 2);
	ft_strlcat(temparg, " ", ft_strlen(argv[2]) + ft_strlen(argv[1]) + 2);
	ft_strlcat(temparg, argv[1], ft_strlen(argv[2]) + ft_strlen(argv[1]) + 2);
    char **args1 = ft_split(temparg, ' '); //{"ping", "-c", "5", "google.com", NULL};
	char *cmd1 = ft_strjoin(path, args1[0]);
	char *env_args1[] = {NULL};
	int fd[2];
	if (pipe(fd) == -1)
		return (perror("pipe error\n"), 1);
	int pid1 = fork();
	if (pid1 == -1)
		return (perror("fork error\n"), 2);
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (execve(cmd1, args1, env_args1))
		{
			perror("Execution Error\n");
			exit(EXIT_FAILURE);
		}
	}
	free_arr(args1);
	free(cmd1);
	free(temparg);
	
	int pid2 = fork();
	if (pid2 == -1)
		return (perror("fork error\n"), 2);
	char **args2 = ft_split(argv[3], ' ');
    char *cmd2 = ft_calloc(ft_strlen(path) + ft_strlen(args2[0]) + 1, sizeof(char));
	ft_strlcpy(cmd2, path, ft_strlen(path) + ft_strlen(args2[0]) + 1);
    ft_strlcat(cmd2, args2[0], ft_strlen(path) + ft_strlen(args2[0]) + 1);
	char *env_args2[] = {NULL};
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (execve(cmd2, args2, env_args2))
		{
			perror("Execution Error");
			exit(EXIT_FAILURE);
		}
	}
	free_arr(args2);
	free(cmd2);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	ft_printf("Main program done\n");
    return 0;
}
