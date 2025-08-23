/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 10:19:36 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/23 14:13:15 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_env_var(char *name, char **env)
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

	vars.path_env = get_env_var("PATH", env);
	if (!vars.path_env)
		return (NULL);
	vars.dirs = ft_split(vars.path_env, ':');
	if (!vars.dirs)
		return (ft_putstr_fd("Malloc Error\n", 2), NULL);
	vars.i = 0;
	while (vars.dirs[vars.i])
	{
		vars.temp = ft_strjoin(vars.dirs[vars.i], "/");
		if (!vars.temp)
			break ;
		vars.full_path = ft_strjoin(vars.temp, cmd);
		free(vars.temp);
		if (!vars.full_path)
			break ;
		if (access(vars.full_path, X_OK) == 0)
			return (free_arr(vars.dirs), vars.full_path);
		free(vars.full_path);
		vars.full_path = NULL;
		vars.i++;
	}
	return (free_arr(vars.dirs), NULL);
}

int	cmd_create(t_cmd *cmd_s, char *cmd_args, char **env)
{
	if (!cmd_args || !cmd_args[0])
	{
		cmd_s->cmd = NULL;
		return (ft_putstr_fd("Empty args\n", 2), 1);
	}
	cmd_s->args = arg_split(cmd_args);
	if (cmd_s->args == NULL)
		return (ft_putstr_fd("Malloc Error\n", 2), 1);
	if (cmd_s->args[0] == NULL)
		return (free(cmd_s->args), 32);
	cmd_s->cmd = find_command(cmd_s->args[0], env);
	if (!cmd_s->cmd)
	{
		if (access(cmd_s->args[0], F_OK) != 0)
			return (perror(cmd_s->args[0]), free_arr(cmd_s->args), 127);
		if (access(cmd_s->args[0], X_OK) == 0)
		{
			cmd_s->cmd = ft_strdup(cmd_s->args[0]);
			if (!cmd_s->cmd)
				return (ft_putstr_fd("AllocE\n", 2), free_arr(cmd_s->args), 1);
			return (0);
		}
		return (perror(cmd_s->args[0]), free_arr(cmd_s->args), 126);
	}
	return (0);
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

int	h_d_handler(t_data cmd_data)
{
	char	*line;
	int		h_d_pipe[2];
	size_t	lim_len;
	size_t	line_len;

	if (pipe(h_d_pipe) == -1)
		return (ft_putstr_fd("pipe error\n", 2), -1);
	lim_len = ft_strlen(cmd_data.argv[2]);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line)
			line_len = ft_strlen(line);
		if (!line || \
(!ft_strncmp(line, cmd_data.argv[2], (lim_len)) && line_len - 1 == lim_len))
		{
			free(line);
			break ;
		}
		write(h_d_pipe[1], line, line_len);
		free(line);
	}
	close(h_d_pipe[1]);
	return (h_d_pipe[0]);
}
