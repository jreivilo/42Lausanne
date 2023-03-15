/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 07:21:17 by jolivier          #+#    #+#             */
/*   Updated: 2023/01/13 07:21:17 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCCESS 0
# define ERROR -1

# define STDIN 0
# define STDOUT 1

# define SPACE 32
# define QUOTE 39
# define DQUOTE 34
# define BSLASH 92

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

# include "../libft/libft.h"
# include "ast.h"
# include "buildins.h"
# include "exec.h"
# include "free.h"
# include "parsing.h"
# include "utils.h"

int		g_status;
int			exec_tree(t_tree *tree, t_bash *bash);
void		all_cmd(t_cmd *cmd, t_bash *bash);
void		lst_cmd(t_cmd *cmd, t_bash *bash);
void		tree_main(t_tree *tree, t_bash *bash);
int			main_special_case(int argc);
void		main_special_case2(t_bash *bash);

#endif