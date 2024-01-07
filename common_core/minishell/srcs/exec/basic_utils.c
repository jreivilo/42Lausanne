/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:07:24 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/14 21:07:29 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pick_buildin(t_builtin *builtin, char ***env)
{
	if (ft_strcmp(builtin->cmd, "cd") == 0)
		return (ft_cd(builtin->args, *env));
	if (ft_strcmp(builtin->cmd, "echo") == 0)
		return (ft_echo(builtin->args, *env));
	if (ft_strcmp(builtin->cmd, "env") == 0)
		return (ft_env(*env));
	if (ft_strcmp(builtin->cmd, "exit") == 0)
		return (ft_exit(builtin->args));
	if (ft_strcmp(builtin->cmd, "export") == 0)
		return (ft_export(env, builtin->args));
	if (ft_strcmp(builtin->cmd, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(builtin->cmd, "unset") == 0)
		return (ft_unset(builtin->args, env));
	return (SUCCESS);
}
