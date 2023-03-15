/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parsing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 18:42:27 by hradoux           #+#    #+#             */
/*   Updated: 2023/03/14 19:51:59 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SPACE 32
#define QUOTE 39
#define DQUOTE 34
#define BSLASH 92

int	ft_word_count_parse2(char const *s, char c)
{
	int	quote;
	int	word_count;

	quote = 0;
	word_count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			word_count++;
		while ((*s && *s != c) || (*s && quote))
		{
			if (*s == QUOTE || *s == DQUOTE)
			{
				if (!quote || quote == *s)
					quote = (quote - *s) * -1;
			}
			s++;
		}
	}
	return (word_count);
}

int	string_size_parse2(char const *s, char c)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while ((*s && *s != c) || (*s && quote))
	{
		if (*s == BSLASH && *(s + 1))
		{
			while (*s == BSLASH && *(s + 1))
			{
				i++;
				s++;
			}
			if (!*s || *s == c)
				break ;
		}
		else if (*s == QUOTE || *s == DQUOTE)
			quote_dquote_count(s, &quote, &i);
		else
			i++;
		s++;
	}
	return (i);
}

void	get_string_parse2(char **tmp, char const *s, char c)
{
	int	quote;

	quote = 0;
	while ((*s && *s != c) || (*s && quote))
	{
		if (*s == BSLASH && *(s + 1))
		{
			while (*s == BSLASH && *(s + 1))
			{
				s++;
				*((*tmp)++) = *s;
			}
			if (!*s || *s == c)
				break ;
		}
		else if (*s == QUOTE || *s == DQUOTE)
			quote_dquote(s, &quote, tmp);
		else
			*((*tmp)++) = *s;
		s++;
	}
}

char	*dup_string_parse2(char const *s, char c)
{
	char	*tmp;
	char	*tmp_start;

	tmp = ft_calloc(string_size_parse2(s, SPACE) + 1, sizeof(char));
	if (!tmp)
		return (0);
	tmp_start = tmp;
	get_string_parse2(&tmp, s, c);
	return (tmp_start);
}

char	**ft_split_parse2(char const *s, char c)
{
	int		word_count;
	char	**tmp;
	int		quote;

	ft_split_parse2a(&word_count, &tmp, s, c);
	quote = 0;
	while (*s)
	{
		while (*s && *s == SPACE)
			s++;
		if (*s)
			*tmp++ = dup_string_parse2(s, c);
		while ((*s && *s != c) || (*s && quote))
		{
			if (*s == QUOTE || *s == DQUOTE)
			{
				if (!quote || quote == *s)
					quote = (quote - *s) * -1;
			}
			s++;
		}
	}
	tmp -= word_count;
	return (tmp);
}
