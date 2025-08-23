/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 10:24:42 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/23 14:13:23 by ddamiba          ###   ########.fr       */
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

void	closefds(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}

void	cmd_clean(t_cmd cmd)
{
	free_arr(cmd.args);
	free(cmd.cmd);
}

void	parent_exit(int i, int last_pid, t_cmd *cmd_vars)
{
	int		w_status;
	int		exit_code;
	pid_t	pid;

	while (i >= 0)
	{
		w_status = 0;
		if (cmd_vars[i].pid > 0)
		{
			pid = waitpid(cmd_vars[i].pid, &w_status, 0);
			if (pid == last_pid)
				exit_code = w_status;
		}
		i--;
	}
	free(cmd_vars);
	if (WIFEXITED(exit_code))
		exit(WEXITSTATUS(exit_code));
	if (WIFSIGNALED(exit_code))
		exit(128 + WTERMSIG(exit_code));
}
