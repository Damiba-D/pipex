/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 09:53:36 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/21 15:17:06 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	cmd2_exit1(t_data cmd_data, int pipe[2], int arr_pos)
{
	perror(cmd_data.cmd_vars[arr_pos].file);
	closefds(pipe);
	free(cmd_data.cmd_vars);
	exit(1);
}

static void	cmd2_exit2(t_data cmd_data, int pipe[2], int arr_pos, int exit_code)
{
	close(cmd_data.cmd_vars[arr_pos].fd);
	closefds(pipe);
	free(cmd_data.cmd_vars);
	exit(exit_code);
}

static void	cmd2_exit3(t_data cmd_data, int pipe_r, int arr_pos, int dup_num)
{
	perror("child 2: dup2 error");
	cmd_clean(cmd_data.cmd_vars[arr_pos]);
	if (dup_num == 1)
		close(pipe_r);
	close(cmd_data.cmd_vars[arr_pos].fd);
	free(cmd_data.cmd_vars);
	exit(1);
}

static void	cmd2_open_mode(t_data *cmd_data, int arr_pos)
{
	if (cmd_data->h_d_mode == 0)
		cmd_data->cmd_vars[arr_pos].fd = \
open(cmd_data->cmd_vars[arr_pos].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		cmd_data->cmd_vars[arr_pos].fd = \
open(cmd_data->cmd_vars[arr_pos].file, O_WRONLY | O_CREAT | O_APPEND, 0644);
}

void	cmd2(t_data cmd_data, int pipe[2], int cmd_pos, int arr_pos)
{
	cmd_data.cmd_vars[arr_pos].pid = fork();
	if (cmd_data.cmd_vars[arr_pos].pid == -1)
		return (ft_putstr_fd("fork error\n", 2));
	if (cmd_data.cmd_vars[arr_pos].pid == 0)
	{
		cmd2_open_mode(&cmd_data, arr_pos);
		if (cmd_data.cmd_vars[arr_pos].fd < 0)
			cmd2_exit1(cmd_data, pipe, arr_pos);
		cmd_data.cmd_vars[arr_pos].create_flag = \
cmd_create(&cmd_data.cmd_vars[arr_pos], cmd_data.argv[cmd_pos], cmd_data.env);
		if (cmd_data.cmd_vars[arr_pos].create_flag)
			cmd2_exit2(cmd_data, pipe, arr_pos, \
cmd_data.cmd_vars[arr_pos].create_flag);
		if (dup2(pipe[0], STDIN_FILENO) == -1)
			cmd2_exit3(cmd_data, pipe[0], arr_pos, 1);
		close(pipe[0]);
		if (dup2(cmd_data.cmd_vars[arr_pos].fd, STDOUT_FILENO) == -1)
			cmd2_exit3(cmd_data, pipe[0], arr_pos, 2);
		close(cmd_data.cmd_vars[arr_pos].fd);
		exec_cmd(cmd_data, cmd_data.cmd_vars[arr_pos], cmd_data.env);
	}
}
