/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_boolean.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 13:10:31 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/31 13:10:33 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BOOLEAN_H
# define FT_BOOLEAN_H 

# include <unistd.h>

typedef int	t_bool;

# define TRUE 1

# define FALSE 0

# define SUCCESS 0
# define EVEN(nbr) (nbr %2 == 0)

# define EVEN_MSG "I have an even number of arguments.\n"

# define ODD_MSG "I have an odd number of arguments.\n"
#endif
