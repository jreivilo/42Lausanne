/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 18:12:19 by jolivier          #+#    #+#             */
/*   Updated: 2022/12/30 18:12:19 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long long	time_diff(long long int start, long long int end)
{
	return (end - start);
}

void	milisleep(long long milisec)
{
	long long	start;

	start = timestamp();
	while (time_diff(start, timestamp()) < milisec)
		usleep(100);
}
