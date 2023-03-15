/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:13:22 by afrigger          #+#    #+#             */
/*   Updated: 2023/03/14 21:25:01 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tab[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

char	*return_arg(char *arg)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	if (arg == NULL)
		return (NULL);
	while (arg[i] != '\"' && arg[i] != '\0')
		i++;
	i++;
	ret = malloc(sizeof(char) * (ft_strlen(arg) - i + 1));
	while (arg[i] != '\"' && arg[i] != '\0')
	{
		ret[j] = arg[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

int	len_until_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '=')
		i++;
	return (i);
}

void	ft_print_tab_unique(char **tab, char **tab2)
{
	t_export	export;

	export.i = 0;
	export.j = 0;
	if (tab2[0] == NULL)
	{
		ft_print_tab(tab);
		return ;
	}
	while (tab[export.i])
	{
		export.j = 0;
		export.tmp = return_arg(tab2[export.j]);
		ft_print_tab_unique1(&export, &tab, &tab2);
		export.i++;
	}
}

void	ft_print_tab_unique1(t_export *data, char ***tabs, char ***tabs2)
{
	t_export	export;
	char		**tab;
	char		**tab2;

	export = *data;
	tab = *tabs;
	tab2 = *tabs2;
	while (ft_strcmp(tab[export.i] + len_until_equal(tab[export.i])
			+ 1, export.tmp) != 0)
	{
		if (tab2[export.j + 1] == NULL)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tab[export.i], 1);
			ft_putstr_fd("\n", 1);
			break ;
		}
		export.j++;
		free(export.tmp);
		export.tmp = return_arg(tab2[export.j]);
	}
}
