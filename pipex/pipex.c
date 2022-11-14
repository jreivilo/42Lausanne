/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:33:27 by jolivier          #+#    #+#             */
/*   Updated: 2022/11/11 13:44:03 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	child_process(int *fd, char **argv, char **envp)
{
	char	*path_cmd;
	char	**only_cmd;
	int		in_file_fd;

	in_file_fd = open(argv[1], O_RDONLY, 0777);
	if (access(argv[1], F_OK | R_OK) == -1)
		error("File not found");
	if (in_file_fd == -1)
		error("File not found");
	only_cmd = ft_split(argv[2], ' ');
	path_cmd = find_cmd(only_cmd[0], envp);
	if (path_cmd == NULL)
	{
		split_free(only_cmd);
		error("Command not found");
	}
	dup2(in_file_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	if (execve(path_cmd, only_cmd, envp) == -1)
		error("Execve failed");
}

void	parent_process(int *fd, char **argv, char **envp)
{
	char	*path_cmd;
	char	**only_cmd;
	int		out_file_fd;

	out_file_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (access(argv[4], F_OK | W_OK | X_OK) == -1)
		error("File not found");
	if (out_file_fd == -1)
		error("File not found");
	only_cmd = ft_split(argv[3], ' ');
	path_cmd = find_cmd(only_cmd[0], envp);
	dup2(fd[0], STDIN_FILENO);
	dup2(out_file_fd, STDOUT_FILENO);
	close(fd[1]);
	if (execve(path_cmd, only_cmd, envp) == -1)
		error("Execve failed");
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	fork_id;

	if (argc != 5)
		error("Wrong number of arguments");
	if (pipe(fd) == -1)
		error("Pipe error");
	fork_id = fork();
	if (fork_id == -1)
		error("Fork error");
	if (fork_id == 0)
		child_process(fd, argv, envp);
	parent_process(fd, argv, envp);
	waitpid(fork_id, NULL, 0);
	return (0);
}
