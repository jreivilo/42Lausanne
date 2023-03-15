/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:27:52 by jolivier          #+#    #+#             */
/*   Updated: 2023/01/13 13:27:52 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_var(char **env, int index)
{
	int	i;

	i = index;
	while (env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
}

int	ft_unset(char **args, char ***env)
{
	int		i;
	int		j;
	int		k;
	char	**new_env;

	new_env = *env;
	i = 1;
	while (args[i])
	{
		j = 0;
		while (new_env[j])
		{
			k = 0;
			while (new_env[j][k] != '=' && new_env[j][k] != '\0')
				k++;
			if (ft_strncmp(args[i], new_env[j], k) == 0)
			{
				remove_env_var(*env, j);
			}
			j++;
		}
		i++;
	}
	g_status = 0;
	return (g_status);
}
