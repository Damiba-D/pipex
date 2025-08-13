/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:07:02 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/13 23:10:29 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*get_env_var(char *name, char **env)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*find_command(char *cmd, char **env)
{
	t_search_vars	vars;
	char			*temp;

	vars.path_env = get_env_var("PATH", env);
	if (!vars.path_env)
		return (NULL);
	vars.dirs = ft_split(vars.path_env, ':');
	vars.full_path = NULL;
	vars.i = 0;
	while (vars.dirs[vars.i])
	{
		temp = ft_strjoin(vars.dirs[vars.i], "/");
		vars.full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(vars.full_path, X_OK) == 0)
		{
			free_arr(vars.dirs);
			return (vars.full_path);
		}
		free(vars.full_path);
		vars.i++;
	}
	free_arr(vars.dirs);
	return (NULL);
}

void	closefds(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}

int	cmd_create(t_cmd *cmd_s, char *cmd_args, char **env)
{
	cmd_s->args = ft_split(cmd_args, ' ');
	if (cmd_s->args == NULL)
		return (ft_putstr_fd("Malloc Error\n", 2), 0);
	cmd_s->cmd = find_command(cmd_s->args[0], env);
	if (!cmd_s->cmd)
		return (perror(cmd_s->args[0]), free_arr(cmd_s->args), 0);
	return (1);
}
void	cmd_clean(t_cmd cmd)
{
	free_arr(cmd.args);
	free(cmd.cmd);
}

void	exec_cmd(t_cmd cmd, char **env)
{
	if (execve(cmd.cmd, cmd.args, env) == -1)
	{
		perror("Execution Error");
		cmd_clean(cmd);
		exit(EXIT_FAILURE);
	}
}

void	clean_type_1(char *file, t_cmd cmd_s, int pipefd[2])
{
	cmd_clean(cmd_s);
	closefds(pipefd);
	perror(file);
}
void closed(int fd)
{
	close(fd);
}

void	cmd1(t_cmd *cmd_vars, int pipe[2], char *cmd_args, char **env)
{
	
	cmd_vars->pid = fork();
	if (cmd_vars->pid == -1)
		return (ft_putstr_fd("fork error\n", 2));
	if (cmd_vars->pid == 0)
	{
		if (access(cmd_vars->file, R_OK) == -1)
		{
			perror(cmd_vars->file);
			exit(EXIT_FAILURE);
		}
		if (!cmd_create(cmd_vars, cmd_args, env))
			exit(127);
		cmd_vars->fd = open(cmd_vars->file, O_RDONLY);
		if (cmd_vars->fd < 0)
			return (clean_type_1(cmd_vars->file, *cmd_vars, pipe));
		close(pipe[0]);
		if (dup2(cmd_vars->fd, STDIN_FILENO) == -1)
			return (perror("child 1: dup2 error"), cmd_clean(*cmd_vars), closed(pipe[1]), closed(cmd_vars->fd));
		close(cmd_vars->fd);
		if (dup2(pipe[1], STDOUT_FILENO) == -1)
			return (perror("child 1: dup2 error"), cmd_clean(*cmd_vars), closed(pipe[1]));
		close(pipe[1]);
		exec_cmd(*cmd_vars, env);
	}
}

void	cmd_mid(t_cmd *cmd_vars, int pipes[2][2], char *cmd_args, char **env)
{
	cmd_vars->pid = fork();
	if (cmd_vars->pid == -1)
		return (ft_putstr_fd("fork error\n", 2));
	if (cmd_vars->pid == 0)
	{
		if (!cmd_create(cmd_vars, cmd_args, env))
			return (closefds(pipes[0]), closefds(pipes[1]), exit(127));
		if (dup2(pipes[0][0], STDIN_FILENO) == -1)
			return (perror("child mid: dup2 error"), cmd_clean(*cmd_vars), closed(pipes[0][0]), closed(cmd_vars->fd));
		close(pipes[0][0]);
		close(pipes[1][0]);
		if (dup2(pipes[1][1], STDOUT_FILENO) == -1)
			return (perror("child mid: dup2 error"), cmd_clean(*cmd_vars), closed(pipes[1][1]));
		close(pipes[1][1]);
		exec_cmd(*cmd_vars, env);
	}
}

void	cmd2(t_cmd *cmd_vars, int pipe[2], char *cmd_args, char **env)
{
	cmd_vars->pid = fork();
	if (cmd_vars->pid == -1)
		return (ft_putstr_fd("fork error\n", 2));
	if (cmd_vars->pid == 0)
	{
		cmd_vars->fd = open(cmd_vars->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd_vars->fd < 0)
			return (perror(cmd_vars->file), closefds(pipe));
		if (!cmd_create(cmd_vars, cmd_args, env))
			return (close(cmd_vars->fd), closefds(pipe), exit(127));
		if (dup2(pipe[0], STDIN_FILENO) == -1)
			return (perror("child 2: dup2 error"), cmd_clean(*cmd_vars), closed(pipe[0]), closed(cmd_vars->fd));
		close(pipe[0]);
		if (dup2(cmd_vars->fd, STDOUT_FILENO) == -1)
			return (perror("child 2: dup2 error"), cmd_clean(*cmd_vars), closed(cmd_vars->fd));
		close(cmd_vars->fd);
		exec_cmd(*cmd_vars, env);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_cmd	cmd_vars[argc - 3];
	int		fd[2][2];
	int		i;
	int		j;

	if (argc < 5)
		return (ft_putstr_fd("Insufficient args\n", 2), -1);
	if (pipe(fd[0]) == -1)
		return (ft_putstr_fd("pipe error\n", 2), 1);
	cmd_vars[0].file = argv[1];
	cmd1(&cmd_vars[0], fd[0], argv[2], env);
	if (cmd_vars[0].pid == 0)
		exit(EXIT_FAILURE);
	if (cmd_vars[0].pid > 0)
		close(fd[0][1]);
	i = 3;
	while(i < argc - 2)
    {
        // Create next pipe
        if (pipe(fd[1]) == -1)
            return (ft_putstr_fd("pipe error\n", 2), 1);

        cmd_mid(&cmd_vars[i - 2], fd, argv[i], env);
		if (cmd_vars[i - 2].pid == 0)
			exit(EXIT_FAILURE);

        // Close the previous pipe in the parent
        close(fd[0][0]);
    	close(fd[1][1]);

        // Rotate: next pipe becomes previous
        fd[0][0] = fd[1][0];
        fd[0][1] = fd[1][1];
		i++;
    }
	cmd_vars[i - 2].file = argv[argc - 1];
	cmd2(&cmd_vars[i - 2], fd[0], argv[argc - 2], env);
	if (cmd_vars[i - 2].pid == 0)
		exit(EXIT_FAILURE);
	if (cmd_vars[i - 2].pid > 0)
		closefds(fd[0]);
	j = i - 2;
	while (j >= 0)
	{
		waitpid(cmd_vars[j].pid, NULL, 0);
		j--;
	}
	ft_printf("Main Program done\n");
	return (0);
}
