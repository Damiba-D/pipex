/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:07:02 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/26 12:27:24 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parsing(t_data *cmd_data, int argc, char **argv, char **env)
{
	if (argc < 5)
	{
		ft_putstr_fd("Insufficient args\n", 2);
		exit(1);
	}
	cmd_data->cmd1_pos = 2;
	cmd_data->non_cmds = 3;
	cmd_data->h_d_mode = 0;
	cmd_data->argv = argv;
	cmd_data->env = env;
	if (argc < 6 && !ft_strncmp(argv[1], "here_doc", 9))
	{
		ft_putstr_fd("Insufficient args\n", 2);
		exit(1);
	}
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		cmd_data->cmd1_pos += 1;
		cmd_data->non_cmds += 1;
		cmd_data->h_d_mode = 1;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data		cmd_data;
	int			fd[2][2];
	int			arr_size;

	parsing(&cmd_data, argc, argv, env);
	arr_size = argc - cmd_data.non_cmds;
	cmd_data.cmd_vars = malloc(sizeof(t_cmd) * arr_size);
	if (cmd_data.cmd_vars == NULL)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	if (pipe(fd[0]) == -1)
		return (free(cmd_data.cmd_vars), ft_putstr_fd("pipe error\n", 2), 1);
	cmd_data.cmd_vars[0].file = argv[1];
	cmd1(cmd_data, fd[0]);
	close(fd[0][1]);
	if (exec_mid(cmd_data, fd, argc))
		return (free(cmd_data.cmd_vars), 1);
	cmd_data.cmd_vars[arr_size - 1].file = argv[argc - 1];
	cmd2(cmd_data, fd[0], argc - 2, arr_size - 1);
	closefds(fd[0]);
	parent_exit(arr_size - 1, \
cmd_data.cmd_vars[arr_size - 1].pid, cmd_data.cmd_vars);
	return (1);
}
