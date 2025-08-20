/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:07:02 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/20 22:27:47 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_data		cmd_data;
	int			fd[2][2];
	int			i;

	cmd_data.cmd1_pos = 2;
	cmd_data.non_cmds = 3;
	if (argc < 5)
		return (ft_putstr_fd("Insufficient args\n", 2), 1);
	cmd_data.cmd_vars = malloc(sizeof(t_cmd) * (argc - cmd_data.non_cmds));
	if (cmd_data.cmd_vars == NULL)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	if (pipe(fd[0]) == -1)
		return (ft_putstr_fd("pipe error\n", 2), 1);
	cmd_data.argv = argv;
	cmd_data.env = env;
	cmd_data.cmd_vars[0].file = argv[1];
	cmd1(cmd_data, fd[0]);
	close(fd[0][1]);
	i = exec_mid(cmd_data, fd, argc);
	cmd_data.cmd_vars[i - cmd_data.cmd1_pos].file = argv[argc - 1];
	cmd2(cmd_data, fd[0], argc - 2, i - cmd_data.cmd1_pos);
	closefds(fd[0]);
	parent_exit(i - cmd_data.cmd1_pos, cmd_data.cmd_vars[i - cmd_data.cmd1_pos].pid, cmd_data.cmd_vars);
	return (1);
}
