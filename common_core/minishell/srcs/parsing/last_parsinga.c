/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parsinga.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:54:01 by afrigger          #+#    #+#             */
/*   Updated: 2023/03/14 19:39:11 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	var_swap_size2a(char const **s, char ***env, t_swap *data)
{
	t_swap	swap;

	swap = *data;
	if (**(s + 1) == DQUOTE || **(s + 1) == QUOTE)
		swap.i++;
	else if (**(s + 1) == '?')
	{
		swap.i += ft_strlen(ft_itoa(g_status));
		*s += 1;
	}
	else
	{
		swap.i += var_length2(*s + 1, *env);
		while (!not_alpha_num(**(s + 1)))
			*s += 1;
	}
}

void	var_swap_size2b(char const **s, char ***env, t_swap *data)
{
	t_swap	swap;

	swap = *data;
	if (**(s + 1) == DQUOTE || **(s + 1) == QUOTE)
		;
	else if (**(s + 1) == '?')
	{
		swap.i += ft_strlen(ft_itoa(g_status));
		*s += 1;
	}
	else
	{
		swap.i += (var_length2(*s + 1, *env));
		if (*s[1] >= 48 && *s[1] <= 57)
			*s = *s + 1;
		else
		{
			while (!not_alpha_num(**(s + 1)))
				*s += 1;
		}
	}
}

void	swap_var2a(char const **s, char ***env, t_swap *data)
{
	t_swap	swap;

	swap = *data;
	if (**(s + 1) == 34 || **(s + 1) == QUOTE)
		*(swap.tmp++) = **s;
	else if (**(s + 1) == '?')
	{
		swap.var = ft_itoa(g_status);
		while (swap.var && *swap.var)
			*(swap.tmp++) = *(swap.var++);
		*s += 1;
	}
	else
	{
		swap.var = var_in_env2(*s + 1, *env);
		while (swap.var && *swap.var)
			*(swap.tmp++) = *(swap.var++);
		while (!not_alpha_num(**(s + 1)))
			*s += 1;
	}
}

void	swap_var2b(char const **s, char ***env, t_swap *data)
{
	t_swap	swap;

	swap = *data;
	if (**(s + 1) == DQUOTE || **(s + 1) == QUOTE)
		;
	else if (**(s + 1) == '?')
	{
		swap.var = ft_itoa(g_status);
		while (swap.var && *swap.var)
			*(swap.tmp++) = *(swap.var++);
		*s += 1;
	}
	else
	{
		swap.var = var_in_env2(*s + 1, *env);
		while (swap.var && *swap.var)
			*(swap.tmp++) = *(swap.var++);
		if (*s[1] >= 48 && *s[1] <= 57)
			*s = *s + 1;
		else
		{
			while (!not_alpha_num(**(s + 1)))
				*s += 1;
		}
	}
}
