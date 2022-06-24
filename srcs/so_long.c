/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:23:41 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/24 17:38:56 by gkehren          ###   ########.fr       */
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
#include <stdio.h>
int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		return (write(1, "Please give a path map\n", 24), 0);
	if (parse_map(argv[1], &map) == 1)
		return (0);
	printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n", map.map[0], map.map[1], map.map[2], map.map[3], map.map[4], map.map[5], map.map[6]);
	printf("width = %zu | height %zu\n", map.width, map.height);
	return (memfree(map.map), free(map.map), 0);
}
