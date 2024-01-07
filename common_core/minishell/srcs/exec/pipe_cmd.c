/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:33:50 by hradoux           #+#    #+#             */
/*   Updated: 2023/03/14 16:42:27 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup2_files(t_bash *bash)
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
}

void	dup2_first_cmd_files(t_bash *bash)
{
	if (bash->in_fd > 2)
		dup2(bash->in_fd, STDIN_FILENO);
	else
		dup2(bash->tmp_fd, STDIN_FILENO);
	if (bash->out_fd > 2)
		dup2(bash->out_fd, STDOUT_FILENO);
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
	{
		dup2_files(bash);
		close_files(bash);
		if (execve(path_cmd, cmd->args, bash->env) == -1)
		{
			printf("Execve failed\n");
			exit(1);
		}
	}
	close(bash->fd[1]);
	close(bash->tmp_fd);
	bash->tmp_fd = bash->fd[0];
	free(path_cmd);
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
		tty_attribute(0);
		dup2_first_cmd_files(bash);
		close_files_first_cmd(bash);
		if (execve(path_cmd, cmd->args, bash->env) == -1)
		{
			printf("Execve failed\n");
			exit(1);
		}
	}
	close(bash->tmp_fd);
	free(path_cmd);
}
