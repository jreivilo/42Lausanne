/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 17:24:53 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/17 17:24:54 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

int	ft_str_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == 0)
	{
		return (1);
	}
	while (str[i] != '\0')
	{
		if ('0' > str[i] || str[i] > '9')
		{
			return (0);
		}
		i++;
	}
	return (1);
}
/*
int main()
{
	char c;
	int a;
	a = ft_str_is_numeric("5465");
	printf("%i", a);
	write(1, "\n", 1);
}
*/
