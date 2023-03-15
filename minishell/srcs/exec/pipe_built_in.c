/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:53:08 by hradoux           #+#    #+#             */
/*   Updated: 2023/03/14 10:51:27 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_built_in(t_builtin *builtin, t_bash *bash)
{
	bash->pid = fork();
	if (bash->pid == -1)
		printf("Fork failed\n");
	else if (!bash->pid)
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
		if (built_in(builtin, &bash->env, NULL))
			exit(1);
		exit(0);
	}
	close(bash->tmp_fd);
}

void	close_files_builtins(t_bash *bash)
{
	if (bash->in_fd > 2)
		close(bash->in_fd);
	if (bash->out_fd > 2)
		close(bash->out_fd);
	close(bash->tmp_fd);
	close(*bash->fd);
	close(*(bash->fd + 1));
}

void	all_built_in(t_builtin *builtin, t_bash *bash)
{
	bash->pid = fork();
	if (bash->pid == -1)
		printf("Fork failed\n");
	else if (!bash->pid)
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
		close_files_builtins(bash);
		if (built_in(builtin, &bash->env, NULL))
			exit(1);
		exit(0);
	}
	close(bash->fd[1]);
	close(bash->tmp_fd);
	bash->tmp_fd = bash->fd[0];
}
