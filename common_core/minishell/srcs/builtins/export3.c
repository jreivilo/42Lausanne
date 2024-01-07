/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:10:14 by afrigger          #+#    #+#             */
/*   Updated: 2023/03/14 21:23:47 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sort_tab(char **tab)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[j])
		{
			if (ft_strcmp(tab[i], tab[j]) < 0)
			{
				tmp = ft_strdup(tab[i]);
				free(tab[i]);
				tab[i] = ft_strdup(tab[j]);
				free(tab[j]);
				tab[j] = ft_strdup(tmp);
				free(tmp);
			}
			j++;
		}
		i++;
	}
	return (tab);
}

int	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (i);
}

void	remove_quotes(char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i])
	{
		while (args[i][j])
		{
			if (args[i][j] == '\'' || args[i][j] == '\"')
			{
				ft_strcpy(&args[i][j], &args[i][j + 1]);
				j--;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

char	*ft_strndup(char *str, int n)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = malloc(sizeof(char) * (n + 1));
	while (i < n)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*add_double_quotes(char *arg)
{
	int		i;
	int		j;
	char	*new_arg;

	i = 0;
	j = 0;
	new_arg = malloc(sizeof(char *) * (ft_strlen(arg) + 3));
	while (arg[i] != '=' && arg[i] != '\0')
	{
		new_arg[i] = arg[i];
		i++;
	}
	j = i + 1;
	new_arg[i] = '=';
	new_arg[i + 1] = '\"';
	i += 2;
	while (arg[j])
	{
		new_arg[i] = arg[j];
		i++;
		j++;
	}
	new_arg[i] = '\"';
	new_arg[i + 1] = '\0';
	return (new_arg);
}
