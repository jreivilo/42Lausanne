/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:27:01 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/14 21:33:52 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	all_cmd_utils(t_cmd *cmd, t_bash *bash, char *path_cmd)
{
	tty_attribute(0);
	if (bash->in_fd > 2)
		dup2(bash->in_fd, STDIN_FILENO);
	else
		dup2(bash->tmp_fd, STDIN_FILENO);
	if (bash->out_fd > 2)
		dup2(bash->out_fd, STDOUT_FILENO);
	else
		dup2(*(bash->fd + 1), STDOUT_FILENO);
	if (bash->in_fd > 2)
		close(bash->in_fd);
	if (bash->out_fd > 2)
		close(bash->out_fd);
	close(bash->tmp_fd);
	close(*bash->fd);
	close(*(bash->fd + 1));
	if (execve(path_cmd, cmd->args, bash->env) == -1)
	{
		printf("Execve failed\n");
		exit(1);
	}
}

void	all_cmd(t_cmd *cmd, t_bash *bash)
{
	char	*path_cmd;

	path_cmd = get_path_cmd(cmd->cmd, bash->env);
	if (path_cmd == NULL)
	{
		error_path(cmd->cmd);
		return ;
	}
	bash->pid = fork();
	if (bash->pid == -1)
		printf("Fork failed\n");
	else if (!bash->pid)
		all_cmd_utils(cmd, bash, path_cmd);
	close(bash->fd[1]);
	close(bash->tmp_fd);
	bash->tmp_fd = bash->fd[0];
	free(path_cmd);
}

void	lst_cmd_utils(t_cmd *cmd, t_bash *bash, char *path_cmd)
{
	tty_attribute(0);
	if (bash->in_fd > 2)
		dup2(bash->in_fd, STDIN_FILENO);
	else
		dup2(bash->tmp_fd, STDIN_FILENO);
	if (bash->out_fd > 2)
		dup2(bash->out_fd, STDOUT_FILENO);
	if (bash->in_fd > 2)
		close(bash->in_fd);
	if (bash->out_fd > 2)
		close(bash->out_fd);
	close(bash->tmp_fd);
	if (execve(path_cmd, cmd->args, bash->env) == -1)
	{
		printf("Execve failed\n");
		exit(1);
	}
}

void	lst_cmd(t_cmd *cmd, t_bash *bash)
{
	char	*path_cmd;

	path_cmd = get_path_cmd(cmd->cmd, bash->env);
	if (path_cmd == NULL)
	{
		error_path(cmd->cmd);
		return ;
	}
	bash->pid = fork();
	if (bash->pid == -1)
		printf("Fork failed\n");
	else if (!bash->pid)
	{
		lst_cmd_utils(cmd, bash, path_cmd);
	}
	close(bash->tmp_fd);
	free(path_cmd);
}
