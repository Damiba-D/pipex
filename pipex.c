/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:07:02 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/15 20:45:27 by ddamiba          ###   ########.fr       */
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

void	exec_cmd(t_data cmd_data, t_cmd cmd, char **env)
{
	if (execve(cmd.cmd, cmd.args, env) == -1)
	{
		perror("Execution Error");
		cmd_clean(cmd);
		free(cmd_data.cmd_vars);
		exit(EXIT_FAILURE);
	}
}

void	cmd1_exit1(t_data cmd_data, int pipe[2], int exit_code)
{
	perror(cmd_data.cmd_vars[0].file);
	closefds(pipe);
	free(cmd_data.cmd_vars);
	exit(exit_code);
}

void	cmd1_exit2(t_data cmd_data, int pipe[2])
{
	perror(cmd_data.cmd_vars[0].file);
	cmd_clean(cmd_data.cmd_vars[0]);
	closefds(pipe);
	free(cmd_data.cmd_vars);
	exit(EXIT_FAILURE);
}

void	cmd1_exit3(t_data cmd_data, int pipe[2], int dup_num)
{
	perror("child 1: dup2 error");
	cmd_clean(cmd_data.cmd_vars[0]);
	close(pipe[1]);
	if (dup_num == 1)
		close(cmd_data.cmd_vars[0].fd);
	free(cmd_data.cmd_vars);
	exit(EXIT_FAILURE);
}

void	cmd1(t_data cmd_data, int pipe[2], int cmd_pos)
{
	cmd_data.cmd_vars->pid = fork();
	if (cmd_data.cmd_vars->pid == -1)
		return (ft_putstr_fd("fork error\n", 2));
	if (cmd_data.cmd_vars->pid == 0)
	{
		if (access(cmd_data.cmd_vars[0].file, R_OK) == -1)
			cmd1_exit1(cmd_data, pipe, EXIT_FAILURE);
		if (!cmd_create(&cmd_data.cmd_vars[0], \
cmd_data.argv[cmd_pos], cmd_data.env))
			cmd1_exit1(cmd_data, pipe, 127);
		cmd_data.cmd_vars[0].fd = open(cmd_data.cmd_vars[0].file, O_RDONLY);
		if (cmd_data.cmd_vars[0].fd < 0)
			cmd1_exit2(cmd_data, pipe);
		close(pipe[0]);
		if (dup2(cmd_data.cmd_vars[0].fd, STDIN_FILENO) == -1)
			cmd1_exit3(cmd_data, pipe, 1);
		close(cmd_data.cmd_vars[0].fd);
		if (dup2(pipe[1], STDOUT_FILENO) == -1)
			cmd1_exit3(cmd_data, pipe, 2);
		close(pipe[1]);
		exec_cmd(cmd_data, cmd_data.cmd_vars[0], cmd_data.env);
	}
}

void	cmdmid_exit1(t_data cmd_data, int pipes[2][2])
{
	closefds(pipes[0]);
	closefds(pipes[1]);
	free(cmd_data.cmd_vars);
	exit(127);
}

void	cmdmid_exit2(t_data cmd_data, int pipes[2][2], int arr_pos)
{
	perror("child mid: dup2 error");
	cmd_clean(cmd_data.cmd_vars[arr_pos]);
	close(pipes[0][0]);
	closefds(pipes[1]);
	close(cmd_data.cmd_vars[arr_pos].fd);
	free(cmd_data.cmd_vars);
	exit(1);
}

void	cmdmid_exit3(t_data cmd_data, int pipe_w, int arr_pos)
{
	perror("child mid: dup2 error");
	cmd_clean(cmd_data.cmd_vars[arr_pos]);
	close(pipe_w);
	free(cmd_data.cmd_vars);
	exit(1);
}

void	cmd_mid(t_data cmd_data, int pipes[2][2], int cmd_pos, int arr_pos)
{
	cmd_data.cmd_vars[arr_pos].pid = fork();
	if (cmd_data.cmd_vars[arr_pos].pid == -1)
		return (ft_putstr_fd("fork error\n", 2));
	if (cmd_data.cmd_vars[arr_pos].pid == 0)
	{
		if (!cmd_create(&cmd_data.cmd_vars[arr_pos], \
cmd_data.argv[cmd_pos], cmd_data.env))
			cmdmid_exit1(cmd_data, pipes);
		if (dup2(pipes[0][0], STDIN_FILENO) == -1)
			cmdmid_exit2(cmd_data, pipes, arr_pos);
		close(pipes[0][0]);
		close(pipes[1][0]);
		if (dup2(pipes[1][1], STDOUT_FILENO) == -1)
			cmdmid_exit3(cmd_data, pipes[1][1], arr_pos);
		close(pipes[1][1]);
		exec_cmd(cmd_data, cmd_data.cmd_vars[arr_pos], cmd_data.env);
	}
}

