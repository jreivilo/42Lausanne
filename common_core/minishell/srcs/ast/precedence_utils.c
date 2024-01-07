/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:00:54 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/14 21:04:45 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_variables_precedence(int *i, int *index, int *quote, int *prnths)
{
	*i = -1;
	*index = 0;
	*quote = 0;
	*prnths = 0;
}

void	increment_variables_preced(int *i, int *index, int **prcdnc, int tmp)
{
	**prcdnc = tmp;
	*index = *i;
	*i += **prcdnc % 3 - 1;
}
