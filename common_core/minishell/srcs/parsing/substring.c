/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substring_minishell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:18:25 by hradoux           #+#    #+#             */
/*   Updated: 2023/01/20 12:29:05 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*				WHITE SPACE
 *
 *	Définis si la caractère reçu est un white space ou non
 */

#include "minishell.h"

int	white_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

/*				TRIM_WS pour trim white spaces
 *
 * Cette fonction a pour but de retirer les white spaces se situant
 *	aux extremites du str ainsi que des eventuelles parantheses se
 *	situant elle aussi aux extremites du str recu par un node parent
 *	Exepemple: [ ((a|b) && (true || echo bonjour))		]
 *							deviendra
 *				[(a|b) && (true || echo bonjour)]
 */
void	trim_ws(char const *s, unsigned int *start, size_t *len)
{
	int	condition;

	condition = 0;
	while (white_space(*(s + *start)))
	{
		(*start)++;
		(*len)--;
	}
	if (*(s + *start) == '(')
		condition++;
	while (white_space(*(s + *start + *len - 1)))
		(*len)--;
	if (*(s + *start + *len - 1) == ')')
		condition++;
	if (condition == 2)
	{
		(*start)++;
		(*len) -= 2;
	}
}

/*				FT_SUBSTR_MINISHELL
 *
 * 	Comme celle de libft avec la rajout de trim_ws.
 */
char	*ft_substr_minishell(char const *s, unsigned int start, size_t len)
{
	size_t	size_s;
	char	*tmp;
	char	*start_tmp;

	if (!len)
		return (NULL);
	size_s = ft_strlen(s);
	trim_ws(s, &start, &len);
	if (start >= size_s)
		return (NULL);
	if (size_s - start < len)
		tmp = ft_calloc(size_s - start + 1, sizeof(char));
	else
		tmp = ft_calloc(len + 1, sizeof(char));
	if (!tmp)
		return (0);
	start_tmp = tmp;
	s += start;
	while (*s && len--)
		*tmp++ = *s++;
	return (start_tmp);
}
