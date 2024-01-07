/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:30:33 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/14 21:35:33 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

enum
{
	NOPE = 0,
	BUILT_IN = 1,
	CMD = 2,
	FILES = 3,
	OUT_FILE = 4,
	APPEND = 5,
	IN_FILE = 7,
	HR_DC = 8,
	PIPE = 10,
	OR = 12,
	AND = 13,
	ANDOR = 14,
};

typedef struct s_tree
{
	char			*input;
	void			*type;
	int				token;
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*father;
}		t_tree;

typedef struct s_cmd
{
	char		*cmd;
	char		**args;
}		t_cmd;

typedef struct s_builtin
{
	char		*cmd;
	char		**args;
}		t_builtin;

typedef struct s_file
{
	char		*file;
}		t_file;

typedef struct s_error
{
	char		*cmd;
	char		**args;
}		t_error;

int		precedence(char *line, int *prcdnc);
void	set_variables_precedence(int *i, int *index, int *quote, int *prnths);
t_tree	*create_tree(void *token, t_tree *father);

void	increment_variables_preced(int *i, int *index, int **prcdnc, int tmp);

#endif