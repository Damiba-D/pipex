/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 09:45:42 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/18 17:54:22 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	cmd1_exit1(t_data cmd_data, int pipe[2], int exit_code)
{
	if (exit_code == EXIT_FAILURE)
		perror(cmd_data.cmd_vars[0].file);
	closefds(pipe);
	free(cmd_data.cmd_vars);
	exit(exit_code);
}

static void	cmd1_exit2(t_data cmd_data, int pipe[2])
{
	perror(cmd_data.cmd_vars[0].file);
	cmd_clean(cmd_data.cmd_vars[0]);
	closefds(pipe);
	free(cmd_data.cmd_vars);
	exit(EXIT_FAILURE);
}

static void	cmd1_exit3(t_data cmd_data, int pipe[2], int dup_num)
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
		if (cmd_create(&cmd_data.cmd_vars[0], \
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
