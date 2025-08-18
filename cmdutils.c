/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 10:19:36 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/18 18:04:32 by ddamiba          ###   ########.fr       */
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

int	cmd_create(t_cmd *cmd_s, char *cmd_args, char **env)
{
	if (!cmd_args[0] || !cmd_args)
	{
		cmd_s->cmd = NULL;
		return (ft_putstr_fd("Empty args\n", 2), 1);
	}
	cmd_s->args = ft_split(cmd_args, ' ');
	if (cmd_s->args == NULL)
		return (ft_putstr_fd("Malloc Error\n", 2), 1);
	cmd_s->cmd = find_command(cmd_s->args[0], env);
	if (!cmd_s->cmd)
	{
		if (access(cmd_s->args[0], F_OK) != 0)
			return (perror(cmd_s->args[0]), free_arr(cmd_s->args), 127);
		if (access(cmd_s->args[0], X_OK) == 0)
		{
			cmd_s->cmd = cmd_s->args[0];
			return (0);
		}
		return (perror(cmd_s->args[0]), free_arr(cmd_s->args), 126);
	}
	return (0);
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
