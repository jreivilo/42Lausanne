/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:53:56 by jolivier          #+#    #+#             */
/*   Updated: 2022/11/10 17:48:00 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

void	error(char *str);

char	*ft_only_cmd(char *cmd, char c);
char	*real_path_cmd(char *only_cmd, char **path_tab);
char	*find_cmd(char *cmd, char **envp);

void	split_free(char **split);

#endif
