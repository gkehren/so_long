/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 03:17:49 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/27 19:04:55 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	display_pixel(t_fpos *pixel, int color, void *mlx, void *win)
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

void	display_element(t_map *map, t_mlx *mlx)
{
	t_fpos	pixel;
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
				display_pixel(&pixel, 0xFF0000, mlx->mlx, mlx->win);
			else if (map->map[j][i] == '0')
				display_pixel(&pixel, 0xFFFFFF, mlx->mlx, mlx->win);
			else
				display_pixel(&pixel, 0x59FF00, mlx->mlx, mlx->win);
			i++;
		}
		pixel.y += 32;
		pixel.x = 0;
		j++;
	}
}

int	display_map(t_map *map)
{
	t_mlx	mlx;

	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		return (1);
	if (!load_assets(mlx.mlx, mlx.images))
		return (mlx_destroy_display(mlx.mlx), free(mlx.mlx), 1);
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "so_long");
	if (!mlx.win)
		return (mlx_destroy_display(mlx.mlx), free(mlx.mlx), 1);
	if (!generate_image(mlx.mlx, WIDTH, HEIGHT, &mlx.canvas))
		return (mlx_destroy_window(mlx.mlx, mlx.win),
				mlx_destroy_display(mlx.mlx), free(mlx.mlx), 1);
	display_element(map, &mlx);
	if (!generate_level(&mlx, &map[0]))
		return (mlx_destroy_image(mlx.mlx, mlx.canvas.image),
				mlx_destroy_window(mlx.mlx, mlx.win),
				mlx_destroy_display(mlx.mlx), free(mlx.mlx), 1);
	mlx_loop(mlx.mlx);
	map->mlx = mlx.mlx;
	map->win = mlx.win;
	return (0);
}
