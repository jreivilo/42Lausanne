/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:41:03 by jolivier          #+#    #+#             */
/*   Updated: 2022/11/10 18:41:03 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include "../libft/libft.h"

long int	ft_atoi_l(const char *str);

void		check_num(long int argc, char **argv);
void		check_error(long int argc, char **argv);
void		check_double(long int argc, char **argv);

void		stack_top(long int *stack, long int num);

void		swap_a(long int	*stack_a);
void		swap_b(long int	*stack_b);
void		swap_s(long int	*stack_a, long int	*stack_b);

void		push_a(long int	*stack_a, long int	*stack_b);
void		push_b(long int	*stack_a, long int	*stack_b);

void		rotate_a(long int *stack_a);
void		rotate_b(long int *stack_b);
void		rotate_r(long int *stack_a, long int *stack_b);

void		reverse_rotate_a(long int *stack_a);
void		reverse_rotate_b(long int *stack_b);
void		reverse_rotate_r(long int	*stack_a, long int	*stack_b);

void		rotate_min_first(long int *stack);
long int	find_min(long int *stack);
long int	find_max(long int *stack);
long int	len_s(long int *stack);
long int	find_pos(long int *stack_a, long int stack);
long int	find_pos_on(long int *stack_a, long int stack);

void		sort(long int *stack);
void		small_sort(long int *st_a, long int *st_b);
void		medium_sort(long int *st_a, long int *st_b, long int length);
void		big_sort(long int *stack_a, long int *stack_b, long int length);

void		start_end_min_max(long int *start, long int *end, long int length);
void		start_end(long int *start, long int *end, long int length);
long int	get_n(long int length);

void		pushb_plusend(long int *stack_a, long int *stack_b, long int *end);

void		printf_stack(long int *stack_a, long int *stack_b);
#endif