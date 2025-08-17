/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:53:57 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/17 11:55:26 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include "libft/ft_printf/ft_printf.h"
# include "libft/get_next_line/get_next_line.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_cmd
{
	char	**args;
	char	*cmd;
	char	*file;
	int		fd;
	int		pid;
}	t_cmd;

typedef struct s_search_vars
{
	char	*path_env;
	char	**dirs;
	char	*full_path;
	int		i;
}	t_search_vars;

typedef struct s_mid_vars
{
	char	**argv;
	char	**env;
}	t_mid_vars;

typedef struct s_data
{
	t_cmd	*cmd_vars;
	char	**argv;
	char	**env;
}	t_data;

void	free_arr(char **arr);
void	closefds(int pipe[2]);
void	parent_exit(int i, int last_pid, t_cmd *cmd_vars);
char	*find_command(char *cmd, char **env);
int		cmd_create(t_cmd *cmd_s, char *cmd_args, char **env);
void	cmd_clean(t_cmd cmd);
void	exec_cmd(t_data cmd_data, t_cmd cmd, char **env);
void	cmd1(t_data cmd_data, int pipe[2], int cmd_pos);
int		exec_mid(t_data cmd_data, int pipes[2][2], int argc);
void	cmd2(t_data cmd_data, int pipe[2], int cmd_pos, int arr_pos);
#endif