/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:53:57 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/11 10:28:40 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
#include "libft/libft.h"
# include "libft/ft_printf/ft_printf.h"
# include "libft/get_next_line/get_next_line.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
typedef struct s_cmd
{
	char **args;
	char *cmd;
	int fd[2];
	int file_fd;
	int pid;
}	t_cmd;
typedef struct s_search_vars
{
	char *path_env;
	char **dirs;
	char *full_path;
	int	i;
}	t_search_vars;
#endif