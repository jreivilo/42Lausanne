/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bracket2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:17:12 by afrigger          #+#    #+#             */
/*   Updated: 2023/03/14 20:59:37 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bracket_add(t_parsing_bracket *pb, char const *s)
{
	if (!white_space(*(s + pb->i)) && (*(s + pb->i)) != '<'
		&& (*(s + pb->i)) != '>')
		pb->cnt++;
	if ((*(s + pb->i) == 39 || (*(s + pb->i) == 34 && *(s + pb->i - 1) != 92))
		&& (!pb->quote || pb->quote == *(s + pb->i)))
		pb->quote = (pb->quote - *(s + pb->i)) * -1;
}

void	bracket_tmp(t_parsing_bracket *pb, char const *s, char **tmp)
{
	while (*(s + pb->i))
	{
		bracket_add(pb, s);
		if (white_space(*(s + pb->i)) && !pb->quote && pb->cnt)
		{
			printf("IN\n");
			*(*tmp + pb->j++) = *(s + pb->i);
			break ;
		}
		pb->i++;
	}
}

void	init_pb(t_parsing_bracket *pb)
{
	pb->i = -1;
	pb->j = 0;
	pb->cnt = 0;
	pb->quote = 0;
}
