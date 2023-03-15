/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:57:41 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/14 20:55:48 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_alpha_num(char c)
{
	if (c >= 48 && c <= 57)
		return (0);
	if (c >= 65 && c <= 90)
		return (0);
	if (c >= 97 && c <= 122)
		return (0);
	if (c == 95)
		return (0);
	return (1);
}

char	*var_in_env2(char const *s, char **env)
{
	int	i;

	while (*env)
	{
		i = 0;
		while (s[i] && (*env)[i] == s[i])
			i++;
		if ((*env)[i] == '=' && not_alpha_num(s[i]))
			return (&(*env)[i + 1]);
		env++;
	}
	if (s[0] == '0')
		return (ft_strdup("minishell"));
	if (s[0] >= 48 && s[0] <= 57)
		return (ft_strdup(""));
	return (NULL);
}

size_t	var_length2(char const *s, char **env)
{
	char	*tmp;

	tmp = var_in_env2(s, env);
	if (!tmp)
		return (0);
	return (ft_strlen(tmp));
}

size_t	var_swap_size2(char const *s, char **env)
{
	int		quote;
	size_t	i;

	i = 0;
	quote = 0;
	while (*s)
	{
		if (*s == '$' && quote == DQUOTE)
			var_swap_size_dollar_quote(&i, &s, env);
		else if (*s == '$' && !quote && *(s + 1))
			var_swap_size_no_dollar_quote(&i, &s, env);
		else if (*s == QUOTE || *s == DQUOTE)
		{
			if (!quote || quote == *s)
				quote = (quote - *s) * -1;
			i++;
		}
		else
			i++;
		s++;
	}
	return (i);
}

char	*swap_var2(char const *s, char **env)
{
	int		quote;
	char	*tmp;
	char	*tmp_start;

	quote = 0;
	tmp = ft_calloc(var_swap_size2(s, env) + 1, sizeof(char));
	if (!tmp)
		return (0);
	tmp_start = tmp;
	while (*s)
	{
		if (*s == '$' && quote == DQUOTE)
			swap_var_dollar_quote(&s, env, &tmp);
		else if (*s == '$' && !quote && *(s + 1))
			swap_var_dollar_no_quote(&s, env, &tmp);
		else if (*s == QUOTE || *s == DQUOTE)
			swap_var_quote_dquote(&quote, &tmp, &s);
		else
			*(tmp++) = *s;
		s++;
	}
	return (tmp_start);
}
