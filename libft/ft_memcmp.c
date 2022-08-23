/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 08:47:37 by jolivier          #+#    #+#             */
/*   Updated: 2022/08/23 08:47:37 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
	{
		return(0);
	}
	while (((unsigned char *)str1)[i] == ((unsigned char *)str2)[i] && i < n)
	{
		i++;
	}
	if (i == n)
	{
		return(((unsigned char *)str1)[i - 1] - ((unsigned char *)str2)[i - 1]);
	}
	return(((unsigned char *)str1)[i] - ((unsigned char *)str2)[i]);
}
/*
int main () {
   char str1[15] = "abcdef";
   char str2[15] = "ABCDEF";
   int ret;

   ret = ft_memcmp(str1, str2, 5);

   if(ret > 0) {
      printf("str2 is less than str1");
   } else if(ret < 0) {
      printf("str1 is less than str2");
   } else {
      printf("str1 is equal to str2");
   }
   
   return(0);
}
*/