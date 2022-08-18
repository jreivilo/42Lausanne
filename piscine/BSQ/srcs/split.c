/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hradoux <marvin@42lausannmarvin@42lausa    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:57:40 by hradoux           #+#    #+#             */
/*   Updated: 2022/08/01 17:39:19 by hradoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	cmp_c_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	nbr_strings(char *str, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && cmp_c_charset(str[i], charset))
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && !cmp_c_charset(str[i], charset))
			i++;
	}
	return (count);
}

int	size_str(char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && !cmp_c_charset(str[i], charset))
		i++;
	return (i);
}

char	*cpy_str(char *str, char *charset)
{
	char	*tab;
	int		i;

	tab = malloc((size_str(str, charset) + 1) * sizeof(char));
	if (!tab)
		return (0);
	i = 0;
	while (str[i] != '\0' && !cmp_c_charset(str[i], charset))
	{
		tab[i] = str [i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_split(char *str, char *charset)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	tab = malloc((nbr_strings(str, charset) + 1) * sizeof(char *));
	if (!tab)
		return (0);
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && cmp_c_charset(str[i], charset))
			i++;
		if (str[i] != '\0')
		{
			tab[j] = cpy_str(&str[i], charset);
			j++;
		}
		while (str[i] != '\0' && !cmp_c_charset(str[i], charset))
			i++;
	}
	tab[j] = 0;
	return (tab);
}
