/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:25:51 by jolivier          #+#    #+#             */
/*   Updated: 2023/01/13 13:25:51 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_exists(char **env, char *arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arg[i] != '=' && arg[i] != '\0')
		i++;
	if (arg[i] == '\0')
		return (ERROR);
	while (env[j])
	{
		if (ft_strncmp(env[j], arg, i) == 0)
			return (j);
		j++;
	}
	return (ERROR);
}

char	**ft_add_env(char **env, char *arg)
{
	t_export	export;

	export.i = 0;
	export.j = 0;
	export.k = 0;
	while (arg[export.i] != '\0')
		export.i++;
	while (env[export.j])
		export.j++;
	if (arg_exists(env, arg) == ERROR)
		export.env_cpy = malloc(sizeof(char *) * (export.j + 2));
	else
		export.env_cpy = malloc(sizeof(char *) * (export.j + 1));
	export.j = 0;
	while (env[export.j])
	{
		export.env_cpy[export.j] = ft_strdup(env[export.j]);
		export.j++;
	}
	if (arg_exists(env, arg) != ERROR)
		ft_add_env2(&export, &arg, &env);
	return (ft_add_env1(&export, &arg, &env));
}

char	**ft_add_env1(t_export *data, char **args, char ***envs)
{
	t_export	export;
	char		*arg;
	char		**env;

	arg = *args;
	env = *envs;
	export = *data;
	export.env_cpy[export.j] = malloc(sizeof(char) * (export.i + 1));
	while (export.k < export.i)
	{
		export.env_cpy[export.j][export.k] = arg[export.k];
		export.k++;
	}
	export.env_cpy[export.j][export.k] = '\0';
	export.env_cpy[export.j + 1] = NULL;
	return (export.env_cpy);
}

char	**ft_add_env2(t_export *data, char **args, char ***envs)
{
	t_export	export;
	char		*arg;
	char		**env;

	export = *data;
	arg = *args;
	env = *envs;
	free(export.env_cpy[arg_exists(env, arg)]);
	export.env_cpy[arg_exists(env, arg)]
		= malloc(sizeof(char) * (export.i + 1));
	while (export.k < export.i)
	{
		export.env_cpy[arg_exists(env, arg)][export.k] = arg[export.k];
		export.k++;
	}
	export.env_cpy[arg_exists(env, arg)][export.k] = '\0';
	export.env_cpy[export.j] = NULL;
	return (export.env_cpy);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
