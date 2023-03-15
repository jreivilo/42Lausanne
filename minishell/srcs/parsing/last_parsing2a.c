/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parsing2a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:27:37 by afrigger          #+#    #+#             */
/*   Updated: 2023/03/14 19:52:09 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	ft_split_parse2a(int *word_count, char ***tmp, const char *s, char c)
{
	*word_count = ft_word_count_parse2(s, c);
	*tmp = ft_calloc(*word_count + 1, sizeof(char *));
	if (!tmp)
		return ;
}

void	quote_dquote(char const *s, int *quote, char **tmp)
{
	if (!*quote || *quote == *s)
		*quote = (*quote - *s) * -1;
	if (*s != *quote && *quote)
		*((*tmp)++) = *s;
}

void	quote_dquote_count(char const *s, int *quote, int *i)
{
	if (!*quote || *quote == *s)
		*quote = (*quote - *s) * -1;
	if (*s != *quote && *quote)
		(*i)++;
}
