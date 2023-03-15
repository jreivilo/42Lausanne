/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:27:04 by jolivier          #+#    #+#             */
/*   Updated: 2023/01/13 13:27:04 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **args)
{
	int	i;

	i = 0;
	if (args[1] == NULL)
		exit(0);
	if (args[2] != NULL)
		return (ft_exit_error(args));
	while (args[1][i])
	{
		if (ft_isdigit(args[1][i]) == 0)
		{
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n", args[1]);
			g_status = 255;
			return (g_status);
		}
		i++;
	}
	g_status = ft_atoi(args[1]);
	exit(g_status);
	return (g_status);
}

int	ft_exit_error(char **args)
{
	(void)args;
	printf("exit\n");
	printf("minishell: exit: too many arguments\n");
	g_status = 255;
	return (g_status);
}
