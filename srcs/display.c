/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 03:17:49 by gkehren           #+#    #+#             */
/*   Updated: 2022/06/28 22:37:31 by gkehren          ###   ########.fr       */
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

int	generate_game(t_mlx *mlx, t_map *map, size_t map_count)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	if (!load_assets(mlx->mlx, mlx->images))
		return (mlx_destroy_display(mlx->mlx), free(mlx->mlx), 1);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "so_long");
	if (!mlx->win)
		return (mlx_destroy_display(mlx->mlx), free(mlx->mlx), 1);
	if (!generate_image(mlx->mlx, WIDTH, HEIGHT, &mlx->canvas))
		return (mlx_destroy_window(mlx->mlx, mlx->win),
				mlx_destroy_display(mlx->mlx), free(mlx->mlx), 1);
	if (!generate_level(mlx, &map[0]))
		return (mlx_destroy_image(mlx->mlx, mlx->canvas.image),
				mlx_destroy_window(mlx->mlx, mlx->win),
				mlx_destroy_display(mlx->mlx), free(mlx->mlx), 1);
	mlx->map = map;
	mlx->cur_map = 0;
	mlx->map_count = map_count;
	return (0);
}

int	start_game(t_map *map, size_t map_count)
{
	t_mlx	mlx;

	mem_set(&mlx, 0, sizeof(t_mlx));
	if (generate_game(&mlx, map, map_count) == 1)
		return (1);
	mlx_hook(mlx.win, 17, 0, destroy_hook, &mlx);
	mlx_hook(mlx.win, 2, 1 << 0, key_press_hook, &mlx);
	mlx_hook(mlx.win, 3, 1 << 1, key_release_hook, &mlx);
	mlx_loop_hook(mlx.mlx, loop_hook, &mlx);
	mlx_loop(mlx.mlx);
	destroy_level(&mlx.level);
	return (0);
}
