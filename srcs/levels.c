/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:29:45 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/29 17:54:22 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	mem_set(void *dst, unsigned char b, size_t n)
{
	while (n)
	{
		*(unsigned char *)dst = b;
		dst++;
		n--;
	}
}

t_fpos	get_pos(t_map *map, char c)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (y < map->height)
	{
		while (x < map->width)
		{
			if (map->map[y][x] == c)
				return ((t_fpos){(float)x, (float)y});
			x++;
		}
		y++;
	}
	return ((t_fpos){0, 0});
}

bool	generate_level(t_mlx *mlx, t_map *map)
{
	mem_set(&mlx->level, 0x00, sizeof(t_level));
	mlx->level.player_pos = get_pos(map, 'P');
	mlx->level.camera = mlx->level.player_pos;
	return (true);
}

void	destroy_level(t_level *level)
{
	free(level->walls);
	free(level->corner);
	free(level->enemy);
}
