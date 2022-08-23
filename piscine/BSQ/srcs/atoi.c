/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hradoux <marvin@42lausannmarvin@42lausa    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:56:03 by hradoux           #+#    #+#             */
/*   Updated: 2022/08/03 11:11:43 by hradoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	ft_atoi(char *str, int nbr)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] >= 48 && str[i] <= 57 && i < nbr)
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
