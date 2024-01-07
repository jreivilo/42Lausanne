/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:22:14 by afrigger          #+#    #+#             */
/*   Updated: 2023/03/14 21:43:14 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char ***env, char **args)
{
	t_export	export;
	static char	**env_cpy2;

	export.i = 0;
	export.j = 1;
	if (env_cpy2 == NULL)
	{
		env_cpy2 = malloc(sizeof(char *) * 2);
		env_cpy2[0] = NULL;
		env_cpy2[1] = NULL;
	}
	if (args[export.j] != NULL)
	{
		ft_export4(&export, &args, &env, &env_cpy2);
	}
	else
		ft_export3(&env_cpy2, &env);
	g_status = 0;
	return (SUCCESS);
}

void	ft_export1(t_export *data, char ***arg, char ****envs, char ***env_cpy2)
{
	t_export	export;
	char		**args;
	char		***env;

	env = *envs;
	args = *arg;
	env = *envs;
	export = *data;
	export.tmp1 = ft_add_env(*env, export.new_arg);
	*env = export.tmp1;
	export.tmp_new_arg = add_double_quotes(export.new_arg);
	free(export.new_arg);
	export.new_arg = export.tmp_new_arg;
	export.tmp2 = ft_add_env(*env_cpy2, export.new_arg);
	free(*env_cpy2);
	*env_cpy2 = export.tmp2;
}

void	ft_export2(t_export *data, char ***env_cpy2)
{
	t_export	export;

	export = *data;
	export.tmp_arg = export.new_arg;
	export.tmp2 = ft_add_env(*env_cpy2, export.tmp_arg);
	free(export.tmp_arg);
	free(*env_cpy2);
	*env_cpy2 = export.tmp2;
}

void	ft_export3(char ***env_cpy2, char ****envs)
{
	char	***env;

	env = *envs;
	ft_print_tab_unique(sort_tab(*env), *env_cpy2);
	ft_print_tab(sort_tab(*env_cpy2));
}

void	ft_export4(t_export *data, char ***arg, char ****envs, char ***env_cpy2)
{
	t_export	export;
	char		**args;
	char		***env;

	env = *envs;
	args = *arg;
	export = *data;
	export.i = 0;
	while (args[export.j][export.i] != '=' && args[export.j][export.i] != '\0')
		export.i++;
	export.new_arg = ft_strdup(args[export.j] + export.i + 1);
	if (export.new_arg != NULL)
	{
		export.tmp_new_arg = ft_strndup(args[export.j], export.i + 1);
		export.new_arg = ft_strjoin(export.tmp_new_arg, export.new_arg);
		free(export.tmp_new_arg);
	}
	else
		export.new_arg = ft_strdup(args[export.j]);
	if (args[export.j][export.i] == '=')
		ft_export1(&export, &args, &env, env_cpy2);
	else
		ft_export2(&export, env_cpy2);
	export.j++;
}
