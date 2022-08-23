/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:45:03 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/18 18:45:05 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	if (s1[i] == s2[i])
	{
		return (0);
	}
	if (s1[i] < s2[i])
	{
		return (-1);
	}
	if (s1[i] > s2[i])
	{
		return (1);
	}
	else
	{
		return (42);
	}
}
/*
int main()
{
    printf("Result:%i\n", ft_strcmp("efcadgf", "efb"));
	printf("Result:%i\n", strcmp("efcadfg", "efb"));
}
*/