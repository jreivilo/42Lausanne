/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:45:24 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/18 18:45:58 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] && i + 1 < n)
	{
		i++;
	}
	if ((unsigned char) s1[i] == (unsigned char) s2[i])
	{
		return (0);
	}
	if ((unsigned char) s1[i] < (unsigned char) s2[i])
	{
		return (-1);
	}
	else
	{
		return (1);
	}
}
