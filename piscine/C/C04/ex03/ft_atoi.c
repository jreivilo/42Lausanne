/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:59:22 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/21 15:29:20 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	int				i;
	unsigned int	diz;
	int				f;

	i = 0;
	diz = 1;
	f = 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		i++;
		diz = diz * 10;
	}
	return (diz / 10);
}

int	ft_atoi(char *str)
{
	int	i;
	int	j;
	int	sign;
	int	dizaine;

	i = 0;
	j = 0;
	sign = 1;
	dizaine = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	dizaine = ft_strlen(str + i);
	while (str[i] != '\0' && '0' <= str[i] && str[i] <= '9')
	{
		j = j + ((str[i] - '0') * dizaine);
		dizaine = dizaine / 10;
		i++;
	}
	return (j * sign);
}

/*
int main()
{
	printf("R1:%i\n", ft_atoi("   --+++123"));
	printf("R2:%i\n", atoi("+123"));
}
*/
