/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:10:34 by jolivier          #+#    #+#             */
/*   Updated: 2022/09/13 13:10:34 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s != NULL && s[i] != 0)
	{
		if (s[i] != c)
		{
			word++;
			while (s[i] != c && s[i] != 0)
				i++;
		}
		else
			i++;
	}
	return (word);
}

static int	size(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != c && s[i] != 0)
	{
		size++;
		i++;
	}
	return (size);
}

static void	ft_free(char **strs, int j)
{
	while (j-- > 0)
		free(strs[j]);
	free(strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;
	int		word;
	int		j;

	i = 0;
	j = -1;
	word = count_word(s, c);
	strs = (char **)malloc((word + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	while (++j < word)
	{
		while (s[i] == c)
			i++;
		strs[j] = ft_substr(s, i, size(s, c, i));
		if (strs[j] == NULL)
		{
			ft_free(strs, j);
			return (NULL);
		}
		i = i + size(s, c, i);
	}
	strs[j] = 0;
	return (strs);
}
