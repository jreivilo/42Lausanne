/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 17:51:59 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/24 17:52:01 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_recursive_power(int nb, int power)
{
	if (power == 0)
	{
		return (1);
	}
	if (power < 0)
	{
		return (0);
	}
	return (ft_recursive_power(nb, power - 1) * nb);
}
/*
int main()
{
	printf("RES:%i\n", ft_recursive_power(2, 3));
	return(0);
}
*/