/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:23:41 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/26 04:46:09 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	memfree(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		return (write(1, "Please give a path map\n", 24), 0);
	if (parse_map(argv[1], &map) == 1)
		return (0);
	display_map(&map);
	return (memfree(map.map), free(map.map), 0);
}
