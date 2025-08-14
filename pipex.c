/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:07:02 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/14 19:40:07 by ddamiba          ###   ########.fr       */
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
	if (!cmd_args[0] || !cmd_args)
	{
		cmd_s->cmd = NULL;
		return (ft_putstr_fd("Empty args\n", 2), 0);
	}
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

int	cmd1(t_cmd *cmd_vars, int pipe[2], char *cmd_args, char **env)
{
	cmd_vars->pid = fork();
	if (cmd_vars->pid == -1)
		return (ft_putstr_fd("fork error\n", 2), 1);
	if (cmd_vars->pid == 0)
	{
		if (access(cmd_vars->file, R_OK) == -1)
			return (perror(cmd_vars->file), closefds(pipe), 1);
		if (!cmd_create(cmd_vars, cmd_args, env))
			return (closefds(pipe), 127);
		cmd_vars->fd = open(cmd_vars->file, O_RDONLY);
		if (cmd_vars->fd < 0)
			return (clean_type_1(cmd_vars->file, *cmd_vars, pipe), 1);
		close(pipe[0]);
		if (dup2(cmd_vars->fd, STDIN_FILENO) == -1)
			return (perror("child 1: dup2 error"), cmd_clean(*cmd_vars), close(pipe[1]), close(cmd_vars->fd), 1);
		close(cmd_vars->fd);
		if (dup2(pipe[1], STDOUT_FILENO) == -1)
			return (perror("child 1: dup2 error"), cmd_clean(*cmd_vars), close(pipe[1]), 1);
		close(pipe[1]);
		exec_cmd(*cmd_vars, env);
	}
	return (0);
}

int	cmd_mid(t_cmd *cmd_vars, int pipes[2][2], char *cmd_args, char **env)
{
	cmd_vars->pid = fork();
	if (cmd_vars->pid == -1)
		return (ft_putstr_fd("fork error\n", 2), 1);
	if (cmd_vars->pid == 0)
	{
		if (!cmd_create(cmd_vars, cmd_args, env))
			return (closefds(pipes[0]), closefds(pipes[1]), 127);
		if (dup2(pipes[0][0], STDIN_FILENO) == -1)
			return (perror("child mid: dup2 error"), cmd_clean(*cmd_vars), close(pipes[0][0]), close(cmd_vars->fd), 1);
		close(pipes[0][0]);
		close(pipes[1][0]);
		if (dup2(pipes[1][1], STDOUT_FILENO) == -1)
			return (perror("child mid: dup2 error"), cmd_clean(*cmd_vars), close(pipes[1][1]), 1);
		close(pipes[1][1]);
		exec_cmd(*cmd_vars, env);
	}
	return (0);
}

int	cmd2(t_cmd *cmd_vars, int pipe[2], char *cmd_args, char **env)
{
	cmd_vars->pid = fork();
	if (cmd_vars->pid == -1)
		return (ft_putstr_fd("fork error\n", 2), 1);
	if (cmd_vars->pid == 0)
	{
		cmd_vars->fd = open(cmd_vars->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd_vars->fd < 0)
			return (perror(cmd_vars->file), closefds(pipe), 1);
		if (!cmd_create(cmd_vars, cmd_args, env))
			return (close(cmd_vars->fd), closefds(pipe), 127);
		if (dup2(pipe[0], STDIN_FILENO) == -1)
			return (perror("child 2: dup2 error"), cmd_clean(*cmd_vars), close(pipe[0]), close(cmd_vars->fd), 1);
		close(pipe[0]);
		if (dup2(cmd_vars->fd, STDOUT_FILENO) == -1)
			return (perror("child 2: dup2 error"), cmd_clean(*cmd_vars), close(cmd_vars->fd), 1);
		close(cmd_vars->fd);
		exec_cmd(*cmd_vars, env);
	}
	return (0);
}

void	child_exit(t_cmd *cmd_vars, int exit_code)
{
	free(cmd_vars);
	exit(exit_code);
}

void	parent_exit(int i, int last_pid, t_cmd *cmd_vars)
{
	int		w_status;
	int		exit_code;
	pid_t	pid;

	while (i >= 0)
	{
		w_status = 0;
		pid = waitpid(cmd_vars[i].pid, &w_status, 0);
		if (pid == last_pid)
			exit_code = w_status;
		i--;
	}
	free(cmd_vars);
	if (WIFEXITED(exit_code))
		exit(WEXITSTATUS(exit_code));
	if (WIFSIGNALED(exit_code))
		exit(128 + WTERMSIG(exit_code));
}

int	exec_mid(t_mid_vars vars, int pipes[2][2], t_cmd *cmd_vars, int argc)
{
	int	i;
	int	exit_code;

	i = 3;
	while (i < argc - 2)
	{
		if (pipe(pipes[1]) == -1)
			return (ft_putstr_fd("pipe error\n", 2), 1);
		exit_code = cmd_mid(&cmd_vars[i - 2], pipes, vars.argv[i], vars.env);
		if (cmd_vars[i - 2].pid == 0)
			child_exit(cmd_vars, exit_code);
		close(pipes[0][0]);
		close(pipes[1][1]);
		pipes[0][0] = pipes[1][0];
		pipes[0][1] = pipes[1][1];
		i++;
	}
	return (i);
}

void	child1_cleanup(t_cmd *cmd_vars, int exit_code, int pipes[2][2])
{
	if (cmd_vars[0].pid == 0)
		child_exit(cmd_vars, exit_code);
	if (cmd_vars[0].pid > 0)
		close(pipes[0][1]);
}

void	child2_cleanup(t_cmd *cmd_vars, int exit_code, int pipes[2][2], int cmd_num)
{
	if (cmd_vars[cmd_num].pid == 0)
		child_exit(cmd_vars, exit_code);
	if (cmd_vars[cmd_num].pid > 0)
		closefds(pipes[0]);
}

int	main(int argc, char **argv, char **env)
{
	t_cmd		*cmd_vars;
	int			fd[2][2];
	int			i;
	int			exit_code;
	t_mid_vars	mid_vars;

	if (argc < 5)
		return (ft_putstr_fd("Insufficient args\n", 2), -1);
	cmd_vars = malloc(sizeof(t_cmd) * (argc - 3));
	if (cmd_vars == NULL)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	if (pipe(fd[0]) == -1)
		return (ft_putstr_fd("pipe error\n", 2), 1);
	cmd_vars[0].file = argv[1];
	exit_code = cmd1(&cmd_vars[0], fd[0], argv[2], env);
	child1_cleanup(cmd_vars, exit_code, fd);
	mid_vars.argv = argv;
	mid_vars.env = env;
	i = exec_mid(mid_vars, fd, cmd_vars, argc);
	cmd_vars[i - 2].file = argv[argc - 1];
	exit_code = cmd2(&cmd_vars[i - 2], fd[0], argv[argc - 2], env);
	child2_cleanup(cmd_vars, exit_code, fd, i - 2);
	parent_exit(i - 2, cmd_vars[i - 2].pid, cmd_vars);
	return (1);
}
