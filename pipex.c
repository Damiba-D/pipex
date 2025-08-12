/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:25:18 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/12 13:28:19 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* 
After fork:
Parent id = (random)
Child id = 0 
*/

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

char	*get_env_var(char *name, char **env)
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

void	closefds(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}

int	cmd_create(t_cmd *cmd_s, char *cmd_args, char **env)
{
	cmd_s->args = ft_split(cmd_args, ' ');
	if (cmd_s->args == NULL)
		return (ft_putstr_fd("Malloc Error\n", 2), 0);
	cmd_s->cmd = find_command(cmd_s->args[0], env);
	if (!cmd_s->cmd)
		return (perror(cmd_s->args[0]), free_arr(cmd_s->args), 0);
	return (1);
}

void	cmd_clean(t_cmd cmd)
{
	free_arr(cmd.args);
	free(cmd.cmd);
}

void	clean_type_1(char *file, t_cmd cmd_s, int pipefd[2])
{
	cmd_clean(cmd_s);
	closefds(pipefd);
	perror(file);
}

void	cleanall(t_cmd cmd[2])
{
	cmd_clean(cmd[0]);
	cmd_clean(cmd[1]);
}

void	exec_cmd(t_cmd cmd, char **env)
{
	if (execve(cmd.cmd, cmd.args, env) == -1)
	{
		perror("Execution Error");
		cmd_clean(cmd);
		exit(EXIT_FAILURE);
	}
}

int	cmd1(t_cmd *cmd_s, int pipefd[2], char *file, char **env)
{
	int	filein;

	cmd_s->pid = fork();
	if (cmd_s->pid == -1)
		return (ft_putstr_fd("fork error\n", 2), 1);
	else if (cmd_s->pid == 0)
	{
		if (cmd_s->cmd == NULL)
			return (closefds(pipefd), 2);
		filein = open(file, O_RDONLY);
		if (filein < 0)
			return (clean_type_1(file, *cmd_s, pipefd), 3);
		close(pipefd[0]);
		if (dup2(filein, STDIN_FILENO) == -1)
			return (perror("dup2 error"), cmd_clean(*cmd_s), closefds(pipefd), close(filein), 4);
		close(filein);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (perror("dup2 error"),cmd_clean(*cmd_s), closefds(pipefd), close(filein), 5);
		close(pipefd[1]);
		exec_cmd(*cmd_s, env);
	}
	if (cmd_s->cmd != NULL)
		cmd_clean(*cmd_s);
	return (0);
}

int	cmd2(t_cmd *cmd_s, int pipefd[2], char *file, char **env)
{
	int	fileout;

	cmd_s->pid = fork();
	if (cmd_s->pid == -1)
		return (ft_putstr_fd("fork error\n", 2), 1);
	else if (cmd_s->pid == 0)
	{
		fileout = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fileout < 0)
			return (perror(file), cmd_clean(*cmd_s), closefds(pipefd), 2);
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			return (perror("dup2 error"), cmd_clean(*cmd_s), closefds(pipefd), close(fileout), 3);
		close(pipefd[0]);
		if (dup2(fileout, STDOUT_FILENO) == -1)
			return (perror("dup2 error"), cmd_clean(*cmd_s), closefds(pipefd), close(fileout), 4);
		close(fileout);
		exec_cmd(*cmd_s, env);
	}
	cmd_clean(*cmd_s);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_cmd	cmd_vars[2];
	int		fd[2];

	if (argc < 5)
		return (perror("Insufficient args"), -1);
	if (access(argv[1], R_OK) == 0)
		cmd_create(&cmd_vars[0], argv[2], env);
	else
	{
		cmd_vars[0].cmd = NULL;
		perror(argv[1]);
	}
	if (!cmd_create(&cmd_vars[1], argv[3], env))
		return (cmd_clean(cmd_vars[0]), 1);
	if (pipe(fd) == -1)
		return (ft_putstr_fd("pipe error\n", 2), 1);
	if(cmd1(&cmd_vars[0], fd, argv[1], env) && cmd_vars[0].pid == 0)
	{
		cmd_clean(cmd_vars[1]);
		exit(EXIT_FAILURE);
	}
	if(cmd2(&cmd_vars[1], fd, argv[4], env))
	{
		closefds(fd);
		exit(EXIT_FAILURE);
	}
	closefds(fd);
	waitpid(cmd_vars[1].pid, NULL, 0);
	waitpid(cmd_vars[0].pid, NULL, 0);
	if (cmd_vars[0].pid == 0)
		ft_printf("Child 1 program done\n");
	else if (cmd_vars[1].pid == 0)
		ft_printf("Child 2 program done\n");
	else
		ft_printf("Main Program done\n");
	return (0);
}
