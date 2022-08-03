/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:57:21 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/18 17:57:23 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

void	special(char *str, int i)
{
	int		tpm;
	char	*hex;

	hex = "0123456789abcdef";
	tpm = 0;
	write(1, "\\", 1);
	tpm = hex[str[i] / 16];
	write(1, &tpm, 1);
	tpm = hex[str[i] % 16];
	write(1, &tpm, 1);
}

void	specialneg(char *str, int i)
{
	int		tpm;
	char	*hex2;
	char	*hex;

	hex2 = "89abcdef";
	hex = "0123456789abcdef";
	tpm = 0;
	write(1, "\\", 1);
	tpm = hex2[str[i] / 16];
	write(1, &tpm, 1);
	tpm = hex[str[i] % 16];
	write(1, &tpm, 1);
}

void	ft_putstr_non_printable(char *str)
{
	int		i;
	int		tpm;
	char	*hex;

	hex = "0123456789abcdef";
	tpm = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 32)
		{
			write(1, str + i, 1);
		}
		if (str[i] < 32 && str[i] >= 0)
		{
			special(str, i);
		}
		if (str[i] < 0)
		{
			str[i] = str[i] + 128;
			specialneg(str, i);
		}
		i++;
	}
}

int main()
{
	char *str = "Couc\xf3ou\ntu vas bien ?:C";
	ft_putstr_non_printable(str);
}
