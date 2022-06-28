/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:23:41 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/28 21:55:45 by gkehren          ###   ########.fr       */
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
	size_t	map_count;

	if (argc != 2)
		return (write(1, "Please give a path map\n", 24), 0);
	map_count = (size_t)argc - 1;
	if (parse_map(argv[1], &map) == 1)
		return (0);
	start_game(&map, map_count);
	return (memfree(map.map), free(map.map), 0);
}
