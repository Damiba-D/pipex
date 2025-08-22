/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 09:49:34 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/22 16:24:58 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	cmdmid_exit1(t_data cmd_data, int pipes[2][2], int exit_code)
{
	closefds(pipes[0]);
	closefds(pipes[1]);
	free(cmd_data.cmd_vars);
	if (exit_code == 32)
		exit_code = 127;
	exit(exit_code);
}

static void	cmdmid_exit2(t_data cmd_data, int pipes[2][2], int arr_pos)
{
	perror("child mid: dup2 error");
	cmd_clean(cmd_data.cmd_vars[arr_pos]);
	close(pipes[0][0]);
	closefds(pipes[1]);
	free(cmd_data.cmd_vars);
	exit(1);
}

static void	cmdmid_exit3(t_data cmd_data, int pipe_w, int arr_pos)
{
	perror("child mid: dup2 error");
	cmd_clean(cmd_data.cmd_vars[arr_pos]);
	close(pipe_w);
	free(cmd_data.cmd_vars);
	exit(1);
}

static void	cmd_mid(t_data cmd_data, int pipes[2][2], int cmd_pos, int arr_pos)
{
	cmd_data.cmd_vars[arr_pos].pid = fork();
	if (cmd_data.cmd_vars[arr_pos].pid == -1)
		return (ft_putstr_fd("fork error\n", 2));
	if (cmd_data.cmd_vars[arr_pos].pid == 0)
	{
		cmd_data.cmd_vars[arr_pos].create_flag = \
cmd_create(&cmd_data.cmd_vars[arr_pos], cmd_data.argv[cmd_pos], cmd_data.env);
		if (cmd_data.cmd_vars[arr_pos].create_flag)
			cmdmid_exit1(cmd_data, pipes, \
cmd_data.cmd_vars[arr_pos].create_flag);
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

int	exec_mid(t_data cmd_data, int pipes[2][2], int argc)
{
	int	i;

	i = cmd_data.cmd1_pos + 1;
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
	return (0);
}
