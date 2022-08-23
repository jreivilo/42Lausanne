/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 19:27:17 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/27 19:27:37 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_strcat(char **strs, int j, char *new, int t)
{
	int	i;

	i = 0;
	while (strs[j][i] != '\0')
	{
		new[t] = strs[j][i];
		t++;
		i++;
	}
	return (t);
}

int	ft_strcat_sep(char *sep, char *new, int t)
{
	int	i;

	i = 0;
	while (sep[i] != '\0')
	{
		new[t] = sep[i];
		t++;
		i++;
	}
	return (t);
}

int	ft_length(char **strs, char *sep, int size)
{
	int	i;
	int	j;
	int	length;

	j = 0;
	length = 0;
	while (j < size)
	{
		i = 0;
		while (strs[j][i] != '\0')
			i++;
		length = length + i;
		if (j < size - 1)
		{
			i = 0;
			while (sep[i] != '\0')
			{
				length++;
				i++;
			}
		}
	j++;
	}
	return (length);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	int		j;
	int		t;
	char	*new;

	j = 0;
	t = 0;
	if (size == 0)
	{
		new = malloc(sizeof(char) * 1);
		new[0] = '\0';
		return (new);
	}
	new = malloc(sizeof(char) * (ft_length(strs, sep, size) + 1));
	if (new == (void *)0)
		return (new);
	while (j < size)
	{
		t = ft_strcat(strs, j, new, t);
		if (j < size - 1)
			t = ft_strcat_sep(sep, new, t);
		j++;
	}
	new[t] = '\0';
	return (new);
}
/*
int main (int argc, char **argv)
{	
	(void)argc;
	char sep[] = "TTT";
	int size = 3;
	//char **src = NULL;
	//src[0] = "Test";
	//src[1] = "gdfg";
	printf("%s\n",ft_strjoin(size, argv, sep));
}
*/