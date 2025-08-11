/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:53:49 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/11 10:35:01 by ddamiba          ###   ########.fr       */
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

char *get_env_var(char *name, char **env)
{
    int i;
    size_t len;

	i = 0;
	len = ft_strlen(name);
    while (env[i])
    {
        if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
            return (env[i] + len + 1); // skip NAME=
        i++;
    }
    return (NULL); // not found
}

char *find_command(char *cmd, char **env)
{
	//t_search_vars vars;
    char *path_env = get_env_var("PATH", env);
	if (!path_env) return NULL;
    char **dirs = ft_split(path_env, ':'); // from your libft
    char *full_path;
    int i = 0;
	

    while (dirs[i])
    {
        char *temp = ft_strjoin(dirs[i], "/");
        full_path = ft_strjoin(temp, cmd);
        free(temp);

        if (access(full_path, X_OK) == 0) // Found executable
        {
            free_arr(dirs);
            return full_path; // Caller frees
        }
        free(full_path);
        i++;
    }
    free_arr(dirs);
    return NULL; // Not found
}

int cmd1_init(t_cmd *cmd_s, char *cmd_args, char *file, char **env)
{
	cmd_s->args = ft_split(cmd_args, ' ');
	if (cmd_s->args == NULL)
		return(ft_putstr_fd("Malloc Error\n", 2), 1);
	cmd_s->cmd = find_command(cmd_s->args[0], env);
	if (!cmd_s->cmd)
    	return(perror(cmd_s->cmd), 2);
	cmd_s->pid = fork();
	if (cmd_s->pid == -1)
		return (ft_putstr_fd("fork error\n", 2), 3);
	else if (cmd_s->pid == 0)
	{
		cmd_s->file_fd = open(file, O_RDONLY);
    	if (cmd_s->file_fd < 0)
		{
        	return(perror(file), 4);
		}
		if (dup2(cmd_s->file_fd, STDIN_FILENO) == -1)
			return(ft_putstr_fd("FDs FULL\n", 2), 5);
		if (dup2(cmd_s->fd[1], STDOUT_FILENO) == -1)
			return(ft_putstr_fd("FDs FULL\n", 2), 6);
		close(cmd_s->file_fd);
		close(cmd_s->fd[0]);
		close(cmd_s->fd[1]);
	}
	return (0);
}

int cmd2_init(t_cmd *cmd_s, char *cmd_args, char *file, char **env)
{
	cmd_s->args = ft_split(cmd_args, ' ');
	if (cmd_s->args == NULL)
		return(ft_putstr_fd("Malloc Error\n", 2), 1);
	cmd_s->cmd = find_command(cmd_s->args[0], env);
	if (!cmd_s->cmd)
    	return(perror(cmd_s->cmd), 2);
	cmd_s->pid = fork();
	if (cmd_s->pid == -1)
		return (ft_putstr_fd("fork error\n", 2), 3);
	else if (cmd_s->pid == 0)
	{
		cmd_s->file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    	if (cmd_s->file_fd < 0)
		{
        	return(perror(file), 4);
		}
		if (dup2(cmd_s->fd[0], STDIN_FILENO) == -1)
			return(ft_putstr_fd("FDs FULL\n", 2), 5);
		if (dup2(cmd_s->file_fd, STDOUT_FILENO) == -1)
			return(ft_putstr_fd("FDs FULL\n", 2), 6);
		close(cmd_s->file_fd);
		close(cmd_s->fd[0]);
		close(cmd_s->fd[1]);
	}
	return (0);
}

int main(int argc, char **argv, char **env)
{
	t_cmd cmd_vars;
	if (argc < 5)
		return(perror("Insufficient args"), -1);
	if (pipe(cmd_vars.fd) == -1)
		return (ft_putstr_fd("pipe error\n", 2), 1);
	if (access(argv[1], R_OK) == 0)
	{
		cmd1_init(&cmd_vars, argv[2], argv[1], env);
		if (cmd_vars.pid == 0)
		{
			if (execve(cmd_vars.cmd, cmd_vars.args, env))
			{
				perror("Execution Error\n");
				exit(EXIT_FAILURE);
			}
		}
		free_arr(cmd_vars.args);
		free(cmd_vars.cmd);
	}
	else
		perror(argv[1]);
	cmd2_init(&cmd_vars, argv[3], argv[4], env);
	if (cmd_vars.pid == 0)
	{
		if (execve(cmd_vars.cmd, cmd_vars.args, env))
		{
			perror("Execution Error");
			exit(EXIT_FAILURE);
		}
	}
	free_arr(cmd_vars.args);
	free(cmd_vars.cmd);
	close(cmd_vars.fd[0]);
	close(cmd_vars.fd[1]);
	wait(NULL);
	ft_printf("Main program done\n");
    return 0;
}
