/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:40:42 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/25 17:40:43 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int	i;

	argc--;
	while (argc > 0)
	{
		i = 0;
		while (argv[argc][i] != '\0')
		{
			write(1, &argv[argc][i], 1);
			i++;
		}
		write(1, "\n", 1);
		argc--;
	}
	return (0);
}
