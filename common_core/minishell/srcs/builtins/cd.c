/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 07:29:33 by jolivier          #+#    #+#             */
/*   Updated: 2023/01/13 07:29:33 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(char *name, char *value, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0)
		{
			tmp = ft_strjoin(name, "=");
			env[i] = ft_strjoin(tmp, value);
			free(tmp);
			return ;
		}
		i++;
	}
}

int	ft_cd(char **argv, char **env)
{
	char	*path;
	char	*oldpwd;
	char	*pwd;

	if (argv[1] == NULL)
		path = get_env("HOME", env);
	else if (ft_strncmp(argv[1], "-", 2) == 0)
		path = get_env("OLDPWD", env);
	else
		path = argv[1];
	if (path == NULL)
		return (ft_cd_error1(argv));
	if (chdir(path) == -1)
		return (ft_cd_error2(argv));
	oldpwd = get_env("PWD", env);
	pwd = getcwd(NULL, 0);
	set_env("OLDPWD", oldpwd, env);
	set_env("PWD", pwd, env);
	free(pwd);
	g_status = SUCCESS;
	return (g_status);
}

int	ft_cd_error1(char **argv)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (argv[1])
		ft_putstr_fd(argv[1], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_status = ERROR;
	return (g_status);
}

int	ft_cd_error2(char **argv)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(argv[1], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_status = ERROR;
	return (g_status);
}
