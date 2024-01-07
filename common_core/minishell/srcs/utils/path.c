/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:28:31 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/14 18:20:30 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_only_cmd(char *cmd, char c)
{
	int		i;
	char	*only_cmd;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == c)
		{
			cmd[i] = '\0';
			only_cmd = ft_strdup(cmd);
			return (only_cmd);
		}
		i++;
	}
	return (ft_strdup(cmd));
}

char	*find_path_cmd(char *cmd, char **path_env)
{
	int		i;
	char	*path_cmd;
	char	*tmp;

	i = 0;
	while (path_env[i])
	{
		tmp = ft_strjoin(path_env[i], "/");
		path_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path_cmd, F_OK | X_OK) == 0)
		{
			return (path_cmd);
		}
		free(path_cmd);
		i++;
	}
	return (NULL);
}

char	*get_path_cmd(char *cmd, char **envp)
{
	char	**path_env;
	char	*path_cmd;
	int		i;

	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	path_env = ft_split(envp[i] + 5, ':');
	path_cmd = find_path_cmd(cmd, path_env);
	free_tab(path_env);
	return (path_cmd);
}