void	cmd2_exit1(t_data cmd_data, int pipe[2], int arr_pos)
{
	perror(cmd_data.cmd_vars[arr_pos].file);
	closefds(pipe);
	free(cmd_data.cmd_vars);
	exit(1);
}

void	cmd2_exit2(t_data cmd_data, int pipe[2], int arr_pos)
{
	close(cmd_data.cmd_vars[arr_pos].fd);
	closefds(pipe);
	free(cmd_data.cmd_vars);
	exit(127);
}

void	cmd2_exit3(t_data cmd_data, int pipe_r, int arr_pos, int dup_num)
{
	perror("child 2: dup2 error");
	cmd_clean(cmd_data.cmd_vars[arr_pos]);
	if (dup_num == 1)
		close(pipe_r);
	close(cmd_data.cmd_vars[arr_pos].fd);
	free(cmd_data.cmd_vars);
	exit(1);
}

void	cmd2(t_data cmd_data, int pipe[2], int cmd_pos, int arr_pos)
{
	cmd_data.cmd_vars[arr_pos].pid = fork();
	if (cmd_data.cmd_vars[arr_pos].pid == -1)
		return (ft_putstr_fd("fork error\n", 2));
	if (cmd_data.cmd_vars[arr_pos].pid == 0)
	{
		cmd_data.cmd_vars[arr_pos].fd = open(cmd_data.cmd_vars[arr_pos].file, \
O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd_data.cmd_vars[arr_pos].fd < 0)
			cmd2_exit1(cmd_data, pipe, arr_pos);
		if (!cmd_create(&cmd_data.cmd_vars[arr_pos], \
cmd_data.argv[cmd_pos], cmd_data.env))
			cmd2_exit2(cmd_data, pipe, arr_pos);
		if (dup2(pipe[0], STDIN_FILENO) == -1)
			cmd2_exit3(cmd_data, pipe[0], arr_pos, 1);
		close(pipe[0]);
		if (dup2(cmd_data.cmd_vars[arr_pos].fd, STDOUT_FILENO) == -1)
			cmd2_exit3(cmd_data, pipe[0], arr_pos, 2);
		close(cmd_data.cmd_vars[arr_pos].fd);
		exec_cmd(cmd_data, cmd_data.cmd_vars[arr_pos], cmd_data.env);
	}
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

int	exec_mid(t_data cmd_data, int pipes[2][2], int argc)
{
	int	i;

	i = 3;
	while (i < argc - 2)
	{
		if (pipe(pipes[1]) == -1)
			return (ft_putstr_fd("pipe error\n", 2), 1);
		cmd_mid(cmd_data, pipes, i, i - 2);
		close(pipes[0][0]);
		close(pipes[1][1]);
		pipes[0][0] = pipes[1][0];
		pipes[0][1] = pipes[1][1];
		i++;
	}
	return (i);
}

int	main(int argc, char **argv, char **env)
{
	t_data		cmd_data;
	int			fd[2][2];
	int			i;

	if (argc < 5)
		return (ft_putstr_fd("Insufficient args\n", 2), -1);
	cmd_data.cmd_vars = malloc(sizeof(t_cmd) * (argc - 3));
	if (cmd_data.cmd_vars == NULL)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	if (pipe(fd[0]) == -1)
		return (ft_putstr_fd("pipe error\n", 2), 1);
	cmd_data.argv = argv;
	cmd_data.env = env;
	cmd_data.cmd_vars[0].file = argv[1];
	cmd1(cmd_data, fd[0], 2);
	close(fd[0][1]);
	i = exec_mid(cmd_data, fd, argc);
	cmd_data.cmd_vars[i - 2].file = argv[argc - 1];
	cmd2(cmd_data, fd[0], argc - 2, i - 2);
	closefds(fd[0]);
	parent_exit(i - 2, cmd_data.cmd_vars[i - 2].pid, cmd_data.cmd_vars);
	return (1);
}
