/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:09:28 by jolivier          #+#    #+#             */
/*   Updated: 2023/02/09 11:09:28 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in(t_builtin *builtin, char ***env, t_bash *bash)
{
	if (bash != NULL && ft_strcmp(builtin->cmd, "exit") != 0
		&& ft_strcmp(builtin->cmd, "export") != 0
		&& ft_strcmp(builtin->cmd, "cd") != 0
		&& ft_strcmp(builtin->cmd, "unset") != 0)
	{
		bash->pid = fork();
		if (bash->pid == 0)
			child_process(bash, NULL, (t_cmd *)builtin);
		else
			waitpid(bash->pid, NULL, 0);
		return (0);
	}
	else
	{
		return (pick_buildin(builtin, env));
	}
}

void	check_fd(t_bash *bash)
{
	if (bash->in_fd != STDIN_FILENO)
	{
		dup2(bash->in_fd, STDIN_FILENO);
		close(bash->in_fd);
	}
	if (bash->out_fd != 1)
	{
		dup2(bash->out_fd, STDOUT_FILENO);
		close(bash->out_fd);
	}
}

void	child_process(t_bash *bash, char *path_cmd, t_cmd *cmd)
{
	tty_attribute(0);
	if (bash->hrdc)
	{
		dup2(*bash->fd, STDIN_FILENO);
		close(*bash->fd);
	}
	else
		dup2(bash->in_fd, STDIN_FILENO);
	dup2(bash->out_fd, STDOUT_FILENO);
	if (bash->in_fd > 2)
		close(bash->in_fd);
	if (bash->out_fd > 2)
		close(bash->out_fd);
	if (path_cmd == NULL)
	{
		built_in((t_builtin *)cmd, &bash->env, NULL);
		exit(1);
	}
	else if (execve(path_cmd, cmd->args, bash->env) == -1)
	{
		printf("Execve failed\n");
		exit(1);
	}
}

int	signal_check(int status)
{
	if (WIFSIGNALED(status))
	{
		g_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == 3)
		{
			printf("Quit : %d\n", status);
			return (ERROR);
		}
		else if (WTERMSIG(status) == 2)
		{
			printf("\n");
			return (SUCCESS);
		}
	}
	else if (WIFEXITED(status))
	{
		g_status = WEXITSTATUS(status);
		if (WEXITSTATUS(status))
			return (ERROR);
		return (SUCCESS);
	}
	return (99);
}

int	cmd(t_cmd *cmd, t_bash *bash)
{
	int		status;
	char	*path_cmd;

	path_cmd = get_path_cmd(cmd->cmd, bash->env);
	if (path_cmd == NULL)
	{
		error_path(cmd->cmd);
		return (ERROR);
	}
	bash->pid = fork();
	if (bash->pid == -1)
		printf("Fork failed\n");
	else if (!bash->pid)
		child_process(bash, path_cmd, cmd);
	waitpid(bash->pid, &status, 0);
	free(path_cmd);
	if (signal_check(status) == ERROR)
		return (ERROR);
	if (signal_check(status) == SUCCESS)
		return (SUCCESS);
	return (SUCCESS);
}
