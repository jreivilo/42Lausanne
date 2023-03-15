/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bracket.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:42:10 by hradoux           #+#    #+#             */
/*   Updated: 2023/03/14 20:59:33 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*				FT_SUBSTR_MINISHELL
 *
 * 	Comme celle de libft avec la rajout de trim_ws.
 */

int	define_size_2(char const *s, unsigned int index)
{
	int	i;
	int	cnt;
	int	size;
	int	quote;

	size = 0;
	s += index;
	i = -1;
	quote = 0;
	cnt = 0;
	while (*(s + (++i)))
	{
		if (!white_space(*(s + i)) && (*(s + i)) != '<' && (*(s + i)) != '>')
			cnt++;
		if ((*(s + i) == 39 || (*(s + i) == 34 && *(s + i - 1) != 92))
			&& (!quote || quote == *(s + i)))
			quote = (quote - *(s + i)) * -1;
		if (white_space(*(s + i)) && !quote && cnt)
			break ;
		if (!white_space(*(s + i)))
			size++;
	}
	return (size);
}

size_t	define_size(char const *s, unsigned int index)
{
	int		i;
	int		cnt;
	int		quote;
	size_t	size;

	size = ft_strlen(s);
	s += index;
	i = -1;
	quote = 0;
	cnt = 0;
	while (*(s + (++i)))
	{
		if (!white_space(*(s + i)) && (*(s + i)) != '<' && (*(s + i)) != '>')
			cnt++;
		if ((*(s + i) == 39 || (*(s + i) == 34 && *(s + i - 1) != 92))
			&& (!quote || quote == *(s + i)))
			quote = (quote - *(s + i)) * -1;
		if (white_space(*(s + i)) && !quote && cnt)
			break ;
		else
			size--;
	}
	return (size);
}

void	substr_help(t_parsing_bracket *pb, char const **s, char **tmp)
{
	while (*(*s + pb->i))
	{
		bracket_add(pb, *s);
		if (white_space(*(*s + pb->i)) && !pb->quote && pb->cnt)
		{
			*(*tmp + pb->j++) = *(*s + pb->i);
			break ;
		}
		pb->i++;
	}
}

char	*ft_substr_brkt(char const *s, int index)
{
	t_parsing_bracket	pb;
	char				*tmp;
	size_t				size_s;

	size_s = define_size(s, index);
	tmp = ft_calloc(size_s + 1, sizeof(char));
	if (!tmp)
		return (0);
	init_pb(&pb);
	while (*(s + (++pb.i)) && size_s--)
	{
		if (pb.i != index)
			*(tmp + pb.j++) = *(s + pb.i);
		else
			substr_help(&pb, &s, &tmp);
	}
	return (tmp);
}

char	*ft_substr_brkt_2(char const *s, int index)
{
	int		i;
	int		j;
	char	*tmp;
	size_t	size_s;

	size_s = define_size_2(s, index);
	tmp = ft_calloc(size_s + 1, sizeof(char));
	if (!tmp)
		return (0);
	i = 0;
	j = 0;
	s += index;
	while (size_s--)
	{
		if (!white_space(*(s + i)))
			*(tmp + (j++)) = *(s + i);
		else
			size_s++;
		i++;
	}
	return (tmp);
}
