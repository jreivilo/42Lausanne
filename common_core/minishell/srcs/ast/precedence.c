/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:02:53 by hradoux           #+#    #+#             */
/*   Updated: 2023/03/14 21:04:37 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	define_case_1(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (IN_FILE);
	else if (c == '>')
		return (OUT_FILE);
	else if (c == '&')
	{
		printf("2not_bash: syntax error near unexpected token `%c'\n", c);
		return (ERROR);
	}
	return (0);
}

int	define_case_2(char *line, char c)
{
	int	count;

	count = 0;
	while (*(line + count) == c)
		count++;
	if (count > 2)
	{
		printf("1not_bash: syntax error near unexpected token `%c'\n", c);
		return (ERROR);
	}
	else if (count == 2)
	{
		if (c == '|' || c == '&')
			return (ANDOR);
		else if (c == '<')
			return (HR_DC);
		else if (c == '>')
			return (APPEND);
	}
	else
		return (define_case_1(c));
	return (0);
}

/*			DEFINE_PRECEDENCE
 * 	Permet de savoir si le caractere donné est un && || ou |
 */

int	define_precedence(char *line)
{
	if (*line == '<' || *line == '>' || *line == '&' || *line == '|')
		return (define_case_2(line, *line));
	return (0);
}

/*			PRECEDENCE
 * 	Permet de trouver l'index du dernier operateur relationnel
 * 	a la precedence la plus haute.
 */

void	precedence_quote(char **line, int *i, int *quote)
{
	if (*i > 0)
	{
		if ((*(*line + *i) == 39 || (*(*line + *i) == 34 && *(*line + *i - 1) \
		!= 92)) && (!*quote || *quote == *(*line + *i)))
			*quote = (*quote - *(*line + *i)) * -1;
	}
}

int	precedence(char *line, int *prcdnc)
{
	int	i;
	int	tmp;
	int	quote;
	int	index;
	int	prnths;

	*prcdnc = 0;
	set_variables_precedence(&i, &index, &quote, &prnths);
	while (*(line + (++i)))
	{
		precedence_quote(&line, &i, &quote);
		if ((*(line + i) == '(' || *(line + i) == ')') && !quote)
			prnths += (41 - *(line + i)) * 2 - 1;
		tmp = define_precedence(line + i);
		if (tmp == -1)
			return (ERROR);
		if (!prnths && !quote && tmp)
		{
			if (*prcdnc <= tmp && (!(*prcdnc) || tmp > 9 || tmp - *prcdnc > 1))
				increment_variables_preced(&i, &index, &prcdnc, tmp);
		}
	}
	return (index);
}
