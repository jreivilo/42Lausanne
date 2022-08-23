/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 13:26:42 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/18 13:26:45 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

void	start(char *str)
{
	if ('a' <= str[0] && str[0] <= 'z')
	{
		str[0] = str[0] - 'a' + 'A';
	}
}

char	*ft_strcapitalize(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		start(str);
		if ('A' <= str[i + 1] && str[i + 1] <= 'Z')
		{
			str[i + 1] = str[i + 1] - 'A' + 'a';
		}
		if ((str[i] < 'A' || ('Z' < str[i] && str[i] < 'a') || 'z' < str[i]))
		{
			if (('0' > str[i] || str[i] > '9'))
			{
				if ('a' <= str[i + 1] && str[i + 1] <= 'z')
				{
					str[i + 1] = str[i + 1] - 'a' + 'A';
				}
			}
		}
		i++;
	}
	return (str);
}

/*
int main()
{
	char str[] = "alut, comment tu vas ? 42mots quArante-deux; cinq	uante+et+un";
	printf("Result:%s\n", ft_strcapitalize(str));
}
*/