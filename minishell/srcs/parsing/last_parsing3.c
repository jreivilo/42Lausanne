/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parsing3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:47:27 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/14 20:56:06 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_var_dollar_quote(char const **s, char **env, char **tmp)
{
	char	*var;

	if (*(*s + 1) == DQUOTE || *(*s + 1) == QUOTE)
		*(*tmp)++ = *(*s)++;
	else if (*(*s + 1) == '?')
	{
		var = ft_itoa(g_status);
		while (var && *var)
			*(*tmp)++ = *(var++);
		*s += 1;
	}
	else
	{
		var = var_in_env2(*s + 1, env);
		while (var && *var)
			*(*tmp)++ = *(var++);
		if (*(*s + 1) >= 48 && *(*s + 1) <= 57)
			*s += 1;
		else
		{
			while (!not_alpha_num(*(*s + 1)))
				*s += 1;
		}
	}
}

void	swap_var_dollar_no_quote(char const **s, char **env, char **tmp)
{
	char	*var;

	if (*(*s + 1) == DQUOTE || *(*s + 1) == QUOTE)
		;
	else if (*(*s + 1) == '?')
	{
		var = ft_itoa(g_status);
		while (var && *var)
			*(*tmp)++ = *(var++);
		*s += 1;
	}
	else
	{
		var = var_in_env2(*s + 1, env);
		while (var && *var)
			*(*tmp)++ = *(var++);
		if (*(*s + 1) >= 48 && *(*s + 1) <= 57)
			*s += 1;
		else
		{
			while (!not_alpha_num(*(*s + 1)))
				*s += 1;
		}
	}
}

void	swap_var_quote_dquote(int *quote, char **tmp, char const **s)
{
	if (!*quote || *quote == **s)
		*quote = (*quote - **s) * -1;
	*(*tmp)++ = **s;
}

void	var_swap_size_dollar_quote(size_t *i, char const **s, char **env)
{
	if (*(*s + 1) == DQUOTE || *(*s + 1) == QUOTE)
		*i += 1;
	else if (*(*s + 1) == '?')
	{
		*i += ft_strlen(ft_itoa(g_status));
		*s += 1;
	}
	else
	{
		*i += var_length2(*s + 1, env);
		while (!not_alpha_num(*(*s + 1)))
			*s += 1;
	}
}

void	var_swap_size_no_dollar_quote(size_t *i, char const **s, char **env)
{
	if (*(*s + 1) == DQUOTE || *(*s + 1) == QUOTE)
		;
	else if (*(*s + 1) == '?')
	{
		*i += ft_strlen(ft_itoa(g_status));
		*s += 1;
	}
	else
	{
		*i += var_length2(*s + 1, env);
		if (*(*s + 1) >= 48 && *(*s + 1) <= 57)
			*s += 1;
		else
		{
			while (!not_alpha_num(*(*s + 1)))
				*s += 1;
		}
	}
}
