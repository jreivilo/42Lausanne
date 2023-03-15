/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:09:46 by jolivier          #+#    #+#             */
/*   Updated: 2023/02/09 11:09:46 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_bash
{
	int		fd[2];
	int		in_fd;
	int		out_fd;
	int		tmp_fd;
	int		hrdc;
	char	*input;
	char	**env;
	pid_t	pid;
}	t_bash;
void	check_fd(t_bash *bash);

int		pipe_exec(t_tree *tree, t_bash *bash);
int		start_exec(t_tree *tree, t_bash *bash);

int		built_in(t_builtin *builtin, char ***env, t_bash *bash);
int		cmd(t_cmd *cmd, t_bash *bash);

void	lst_built_in(t_builtin *builtin, t_bash *bash);
void	all_built_in(t_builtin *builtin, t_bash *bash);

void	lst_cmd(t_cmd *cmd, t_bash *bash);
void	all_cmd(t_cmd *cmd, t_bash *bash);

int		redir_right(t_tree *tree, t_bash *bash);
int		redir_double_right(t_tree *tree, t_bash *bash);

int		redir_double_left(t_tree *tree, t_bash *bash);
int		redir_left(t_tree *tree, t_bash *bash);

void	close_files(t_bash *bash);
void	close_files_first_cmd(t_bash *bash);
int		redir_double_left_signal(t_tree *tree, t_bash *bash, int status);

void	child_process(t_bash *bash, char *path_cmd, t_cmd *cmd);
int		pick_buildin(t_builtin *builtin, char ***env);

#endif