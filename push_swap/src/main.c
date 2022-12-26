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

void	printf_stack(long int *stack_a, long int *stack_b)
{
	long int	i;

	i = 0;
	while (stack_a[i] != '\0')
	{
		printf("%ld ", stack_a[i]);
		i++;
	}
	printf("\n");
	i = 0;
	while (stack_b[i] != '\0')
	{
		printf("%ld ", stack_b[i]);
		i++;
	}
	printf("\n");
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

int	main(int argc, char **argv)
{
	long int	*stack_a;
	long int	*stack_b;
	long int	length;

	length = argc - 1;
	check_error(argc, argv);
	stack_a = ft_calloc(length + 1, sizeof(long int));
	stack_b = ft_calloc(length, sizeof(long int));
	fill_stack(stack_a, argv, length);
	if (length == 2)
	{
		if (stack_a[0] > stack_a[1])
			swap_a(stack_a);
	}
	if (length == 3)
		small_sort(stack_a, stack_b);
	if (length > 3 && length <= 5)
		medium_sort(stack_a, stack_b, length);
	if (length > 5)
		big_sort(stack_a, stack_b, length);
	free(stack_a);
	free(stack_b);
	return (0);
}
