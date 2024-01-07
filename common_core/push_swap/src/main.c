/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:16:08 by jolivier          #+#    #+#             */
/*   Updated: 2022/12/02 14:16:08 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_top(long int *stack, long int num)
{
	long int	i;

	i = 0;
	while (stack[i] != 0)
	{
		i++;
	}
	stack[i + 1] = '\0';
	while (i > 0)
	{
		stack[i] = stack[i - 1];
		i--;
	}
	stack[0] = num;
}

void	fill_stack(long int *stack, char **argv, long int length)
{
	long int	i;

	i = 0;
	while (i < length)
	{
		if (ft_atoi(argv[i + 1]) >= 0)
			stack[i] = ft_atoi(argv[i + 1]) + 1;
		else
			stack[i] = ft_atoi(argv[i + 1]);
		i++;
	}
}

int	sorted(long int *stack, long int length)
{
	long int	i;

	i = 0;
	while (i < length - 1)
	{
		if (stack[i] > stack[i + 1])
			return (0);
		i++;
	}
	return (1);
}

void	launch_sort(long int *stack_a, long int *stack_b, long int length)
{
	if (sorted(stack_a, length) == 1)
		return ;
	if (length == 3)
		small_sort(stack_a, stack_b);
	if (length > 3 && length <= 5)
		medium_sort(stack_a, stack_b, length);
	if (length > 5)
		big_sort(stack_a, stack_b, length);
}

int	main(int argc, char **argv)
{
	long int	*stack_a;
	long int	*stack_b;
	long int	length;
	char		*tmp;

	length = argc - 1;
	if (argc == 2 && ft_strchr(argv[1], ' '))
	{
		length = count_word(argv[1]);
		tmp = ft_strjoin("./push_swap ", argv[1]);
		argv = ft_split(tmp, ' ');
		free(tmp);
	}
	check_error((length + 1), argv);
	stack_a = ft_calloc(length + 1, sizeof(long int));
	stack_b = ft_calloc(length, sizeof(long int));
	fill_stack(stack_a, argv, length);
	if (length == 2)
	{
		if (stack_a[0] > stack_a[1])
			swap_a(stack_a);
	}
	launch_sort(stack_a, stack_b, length);
	free_all(stack_a, stack_b, argv);
	return (0);
}
