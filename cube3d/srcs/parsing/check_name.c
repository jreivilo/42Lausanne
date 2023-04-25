/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:33:23 by nadel-be          #+#    #+#             */
/*   Updated: 2023/04/13 13:45:28 by nadel-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_name_map(char *argv)
{
	int		len;
	char	tmp[5];

	len = ft_strlen(argv);
	tmp[4] = '\0';
	tmp[3] = argv[len - 1];
	tmp[2] = argv[len - 2];
	tmp[1] = argv[len - 3];
	tmp[0] = argv[len - 4];
	if (ft_strncmp(tmp, ".cub", 4) != 0)
	{
		error("Wrong extension map\n");
		return (ERROR);
	}
	return (SUCCESS);
}
