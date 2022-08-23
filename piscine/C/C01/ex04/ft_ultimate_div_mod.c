/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_div_mod.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:11:24 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/15 20:12:00 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

void	ft_ultimate_div_mod(int *a, int *b)
{
	int	a1;
	int	b1;

	a1 = *a;
	b1 = *b;
	*a = a1 / b1;
	*b = a1 % b1;
}
/*
int main()
{
	int a = 92;
	int b = 30;

	ft_ultimate_div_mod(&a , &b);
}
*/