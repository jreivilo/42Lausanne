/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:43:05 by jolivier          #+#    #+#             */
/*   Updated: 2022/11/10 17:41:57 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*real_path_cmd(char *only_cmd, char **path_tab)
{
	int		i;
	char	*real_path_cmd;
	char	*tmp;

	i = 0;
	while (path_tab[i])
	{
		tmp = ft_strjoin(path_tab[i], "/");
		real_path_cmd = ft_strjoin(tmp, only_cmd);
		free(tmp);
		if (access(real_path_cmd, F_OK) == 0)
			return (real_path_cmd);
		free(real_path_cmd);
		i++;
	}
	return (NULL);
}

char	*find_cmd(char *only_cmd, char **envp)
{
	char	**path_tab;
	char	*path_cmd;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	path_tab = ft_split(envp[i] + 5, ':');
	path_cmd = real_path_cmd(only_cmd, path_tab);
	split_free(path_tab);
	if (path_cmd == NULL)
		return (NULL);
	return (path_cmd);
}
