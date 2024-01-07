/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 07:29:01 by jolivier          #+#    #+#             */
/*   Updated: 2023/01/13 07:29:01 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args, char **env)
{
	int	i;
	int	n_flag;

	(void)env;
	i = 1;
	n_flag = 0;
	if (args[1] == NULL)
		return (ft_echo_error(args));
	if (ft_strncmp(args[1], "-n", 2) == 0)
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", 1);
	g_status = 0;
	return (g_status);
}

int	ft_echo_error(char **args)
{
	(void)args;
	ft_putstr_fd("\n", 1);
	g_status = 0;
	return (g_status);
}
