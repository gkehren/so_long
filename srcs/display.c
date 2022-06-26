/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 03:17:49 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/26 04:52:23 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	display_pixel(t_pos *pixel, int color, void *mlx, void *win)
{
	int	x;
	int	y;
	int	delta;

	delta = 32;
	x = pixel->x + delta;
	y = pixel->y + delta;
	while (pixel->y < y)
	{
		pixel->x -= delta;
		while (pixel->x < x)
		{
			mlx_pixel_put(mlx, win, pixel->x, pixel->y, color);
			pixel->x++;
		}
		pixel->y++;
	}
	pixel->y -= delta;
}

void	display_element(t_map *map, void *mlx, void *win)
{
	t_pos	pixel;
	int		i;
	int		j;

	pixel.x = 0;
	pixel.y = 0;
	i = 0;
	j = 0;
	while (map->map[j])
	{
		i = 0;
		while (map->map[j][i])
		{
			if (map->map[j][i] == '1')
				display_pixel(&pixel, 0xFF0000, mlx, win);
			else if (map->map[j][i] == '0')
				display_pixel(&pixel, 0xFFFFFF, mlx, win);
			else
				display_pixel(&pixel, 0x59FF00, mlx, win);
			i++;
		}
		pixel.y += 32;
		pixel.x = 0;
		j++;
	}
}

void	display_map(t_map *map)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 800, "so_long");
	display_element(map, mlx, win);
	mlx_loop(mlx);
}
