/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 20:03:03 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/18 20:03:09 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (to_find[0] == '\0')
	{
		return (str);
	}
	while (str[i] != '\0')
	{
		while (str[i + n] == to_find[n])
		{
			if (to_find[n + 1] == '\0')
			{
				return (str + i);
			}
		n++;
		}
		n = 0;
		i++;
	}
	return ((void *)0);
}
/*
int main(void)
{
	char a[50] = "Telelebies";
	char b[50] = "e";
	printf("%s\n", ft_strstr(a, b));
	char c[50] = "Telelebies";
	char d[50] = "e";
	printf("%s\n", strstr(c, d));
}
*/
/*
This function returns a pointer to the first occurrence in haystack of any of 
the entire sequence of characters specified in needle, or a null pointer if 
the sequence is not present in haystack.
*/